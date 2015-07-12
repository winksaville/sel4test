#
# Copyright 2015, Wink Saville
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.

apps-$(CONFIG_APP_BOOTINFO) += bootinfo

# Libraries needed
bootinfo-y = libsel4 libsel4putchar libsel4printf libsel4startstop

bootinfo: kernel_elf $(bootinfo-y)
