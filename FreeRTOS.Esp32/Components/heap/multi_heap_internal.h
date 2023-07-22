/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

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
