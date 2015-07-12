#
# Copyright 2015, Wink Saville
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.

apps-$(CONFIG_APP_MYASSERT) += myassert

# LIbraries needed
myassert-y = libsel4 libsel4putchar libsel4printf libsel4assert libsel4startstop

myassert: kernel_elf $(myassert-y)
