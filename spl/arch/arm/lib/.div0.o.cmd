cmd_spl/arch/arm/lib/div0.o := arm-none-linux-gnueabi-gcc -Wp,-MD,spl/arch/arm/lib/.div0.o.d  -nostdinc -isystem /home/damien/prj-odf/cross-compile/arm-4.3.2/bin/../lib/gcc/arm-none-linux-gnueabi/4.3.2/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -DCONFIG_SPL_BUILD -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -Wno-format-nonliteral -ffunction-sections -fdata-sections -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv5te -D__LINUX_ARM_ARCH__=5    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(div0)"  -D"KBUILD_MODNAME=KBUILD_STR(div0)" -c -o spl/arch/arm/lib/div0.o arch/arm/lib/div0.c

source_spl/arch/arm/lib/div0.o := arch/arm/lib/div0.c

deps_spl/arch/arm/lib/div0.o := \

spl/arch/arm/lib/div0.o: $(deps_spl/arch/arm/lib/div0.o)

$(deps_spl/arch/arm/lib/div0.o):
