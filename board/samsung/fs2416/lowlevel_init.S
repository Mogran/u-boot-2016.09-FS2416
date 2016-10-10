/*
 * FS2416 memory configuration
 * 
 * 0.配置系统时钟，使能各模块单元时钟，为初始化ddr2内存做准备
 * 1.初始化ddr2内存，初始化nandflash
 * 2.为接下来的拷贝u-boot到内存中做准备
 */
#include <config.h>

#define WDTCON   0x53000000
#define INTMSK1  0x4A000008
#define INTMSK2  0x4A000048
#define LOCKCON0 0x4C000000
#define LOCKCON1 0x4C000004
#define MPLLCON  0x4C000010
#define EPLLCON  0x4C000018
#define CLKSRC   0x4C000020
#define CLKDIV0  0x4C000024
#define CLKDIV1  0x4C000028
#define CLKDIV2  0x4C00002C
#define HCLKCON  0x4C000030
#define PCLKCON  0x4C000034 
#define NFCONF   0x4E000000
#define NFCONT   0x4E000004
#define GPBCON   0x56000010
#define GPBDAT   0x56000014
#define GPBUDP   0x56000018

#define BANKCFG0REG	0x48000000 
#define BANKCON1REG	0x48000004 
#define BANKCON2REG	0x48000008 
#define BANKCON3REG	0x4800000C 
#define REFRESHREG  0x48000010

.globl lowlevel_init

lowlevel_init:
	ldr r0, =WDTCON
	mov r1, #0
	str r1, [r0]

	ldr r0, =INTMSK1
	ldr r1, =0xffffffff
	str r1, [r0]

	ldr r0, =INTMSK2
	ldr r1, =0xffffffff 
	str r1, [r0]

	ldr r0, =CLKDIV0
	ldr r1, =0x0000022d
	str r1, [r0]

	ldr r0, =HCLKCON
	ldr r1, =0xffffffff
	str r1, [r0]

	ldr r0, =PCLKCON
	ldr r1, =0xffffffff
	str r1, [r0]

	ldr r0, =MPLLCON
	ldr r1, =(0 << 24)+(400 << 14)+(3 << 5)+(1 << 0)
	str r1, [r0]

	ldr r0, =EPLLCON
	ldr r1, =(0 << 24)+(32 << 16)+(1 << 8)+(2 << 0)
	str r1, [r0]

	ldr r0, =LOCKCON0
	ldr r1, =3600
	str r1, [r0]

	ldr r0, =LOCKCON1
	ldr r1, =3600
	str r1, [r0]

	ldr r0, =CLKSRC
	ldr r1, =(1 << 6)+(1 << 4)
	str r1, [r0]

	mov r2, #0x10000 @wait until clock stablize all clock.
1:  subs r2, r2, #1
	bne 1b

#	DDR2 initialization

	ldr r0, =BANKCFG0REG @BANKCFG
	ldr r1, =(2<<17)+(2<<14)+(2<<11)+(2<<8)+(1<<1)+(1<<0)
	str r1, [r0]

	ldr r0, =BANKCON1REG
	ldr r1, =(3<<28)+(1<<26)+(1<<8)+(0<<7)+(1<<6)+(0<<5)+(1<<4)
	str r1, [r0]

	ldr r0, =BANKCON2REG
	ldr r1, =(6<<20)+(14<<16)+(2<<4)+(2<<2)+(2<<0)
	str r1, [r0]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x1<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #(BA_EMRS2<<30)
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #(BA_EMRS3<<30)
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r4, =((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_EXIT<<23)+(DLL_EN<<16))

	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, r4
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #((BA_MRS<<14)+(DLL_RESET_HIGH<<8)+(TM<<7)+(CL_MRS<<4))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x2<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x1<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =0x20
	str	r0, [r4]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, #((BA_MRS<<14)+(DLL_RESET_LOW<<8)+(TM<<7)+(CL_MRS<<4))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x2<<0)
	str	r1, [r2]

	mov	r0, #0x100
2:
	subs	r0, r0, #1
	bne	2b

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r4, =((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, r4	@((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r2, =BANKCON3REG
	ldr	r3, =0xFFFF0000
	ldr	r4, =((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_EXIT<<23)+(DLL_EN<<16))
	ldr	r1, [r2]
	bic	r1, r1, r3
	orr	r1, r1, r4	@((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
	str	r1, [r2]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	orr	r1, r1, #(0x3<<0)
	str	r1, [r2]

	ldr	r4, =REFRESHREG
	ldr	r0, =REFCYC
	str	r0, [r4]

	ldr	r2, =BANKCON1REG
	ldr	r1, [r2]
	bic	r1, r1, #(0x3<<0)
	str	r1, [r2]

#   OPEN LED1
	ldr r0, =GPBCON
	mov r1, #0x0
    ldr r1, =(1<<6)|(1<<18) @configure GPB3 and GPB9 output mode
	str r1, [r0]

	ldr r0, =GPBUDP
	ldr r1, [r0]
	bic r1, r1, #(1 << 6)
	orr r1, r1, #(1 << 7)  @configure GPB3's pullup
	bic r1, r1, #(1 << 18)
	orr r1, r1, #(1 << 19) @confgure GPB9's puiiup
	str r1, [r0]

	ldr r0, =GPBDAT
	ldr r1, [r0]
	bic r1, r1, #(1 << 3) @open led3
	orr r1, r1, #(1 << 9) @don't open led9
	str r1, [r0]

	/* everything is fine now */
	mov	pc, lr


