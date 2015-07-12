/*
 * Copyright 2015, Wink Saville
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 */

#include <sel4/sel4.h>
#include <sel4/assert.h>
#include <sel4/printf.h>

volatile seL4_Uint32 volatile0 = 0;

/**
 * No parameters are passed to main, the return
 * value is ignored and the program hangs.
 */
int main(void) {
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

    // These should always succeed
    seL4_CompileTimeAssert(0 == 0);
    seL4_Assert(0 == 0);
    seL4_Assert(volatile0 == 0);
    seL4_DebugAssert(0 == 0);
    seL4_DebugAssert(volatile0 == 0);

    // Test seL4_Fail
    seL4_Fail("Assert app done");

    return 0;
}
