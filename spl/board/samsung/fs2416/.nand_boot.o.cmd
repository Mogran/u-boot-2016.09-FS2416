cmd_spl/board/samsung/fs2416/nand_boot.o := arm-none-linux-gnueabi-gcc -Wp,-MD,spl/board/samsung/fs2416/.nand_boot.o.d  -nostdinc -isystem /home/damien/prj-odf/cross-compile/arm-4.3.2/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.2/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -DCONFIG_SPL_BUILD -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -Wno-format-nonliteral -ffunction-sections -fdata-sections -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv5te -D__LINUX_ARM_ARCH__=5    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nand_boot)"  -D"KBUILD_MODNAME=KBUILD_STR(nand_boot)" -c -o spl/board/samsung/fs2416/nand_boot.o board/samsung/fs2416/nand_boot.c

source_spl/board/samsung/fs2416/nand_boot.o := board/samsung/fs2416/nand_boot.c

deps_spl/board/samsung/fs2416/nand_boot.o := \

spl/board/samsung/fs2416/nand_boot.o: $(deps_spl/board/samsung/fs2416/nand_boot.o)

$(deps_spl/board/samsung/fs2416/nand_boot.o):
