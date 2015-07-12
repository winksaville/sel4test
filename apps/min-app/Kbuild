#
# Copyright 2015, Wink Saville
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.

apps-$(CONFIG_APP_MIN_APP) += min-app

# Libraries needed
min-app-y = libsel4 libsel4startstop

min-app: kernel_elf $(min-app-y)
