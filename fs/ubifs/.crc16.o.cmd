cmd_fs/ubifs/crc16.o := arm-none-linux-gnueabi-gcc -Wp,-MD,fs/ubifs/.crc16.o.d  -nostdinc -isystem /home/damien/prj-odf/cross-compile/arm-4.3.2/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.2/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -Wno-format-nonliteral -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -fno-pic -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv5te -D__LINUX_ARM_ARCH__=5    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(crc16)"  -D"KBUILD_MODNAME=KBUILD_STR(crc16)" -c -o fs/ubifs/crc16.o fs/ubifs/crc16.c

source_fs/ubifs/crc16.o := fs/ubifs/crc16.c

deps_fs/ubifs/crc16.o := \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/use/stdint.h) \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  arch/arm/include/asm/posix_types.h \
  arch/arm/include/asm/types.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/phys/64bit.h) \
    $(wildcard include/config/dma/addr/t/64bit.h) \
  /home/damien/prj-odf/cross-compile/arm-4.3.2/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.2/include/stdbool.h \
  fs/ubifs/crc16.h \

fs/ubifs/crc16.o: $(deps_fs/ubifs/crc16.o)

$(deps_fs/ubifs/crc16.o):
