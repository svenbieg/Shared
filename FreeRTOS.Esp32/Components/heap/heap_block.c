//==============
// heap_block.c
//==============

// Copyright 2023, Sven Bieg (svenbieg@web.de)
// http://github.com/svenbieg/heap


//=======
// Using
//=======

#include "heap_block.h"
#include "multi_heap_internal.h"


//==================
// Con-/Destructors
//==================

void* heap_block_init(multi_heap_handle_t heap, heap_block_info_t const* info)
{
MULTI_HEAP_ASSERT(info->size%sizeof(size_t)==0);
MULTI_HEAP_ASSERT(info->offset>=(size_t)heap+sizeof(multi_heap_t));
MULTI_HEAP_ASSERT(info->offset+info->size<=(size_t)heap+heap->size);
size_t* head_ptr=(size_t*)info->offset;
*head_ptr=info->header;
head_ptr++;
size_t* foot_ptr=(size_t*)(info->offset+info->size);
foot_ptr--;
*foot_ptr=info->header;
return head_ptr;
}


//========
// Common
//========

size_t heap_block_calc_size(size_t size)
{
return multi_heap_align_up(size, sizeof(size_t))+2*sizeof(size_t);
}

size_t heap_block_get_offset(void* ptr)
{
return (size_t)ptr-sizeof(size_t);
}

void* heap_block_get_pointer(size_t offset)
{
return (void*)(offset+sizeof(size_t));
}


//========
// Access
//========

void heap_block_get_chain(multi_heap_handle_t heap, void* ptr, heap_block_chain_t* info)
{
size_t heap_offset=(size_t)heap;
size_t heap_start=heap_offset+sizeof(multi_heap_info_t);
size_t offset=heap_block_get_offset(ptr);
size_t* head_ptr=(size_t*)offset;
info->current.offset=offset;
info->current.header=*head_ptr;
if(offset>heap_start)
	{
	size_t* foot_ptr=(size_t*)offset;
	foot_ptr--;
	info->previous.header=*foot_ptr;
	info->previous.offset=offset-info->previous.size;
	}
else
	{
	info->previous.header=0;
	info->previous.offset=0;
	}
size_t heap_end=heap_offset+heap->used;
size_t next_offset=offset+info->current.size;
if(next_offset<heap_end)
	{
	size_t* head_ptr=(size_t*)next_offset;
	info->next.offset=next_offset;
	info->next.header=*head_ptr;
	}
else
	{
	info->next.header=0;
	info->next.offset=0;
	}
}

void heap_block_get_info(multi_heap_handle_t heap, void* ptr, heap_block_info_t* info)
{
info->offset=heap_block_get_offset(ptr);
MULTI_HEAP_ASSERT(info->offset>=(size_t)heap+sizeof(multi_heap_info_t));
MULTI_HEAP_ASSERT(info->offset<(size_t)heap+heap->used);
size_t* head_ptr=(size_t*)info->offset;
info->header=*head_ptr;
MULTI_HEAP_ASSERT(info->size>=3*sizeof(size_t));
MULTI_HEAP_ASSERT(info->offset+info->size<=(size_t)heap+heap->used);
MULTI_HEAP_ASSERT(*((size_t*)(info->offset+info->size-sizeof(size_t)))==*head_ptr);
}
