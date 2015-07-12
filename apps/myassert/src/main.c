/*
 * Copyright 2015, Wink Saville
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 */

/**
 * This tests overriding _seL4_Fail and _seL4_AssertFail
 */
#include <sel4/sel4.h>
#include <sel4/assert.h>
#include <sel4/printf.h>
#include <sel4/stop.h>

void __assert_fail(const char* s, const char* file, int line, const char*  function) {
    seL4_Printf("My __asert_fail called at %s:%u in function %s with '%s'\n",
        file, line, function, s);
    seL4_Stop();
}

volatile seL4_Uint32 volatile0 = 0;

/**
 * No parameters are passed to main, the return
 * value is ignored and the program hangs.
 */
int main(void) {
    // Enable one at a time test a runtime assert
    //seL4_Assert(0 == 1);
    //seL4_Assert(volatile0 == 1);

    // These should always succeed
    seL4_CompileTimeAssert(0 == 0);
    seL4_Assert(0 == 0);
    seL4_Assert(volatile0 == 0);

    // If the above statement does not fail then this always fails.
    seL4_Fail("Assert app done, NDEBUG is defined");

    return 0;
}
