#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

extra-y	= start.o
obj-y	= cpu.o cache.o

obj-$(CONFIG_ARMADA100) += armada100/
obj-$(CONFIG_S3C2416) += s3c2416/
obj-$(if $(filter lpc32xx,$(SOC)),y) += lpc32xx/
obj-$(CONFIG_MX25) += mx25/
obj-$(CONFIG_MX27) += mx27/
obj-$(if $(filter mxs,$(SOC)),y) += mxs/
obj-$(if $(filter spear,$(SOC)),y) += spear/

# some files can only build in ARM or THUMB2, not THUMB1

ifdef CONFIG_SYS_THUMB_BUILD
ifndef CONFIG_HAS_THUMB2

CFLAGS_cpu.o := -marm
CFLAGS_cache.o := -marm

endif
endif
