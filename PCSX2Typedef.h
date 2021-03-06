#pragma once

#include <stdint.h>

// --------------------------------------------------------------------------------------
//  Basic Atomic Types
// --------------------------------------------------------------------------------------

// Note: char does not have a default sign, unlike other types. As we actually want
// char and not signed char in pcsx2, we define s8 to char

typedef char s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uintptr_t uptr;
typedef intptr_t sptr;

typedef uint64_t uint64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int64_t int64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;

typedef unsigned int uint;

typedef u32(CALLBACK* _PS2EgetLibType)(void);
typedef u32(CALLBACK* _PS2EgetLibVersion2)(u32 type);
typedef char* (CALLBACK* _PS2EgetLibName)(void);
typedef uint32_t (CALLBACK* _PS2EgetCpuPlatform)(void);

#define RESTRICT
#define ASSERT assert
