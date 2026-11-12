// Copyright 2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/**
 * @file unity_xcore.h
 * @brief XCORE support for Unity: function pointer groups for the test functions.
 *
 * The Unity fixture calls each test's setup, body and teardown through function
 * pointers (UnityTestRunner), so the linker cannot see which functions it calls
 * and cannot work out its stack usage. Putting those functions and the pointers
 * in one fptrgroup tells the linker exactly which functions can be called, so
 * the stack of every test body is included in the stack calculation.
 *
 * Included by unity_internals.h. On other compilers the macros expand to nothing.
 * Applications may override macros protected by `#ifndef` before Unity headers
 * are included.
 */
#ifndef UNITY_XCORE_H
#define UNITY_XCORE_H

/**
 * @def UNITY_HAS_FPTRGROUP
 * @brief Indicates whether the compiler supports the `fptrgroup` attribute.
 */
#ifndef UNITY_HAS_FPTRGROUP
#if defined(__xcore__) || defined(__riscv_xxcore)
#define UNITY_HAS_FPTRGROUP 1
#else
#define UNITY_HAS_FPTRGROUP 0
#endif
#endif

/**
 * @def UNITY_FPTR_GROUP
 * @brief Puts a test function, or a pointer that calls test functions, in the
 *        Unity test function group. Expands to nothing on other compilers.
 */
#ifndef UNITY_FPTR_GROUP
#if UNITY_HAS_FPTRGROUP
#define UNITY_FPTR_GROUP __attribute__((fptrgroup("unity_test_fns")))
#else
#define UNITY_FPTR_GROUP
#endif
#endif

#endif // UNITY_XCORE_H
