/*
 * @description : FS2416 memory configuration file
 * @author      : <lumingliang.github@gmail.com>
 * @date        : 2016-10-09
 * @other:
 * 		0.配置系统时钟，使能各模块单元时钟，为初始化ddr2内存做准备
 * 		1.初始化ddr2内存，初始化nandflash
 * 		2.为接下来的拷贝u-boot到内存中做准备
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

#define BANKCFG_REG		0x48000000 
#define BANKCON1_REG	0x48000004 
#define BANKCON2_REG	0x48000008 
#define BANKCON3_REG	0x4800000C 
#define REFRESH_REG  	0x48000010

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
	
	/* Step 1: BANKCFG Seting */
	ldr r0, =BANKCFG_REG
	ldr r1, =BANKCFG_VAL
	str r1, [r0]
	
	ldr r0, =BANKCON1_REG
	ldr r1, =BANKCON1_VAL
	str r1, [r0]

	/* Step 2: BANKCON2 Seting */
	ldr r0, =BANKCON2_REG
	ldr r1, =BANKCON2_VAL
	str r1, [r0]

	/* Step 3: issue PALL */
	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	orr	r1, r1, #1
	str	r1, [r0]

	/* Step 4: issue a EMRS2 command */
	ldr r2, =0x80000000
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #3
	str	r1, [r0]

	/* Step 5: issue a EMRS3 command */
	ldr r2, =0xC0000000
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #3
	str	r1, [r0]

	/* Step 6: issue a EMRS1 command */
	ldr r2, =0x44000000
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #3
	str	r1, [r0]

	/* Step 7: issue a MRS command */
	ldr r2, =0x44000130
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #2
	str	r1, [r0]

	/* Step 8: issue PALL */
	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	orr	r1, r1, #1
	str	r1, [r0]

	/* Step 9: write 0xff into the refresh timer */
	ldr r0, =REFRESH_REG
	mov r1, #0xff
	str r1, [r0]

	/* Step 10: wait more than 120 clk */
	mov r3, #0x100
10 :
	subs r3, r3, #1
	bne 10b

	/* The next steps will excute OCD Calibration*/
	/* Step 11: issue MRS */
	ldr r2, =0x44000030
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #2
	str	r1, [r0]

	/* Step 12: issue a EMRS1 command */
	ldr r2, =0x47800030
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #3
	str	r1, [r0]

	ldr r2, =0x44000030
	ldr r3, =BANKCON3_REG
	str r2, [r3]

	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	orr	r1, r1, #3
	str	r1, [r0]

	/* Step 13: write 1037 into refresh timer */
	ldr r0, =REFRESH_REG
	ldr r1, =1037
	str r1, [r0]

	/* Step 14: write back Normal mode */
	ldr r0, =BANKCON1_REG
	ldr r1, [r0]
	bic r1, r1, #3
	str	r1, [r0]

# OPEN LED1
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

# DDR2 init test, if init success,return back or jump into infinte loop	
	ldr r6, =(PHYS_SDRAM_1+0x4)
	ldr r7, =0x24564236 @write a randam integer
	swp r8, r7, [r6]
	swp r5, r8, [r6]
	cmp r7, r5
	bne 1002f		



# Nand asm init
	ldr r0, =NFCONF
	ldr r2, =(0<<12)|(2<<8)|(1<<4)|(1<<1)
	str r2, [r0]	

	ldr r0, =NFCONT
	ldr r2, =(2<<12)|(1<<1)|(1<<0)
	str r2, [r0]	


	/* everything is fine now */
	mov	pc, lr

1002:
	ldr r1, =0x56000014 @0x56000014 this is GPBDAT register
	ldr r2, [r1]
	bic r2, r2, #(1 << 9)
	str r2, [r1]
0: 	
	b 0b
