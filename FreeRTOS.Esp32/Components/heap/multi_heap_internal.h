// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// This file was modified
// Copyright 2023, Sven Bieg (svenbieg@web.de)
// http://github.com/svenbieg/heap

#pragma once


//=======
// Using
//=======

#include <multi_heap.h>
#include <stdbool.h>
#include <stdint.h>
#include "block_map.h"


//======
// Info
//======

typedef struct multi_heap_info
{
void* lock;
size_t size;
size_t used;
size_t free_bytes;
size_t minimum_free_bytes;
size_t allocated_blocks;
size_t free_blocks;
size_t total_blocks;
uint32_t flags;
size_t free_block;
block_map_t map_free;
}multi_heap_t;


//==========
// Internal
//==========

void* multi_heap_alloc_internal(multi_heap_handle_t heap, size_t size);
bool multi_heap_check_internal(multi_heap_handle_t heap, bool print_errors);
void multi_heap_dump_internal(multi_heap_handle_t heap);
void multi_heap_free_to_cache(multi_heap_handle_t heap, void* ptr);
