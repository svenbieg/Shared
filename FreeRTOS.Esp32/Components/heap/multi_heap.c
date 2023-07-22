// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// This file was modified
// Copyright 2023, Sven Bieg (svenbieg@web.de)
// http://github.com/svenbieg/heap


//=======
// Using
//=======

#include <string.h>
#include "heap_block.h"
#include "multi_heap_internal.h"


//=========
// Private
//=========

void* multi_heap_alloc_from_cache(multi_heap_handle_t heap, size_t size)
{
size_t free_block=heap->free_block;
size_t* prev_ptr=&heap->free_block;
while(free_block)
	{
	size_t* buf=(size_t*)heap_block_get_pointer(free_block);
	size_t next_free=*buf;
	heap_block_info_t info;
	heap_block_get_info(heap, buf, &info);
	if(info.size==size)
		{
		*prev_ptr=next_free;
		return buf;
		}
	if(info.size>=size+BLOCK_SIZE_MIN)
		{
		heap_block_info_t free_info;
		free_info.offset=free_block+size;
		free_info.size=info.size-size;
		free_info.free=false;
		size_t* free_body=(size_t*)heap_block_init(heap, &free_info);
		*free_body=next_free;
		*prev_ptr=free_info.offset;
		info.size=size;
		return heap_block_init(heap, &info);
		}
	prev_ptr=buf;
	free_block=next_free;
	}
return NULL;
}

void* multi_heap_alloc_from_foot(multi_heap_handle_t heap, size_t size)
{
if(heap->used+size>heap->size)
	return NULL;
heap_block_info_t info;
info.offset=(size_t)heap+heap->used;
info.size=size;
info.free=false;
heap->free_bytes-=size;
heap->used+=size;
heap->allocated_blocks++;
heap->total_blocks++;
return heap_block_init(heap, &info);
}

void* multi_heap_alloc_from_map(multi_heap_handle_t heap, size_t size)
{
heap_block_info_t info;
if(!block_map_get_block(heap, &heap->map_free, size, &info))
	return NULL;
heap->free_bytes-=info.size;
heap->allocated_blocks++;
heap->free_blocks--;
size_t free_size=info.size-size;
if(free_size>=BLOCK_SIZE_MIN)
	{
	heap_block_info_t free_info;
	free_info.offset=info.offset+size;
	free_info.size=free_size;
	free_info.free=false;
	void* free_buf=heap_block_init(heap, &free_info);
	multi_heap_free_to_cache(heap, free_buf);
	info.size=size;
	}
info.free=false;
return heap_block_init(heap, &info);
}

void multi_heap_free_to_map(multi_heap_handle_t heap, void* buf)
{
heap_block_chain_t info;
heap_block_get_chain(heap, buf, &info);
size_t heap_end=(size_t)heap+heap->used;
size_t offset=info.current.offset;
size_t size=info.current.size;
assert(offset>=(size_t)heap);
assert(offset<heap_end);
assert(offset+size<=heap_end);
if(info.previous.free)
	{
	offset=info.previous.offset;
	size+=info.previous.size;
	block_map_remove_block(heap, &heap->map_free, &info.previous);
	heap->free_bytes-=info.previous.size;
	heap->free_blocks--;
	heap->total_blocks--;
	}
if(!info.next.offset)
	{
	heap->free_bytes+=size;
	heap->used-=size;
	heap->total_blocks--;
	return;
	}
if(info.next.free)
	{
	size+=info.next.size;
	block_map_remove_block(heap, &heap->map_free, &info.next);
	heap->free_bytes-=info.next.size;
	heap->free_blocks--;
	heap->total_blocks--;
	}
heap->free_bytes+=size;
heap->allocated_blocks--;
heap->free_blocks++;
info.current.offset=offset;
info.current.size=size;
info.current.free=true;
heap_block_init(heap, &info.current);
block_map_add_block(heap, &heap->map_free, &info.current);
}

void multi_heap_free_cache(multi_heap_handle_t heap)
{
size_t free_block=heap->free_block;
heap->free_block=0;
while(free_block)
	{
	size_t* body_ptr=(size_t*)heap_block_get_pointer(free_block);
	free_block=*body_ptr;
	multi_heap_free_to_map(heap, body_ptr);
	}
}


//==========
// Internal
//==========

void* multi_heap_alloc_internal(multi_heap_handle_t heap, size_t size)
{
size=heap_block_calc_size(size);
void* p=multi_heap_alloc_from_cache(heap, size);
if(p)
	return p;
p=multi_heap_alloc_from_map(heap, size);
if(p)
	return p;
return multi_heap_alloc_from_foot(heap, size);
}

bool multi_heap_check_internal(multi_heap_handle_t heap, bool print_errors)
{
return true; // TODO
}

void multi_heap_dump_internal(multi_heap_handle_t heap)
{
if(!heap->total_blocks)
	return;
MULTI_HEAP_PRINTF("heap 0x%x:\n", heap);
size_t heap_start=(size_t)heap+sizeof(multi_heap_t);
MULTI_HEAP_PRINTF("\tstart: 0x%x\tend: 0x%x\tused: %u\tsize: %u\n", heap_start, heap_start+heap->size, heap->used, heap->size);
MULTI_HEAP_PRINTF("\tfree bytes: %u", heap->free_bytes);
MULTI_HEAP_PRINTF("\n\tblocks allocated: %u\tfree blocks: %u\ttotal blocks: %u\n", heap->allocated_blocks, heap->free_blocks, heap->total_blocks);
MULTI_HEAP_PRINTF("\n");
}

void multi_heap_free_to_cache(multi_heap_handle_t heap, void* buf)
{
size_t* body_ptr=(size_t*)buf;
*body_ptr=heap->free_block;
heap->free_block=heap_block_get_offset(buf);
}


//========
// Public
//========

void *multi_heap_aligned_alloc(multi_heap_handle_t heap, size_t size, size_t alignment)
{
if(alignment!=sizeof(size_t))
	return NULL; // TODO
return multi_heap_malloc(heap, size);
}

void* multi_heap_malloc(multi_heap_handle_t heap, size_t size)
{
if(heap==NULL||size==0)
	return NULL;
MULTI_HEAP_LOCK(heap->lock);
size=heap_block_calc_size(size);
void* p=multi_heap_alloc_from_map(heap, size);
if(!p)
	p=multi_heap_alloc_from_foot(heap, size);
multi_heap_free_cache(heap);
MULTI_HEAP_UNLOCK(heap->lock);
return p;
}

void multi_heap_aligned_free(multi_heap_handle_t heap, void* p)
{
multi_heap_free(heap, p);
}

void multi_heap_free(multi_heap_handle_t heap, void* p)
{
MULTI_HEAP_ASSERT(heap!=NULL);
if(!p)
	return;
MULTI_HEAP_LOCK(heap->lock);
multi_heap_free_to_map(heap, p);
multi_heap_free_cache(heap);
MULTI_HEAP_UNLOCK(heap->lock);
}

void* multi_heap_realloc(multi_heap_handle_t heap, void* p, size_t size)
{
if(p==NULL)
	return multi_heap_malloc(heap, size);
return NULL; // TODO
}

size_t multi_heap_get_allocated_size(multi_heap_handle_t heap, void* p)
{
MULTI_HEAP_LOCK(heap->lock);
heap_block_info_t info;
heap_block_get_info(heap, p, &info);
MULTI_HEAP_UNLOCK(heap->lock);
return info.size;
}

multi_heap_handle_t multi_heap_register(void* head, size_t size)
{
size_t offset=multi_heap_align_up((size_t)head, sizeof(size_t));
size=multi_heap_align_down(size, sizeof(size_t));
multi_heap_t* heap=(multi_heap_t*)offset;
size_t start=offset+sizeof(multi_heap_t);
size_t end=offset+size;
heap->lock=NULL;
heap->size=end-start;
heap->used=sizeof(multi_heap_t);
heap->free_bytes=heap->size-heap->used;
heap->minimum_free_bytes=heap->free_bytes;
heap->allocated_blocks=0;
heap->free_blocks=0;
heap->total_blocks=0;
heap->flags=0;
heap->free_block=0;
block_map_init(&heap->map_free);
return heap;
}

void multi_heap_set_lock(multi_heap_handle_t heap, void* lock)
{
heap->lock=lock;
}

void multi_heap_dump(multi_heap_handle_t heap)
{
MULTI_HEAP_LOCK(heap->lock);
multi_heap_dump_internal(heap);
MULTI_HEAP_UNLOCK(heap->lock);
}

bool multi_heap_check(multi_heap_handle_t heap, bool print_errors)
{
MULTI_HEAP_LOCK(heap->lock);
bool b=multi_heap_check_internal(heap, print_errors);
MULTI_HEAP_UNLOCK(heap->lock);
return b;
}

size_t multi_heap_free_size(multi_heap_handle_t heap)
{
if(heap==NULL)
	return 0;
MULTI_HEAP_LOCK(heap->lock);
size_t size=heap->free_bytes;
MULTI_HEAP_UNLOCK(heap->lock);
return size;
}

size_t multi_heap_minimum_free_size(multi_heap_handle_t heap)
{
if(heap==NULL)
	return 0;
MULTI_HEAP_LOCK(heap->lock);
size_t size=heap->minimum_free_bytes;
MULTI_HEAP_UNLOCK(heap->lock);
return size;
}

void multi_heap_get_info(multi_heap_handle_t heap, multi_heap_info_t *info)
{
memset(info, 0, sizeof(multi_heap_info_t));
if(heap==NULL)
	return;
MULTI_HEAP_LOCK(heap->lock);
info->total_free_bytes=heap->free_bytes;
info->total_allocated_bytes=heap->size;
info->largest_free_block=heap->size-heap->used;
info->minimum_free_bytes=heap->minimum_free_bytes;
info->allocated_blocks=heap->allocated_blocks;
info->free_blocks=heap->free_blocks;
info->total_blocks=heap->total_blocks;
MULTI_HEAP_UNLOCK(heap->lock);
}
