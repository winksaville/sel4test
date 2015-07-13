/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

//#include <sel4/sel4.h>
#include <sel4/string.h>
#include <sel4/printf.h>
#include <sel4/debug_printf.h>
#include <sel4/assert.h>
#include <sel4/debug_assert.h>
#include <sel4/putchar.h>
#include <sel4/bootinfo.h>
#include <sel4/stop.h>

#include <sel4test/test.h>
#include <sel4utils/benchmark.h>

int test_strlen(env_t env, void *arg)
{
    test_assert(seL4_StrLen(seL4_Null) == 0);
    test_assert(seL4_StrLen("") == 0);
    test_assert(seL4_StrLen("1") == 1);
    test_assert(seL4_StrLen("\n") == 1);
    test_assert(seL4_StrLen("12") == 2);
    return SUCCESS;
}
DEFINE_TEST(STRLEN0000, "Test seL4_StrLen", test_strlen)

int test_strncmp(env_t env, void *arg)
{
    char *str1 = "str1";
    char *str2 = "str2";
    test_assert(seL4_StrNCmp(seL4_Null, seL4_Null, 0) == 0);
    test_assert(seL4_StrNCmp(str1, seL4_Null, 0) == 0);
    test_assert(seL4_StrNCmp(seL4_Null, str1, 0) == 0);
    test_assert(seL4_StrNCmp(str1, str1, 4) == 0);
    test_assert(seL4_StrNCmp(str1, str2, 3) == 0);
    test_assert(seL4_StrNCmp(str1, str2, 4) < 0);
    test_assert(seL4_StrNCmp(str2, str1, 4) > 0);
    return SUCCESS;
}
DEFINE_TEST(STRNCMP0000, "Test seL4_StrNCmp", test_strncmp)

int test_putchar(env_t env, void *arg) {
    // Just verify we can call it.
    seL4_PutChar('h');
    seL4_PutChar('i');
    seL4_PutChar('\n');
    return SUCCESS;
}
DEFINE_TEST(PUTCHAR0000, "Test seL4_PutChar", test_putchar)

volatile seL4_Int32 volatile0 = 0;

int test_simple_types(env_t env, void *arg) {
    seL4_Int8 i8 = 1;
    test_assert(i8 == 1);
    test_assert(sizeof(i8) == 1);
    seL4_Int16 i16 = 2;
    test_assert(i16 == 2);
    test_assert(sizeof(i16) == 2);
    seL4_Int32 i32 = 3;
    test_assert(i32 == 3);
    test_assert(sizeof(i32) == 4);
    seL4_Int64 i64 = 4;
    test_assert(i64 == 4);
    test_assert(sizeof(i64) == 8);

    seL4_Uint8 u8 = 1;
    test_assert(u8 == 1);
    test_assert(sizeof(u8) == 1);
    seL4_Uint16 u16 = 2;
    test_assert(u16 == 2);
    test_assert(sizeof(u16) == 2);
    seL4_Uint32 u32 = 3;
    test_assert(u32 == 3);
    test_assert(sizeof(u32) == 4);
    seL4_Uint64 u64 = 4;
    test_assert(u64 == 4);
    test_assert(sizeof(u64) == 8);

    seL4_Uint8 *p = seL4_Null;
    test_assert(p == seL4_Null);

    return SUCCESS;
}
DEFINE_TEST(SIMPLETYPES0000, "Test seL4 simple types", test_simple_types)

int test_sel4_assert(env_t env, void *arg) {
    /*
     * Manually test these compile time errors by enabling both
     * and the compilation should fail.
     */
    //seL4_CompileTimeAssert(1 == 0);
    //seL4_CompileTimeAssert(volatile0 == 0);

    /*
     * Manually test these runtime errors, enable one at a time
     * and compile and run, each statement should fail.
     */
    //seL4_Fail("failing");
    //seL4_Assert(0 == 1);
    //seL4_Assert(volatile0 == 1);
    //seL4_DebugAssert(1 == 2);

    /*
     * Manually uncomment the statement below and in .config
     * set CONFIG_USER_DEBUG_BUILD=y this causes NDEBUG to NOT
     * be defined. Compile and run and you should see a runtime
     * error.
     *
     * Next set CONFIG_USER_DEBUG_BUILD=n recompile and rerun.
     * The statement will NOT fail because NDEBUG is now defined.
     * This verifies seL4_DebugAssert compiles to a NOP when
     * NDEBUG is defined.
     */
    //seL4_DebugAssert(volatile0 == 2);

    seL4_Assert(0 == 0);
    seL4_Assert(volatile0 == 0);
    seL4_DebugAssert(0 == 0);
    seL4_DebugAssert(volatile0 == 0);
    seL4_CompileTimeAssert(0 == 0);
    seL4_Bool b = seL4_True;
    seL4_Assert(b != seL4_False);

    return SUCCESS;
}
DEFINE_TEST(SEL4ASSERT0000, "Test seL4_Assert", test_sel4_assert)


#ifdef CONFIG_BENCHMARK
int test_benchmark(env_t env, void *arg) {
    seL4_BenchmarkResetLog();
    seL4_BenchmarkDumpFullLog();
    return SUCCESS;
}
DEFINE_TEST(BENCHMARK0000, "Test sel4utils/benchmark.h", test_benchmark)
#else // CONFIG_BENCHMARK is not defined
#pragma message "In " __FILE__ " CONFIG_BENCHMARK is not defined. Edit .config setting 'CONFIG_BENCHMARK=y'"
#endif // CONFIG_BENCHMARK

#ifdef TEST_BOOTINFO
// Test BootInfo if it gets initialized, currently it isn't
int test_bootinfo(env_t env, void *arg) {
    seL4_BootInfo *bi = seL4_GetBootInfo();
    test_assert(bi != seL4_Null);
    test_assert(bi->nodeID == 1);
    return SUCCESS;
}
DEFINE_TEST(BOOTINFO0000, "Test seL4_BootInfo", test_bootinfo)
#endif

typedef struct {
    int idx;
    char buff[256];
} Buffer;

/**
 * writeBeg called before first writeCharToBuff
 */
static void writeBeg(seL4_Writer* this) {
    Buffer *pBuffer = (Buffer*)this->data;
    pBuffer->idx = 0;
}

/**
 * writeEnd called after the last writeCharToBuff
 */
static void writeEnd(seL4_Writer* this) {
    Buffer *pBuffer = (Buffer*)this->data;
    pBuffer->buff[pBuffer->idx] = 0;
}

/**
 * Write a character to the buffer
 */
static void writeCharToBuff(seL4_Writer* this, void* param) {
    Buffer *pBuffer = (Buffer*)this->data;
    char ch = ((char)(((int)param) & 0xff));
    pBuffer->buff[pBuffer->idx++] = ch;
    if (pBuffer->idx >= sizeof(pBuffer->buff)) {
        pBuffer->idx = 0;
    }
}

#define __TEST_PRINTING_RESULT() \
    if (buffer.idx != seL4_StrLen(expected)) { \
        seL4_Printf("buff:%s != expected:%s idx=%d\n", buffer.buff, expected, buffer.idx); \
        test_assert(buffer.idx == seL4_StrLen(expected)); \
    } \
    if (seL4_StrNCmp(expected, buffer.buff, buffer.idx) != 0) { \
        seL4_Printf("buff:%s != expected:%s idx=%d\n", buffer.buff, expected, buffer.idx); \
        test_assert(seL4_StrNCmp(expected, buffer.buff, buffer.idx) == 0); \
    } \

#define TEST_PRINTING_NO_PARAM(formatting, expectedVal) \
    do { \
        const char *expected = expectedVal; \
        seL4_WPrintf(&writer, formatting); \
        __TEST_PRINTING_RESULT(); \
    } \
    while(0)

#define TEST_PRINTING(formatting, param, expectedVal) \
    do { \
        const char *expected = expectedVal; \
        seL4_WPrintf(&writer, formatting, param); \
        __TEST_PRINTING_RESULT(); \
    } \
    while(0)

int test_printf(env_t env, void *arg) {
    seL4_Printf("Hello, World\n");
    seL4_DebugPrintf("Hello, World: via seL4_DebugDrintf\n");

    // Define a buffer and a writer for testing printf
    Buffer buffer;
    seL4_Writer writer = {
            .writeBeg = writeBeg,
            .writeParam = writeCharToBuff,
            .writeEnd = writeEnd,
            .data = &buffer
    };

    TEST_PRINTING_NO_PARAM("Hello", "Hello");
    TEST_PRINTING_NO_PARAM("%", "");
    TEST_PRINTING_NO_PARAM("%1", "%1");
    TEST_PRINTING_NO_PARAM("%%", "%");

    TEST_PRINTING("%s", "string", "string");
    TEST_PRINTING("%b", 0, "0");
    TEST_PRINTING("%b", 0x87654321, "10000111011001010100001100100001");
    TEST_PRINTING("%b", 0xFFFFFFFF, "11111111111111111111111111111111");

    TEST_PRINTING("%d", 1, "1");
    TEST_PRINTING("%d", 0x7FFFFFFF, "2147483647");
    TEST_PRINTING("%d", 0x80000000, "-2147483648");
    TEST_PRINTING("%d", 0x80000001, "-2147483647");
    TEST_PRINTING("%d", 0xFFFFFFFF, "-1");
    TEST_PRINTING("%d", -1, "-1");

    TEST_PRINTING("%u", 2, "2");
    TEST_PRINTING("%u", 0x7FFFFFFF, "2147483647");
    TEST_PRINTING("%u", 0x80000000, "2147483648");
    TEST_PRINTING("%u", 0x80000001, "2147483649");
    TEST_PRINTING("%u", 0xFFFFFFFF, "4294967295");
    TEST_PRINTING("%u", -1, "4294967295");

    TEST_PRINTING("%x", 0, "0");
    TEST_PRINTING("%x", 9, "9");
    TEST_PRINTING("%x", 10, "a");
    TEST_PRINTING("%x", 15, "f");
    TEST_PRINTING("%x", 16, "10");
    TEST_PRINTING("0x%x", 0x12345678, "0x12345678");
    TEST_PRINTING("0x%x", 0x9abcdef0, "0x9abcdef0");

    TEST_PRINTING_NO_PARAM("%l", "%l");
    TEST_PRINTING_NO_PARAM("%la", "%la");
    TEST_PRINTING_NO_PARAM("%ll", "%ll");
    TEST_PRINTING_NO_PARAM("%llz1", "%llz1");

    TEST_PRINTING("%llx", 0ll, "0");
    TEST_PRINTING("%llx", 9ll, "9");
    TEST_PRINTING("%x", 10ll, "a");
    TEST_PRINTING("%x", 15ll, "f");
    TEST_PRINTING("%llx", 16ll, "10");

    // Test we are "filling" zeros correctly as we print using writeUint32 twice
    TEST_PRINTING("%llx", 0x80000000ll, "80000000");
    TEST_PRINTING("%llx", 0x800000000ll, "800000000");
    TEST_PRINTING("%llx", 0x800000000000ll, "800000000000");
    TEST_PRINTING("%llx", 0x80000000000000ll, "80000000000000");
    TEST_PRINTING("%llx", 0x8000000000000000ll, "8000000000000000");
    TEST_PRINTING("%llx", 0x8000000000000001ll, "8000000000000001");

    TEST_PRINTING("%llx", 0xFEDCBA9876543210ll, "fedcba9876543210");
    TEST_PRINTING("%llx", 0x7fffffffffffffffll, "7fffffffffffffff");
    TEST_PRINTING("%llx", -1ll,                 "ffffffffffffffff");

    void *pv = (void *)0xf7654321;
    TEST_PRINTING("%p", pv, "f7654321");

    return SUCCESS;
}
DEFINE_TEST(PRINTF0000, "Test seL4_Printf", test_printf)
