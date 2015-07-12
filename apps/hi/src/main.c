/*
 * Copyright 2015, Wink Saville
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 */

#include <sel4/putchar.h>

/**
 * No parameters are passed to main, the return
 * value is ignored and the program hangs.
 */
int main(void) {
  seL4_PutChar('h');
  seL4_PutChar('i');
  seL4_PutChar('\n');

  return 0;
}
