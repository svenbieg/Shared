/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// This file was modified
// Copyright 2023, Sven Bieg (svenbieg@web.de)
// http://github.com/svenbieg/heap

#pragma once

#ifdef MULTI_HEAP_FREERTOS

#include "freertos/FreeRTOS.h"

#include "sdkconfig.h"
#include "esp_rom_sys.h"
#include <assert.h>

typedef portMUX_TYPE multi_heap_lock_t;

/* Because malloc/free can happen inside an ISR context,
   we need to use portmux spinlocks here not RTOS mutexes */
#define MULTI_HEAP_LOCK(PLOCK) do {                         \
        if((PLOCK) != NULL) {                               \
            portENTER_CRITICAL((portMUX_TYPE*)(PLOCK));                    \
        }                                                   \
    } while(0)


#define MULTI_HEAP_UNLOCK(PLOCK) do {                       \
        if ((PLOCK) != NULL) {                              \
            portEXIT_CRITICAL((portMUX_TYPE*)(PLOCK));                     \
        }                                                   \
    } while(0)

#define MULTI_HEAP_LOCK_INIT(PLOCK) do {                    \
        portMUX_INITIALIZE((portMUX_TYPE*)(PLOCK));                        \
    } while(0)

#define MULTI_HEAP_LOCK_STATIC_INITIALIZER     portMUX_INITIALIZER_UNLOCKED

/* Not safe to use std i/o while in a portmux critical section,
   can deadlock, so we use the ROM equivalent functions. */

#define MULTI_HEAP_PRINTF esp_rom_printf
#define MULTI_HEAP_STDERR_PRINTF(MSG, ...) esp_rom_printf(MSG, __VA_ARGS__)

inline static void multi_heap_assert(bool condition, const char *format, const char* file, int line)
{
    /* Can't use libc assert() here as it calls printf() which can cause another malloc() for a newlib lock.

       Also, it's useful to be able to print the memory address where corruption was detected.
    */
#ifndef NDEBUG
    if(!condition) {
#ifndef CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT
        esp_rom_printf(format, file, line);
#endif  // CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT
        abort();
    }
#else // NDEBUG
    (void) condition;
#endif // NDEBUG
}

#define MULTI_HEAP_ASSERT(CONDITION) \
    multi_heap_assert((CONDITION), "CORRUPT HEAP: %s:%d\n", \
                      __FILE__, __LINE__)

#ifdef CONFIG_HEAP_TASK_TRACKING
#include <freertos/task.h>
#define MULTI_HEAP_BLOCK_OWNER TaskHandle_t task;
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD) (HEAD)->task = xTaskGetCurrentTaskHandle()
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) ((HEAD)->task)
#else
#define MULTI_HEAP_BLOCK_OWNER
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD)
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) (NULL)
#endif

#else // MULTI_HEAP_FREERTOS

#include <assert.h>

#define MULTI_HEAP_PRINTF printf
#define MULTI_HEAP_STDERR_PRINTF(MSG, ...) fprintf(stderr, MSG, __VA_ARGS__)
#define MULTI_HEAP_LOCK(PLOCK)  (void) (PLOCK)
#define MULTI_HEAP_UNLOCK(PLOCK)  (void) (PLOCK)
#define MULTI_HEAP_LOCK_INIT(PLOCK)  (void) (PLOCK)
#define MULTI_HEAP_LOCK_STATIC_INITIALIZER  0

#define MULTI_HEAP_ASSERT(CONDITION) assert(CONDITION)

#define MULTI_HEAP_BLOCK_OWNER
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD)
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) (NULL)

#endif // MULTI_HEAP_FREERTOS


//=======
// Using
//=======

#include <multi_heap.h>
#include <stdbool.h>


//===========
// Alignment
//===========

#define SIZE_BITS (sizeof(size_t)*8)
#define SIZE_BYTES sizeof(size_t)

#define BLOCK_SIZE_MIN (3*SIZE_BYTES)

inline static size_t multi_heap_align_down(size_t value, size_t align)
{
return value&~(align-1);
}

inline static size_t multi_heap_align_up(size_t value, size_t align)
{
return (value+align-1)&~(align-1);
}
