#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

ifdef CONFIG_SPL_BUILD
obj-$(CONFIG_USE_IRQ) += interrupts.o
else
obj-$(CONFIG_USE_IRQ) += interrupts.o
obj-$(CONFIG_DISPLAY_CPUINFO)	+= cpu_info.o
obj-y	+= speed.o
obj-y	+= timer.o
endif
