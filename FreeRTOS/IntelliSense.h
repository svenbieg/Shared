//================
// IntelliSense.h
//================

#pragma once


//========
// Common
//========

#define __asm__ __asm
#define __attribute__(a)
#define __builtin_bswap16(x) x
#define __builtin_offsetof(t, m) ((SIZE_T)&((t*)0)->m)
#define __builtin_va_end
#define __builtin_va_list
#define __builtin_va_start

#define _HAVE_STDC 1

#define PROJECT_VER "0"

#define configTICK_RATE_HZ 1

inline VOID setenv(LPSTR Variable, LPSTR Value, BOOL Overwrite) {}
