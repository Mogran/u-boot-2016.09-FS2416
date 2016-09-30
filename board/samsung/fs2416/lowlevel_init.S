/*
 * FS2416 memory configuration
 *
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
#define BANKCFG	 0x48000000

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
	ldr r0, =BANKCFG @BANKCFG
	ldr r1, =(2<<17)+(2<<14)+(2<<11)+(2<<8)+(1<<1)+(1<<0)
	str r1, [r0, #0x0]

#   BANKCON1
	ldr r1, =(3<<28)+(1<<26)+(1<<8)+(0<<7)+(1<<6)+(0<<5)+(1<<4)
	str r1, [r0, #0x4]

#  BANKCON2
	ldr r1, =(6<<20)+(14<<16)+(2<<4)+(2<<2)+(2<<0)
	str r1, [r0, #0x8]

#  issue a PALL CMD to DRAMC
	ldr r1, [r0, #0x4]
	bic r1, r1, #0x3
	orr r1, r1, #0x1
	str r1, [r0, #0x4]

#  issue a CMD to EMR(2)	
	ldr r1, =(2<<30)+(0<<23)+(0<<19)+(0<<16)
	str r1, [r0, #0x0c]

	ldr r1, [r0, #0x4]
	orr r1, r1, #0x3
	str r1, [r0, #0x4]

#  issue a cmd EMR(3)
	ldr r1, =(3<<30)
	str r1, [r0, #0x0c]

	ldr r1, [r0, #0x4]
	orr r1, r1, #0x3
	str r1, [r0, #0x4]

#  enable DLL, RDQS, nDQS, ODT disable
	ldr r1, =0xffff0000 
	ldr r2, [r0, #0x0c]
	bic r2, r2, r1
	
	ldr r1,=(1<<30)+(0<<28)+(0<<27)+(1<<26)+(7<<23)+(0<<19)+(0<<18)+(0<<17)+(0<<16)
	orr r1, r1, r2	
	str r1, [r0, #0x0c]

	ldr r1, [r0, #0x4]
	orr r1, r1, #0x3
	str r1, [r0, #0x4]

#  issue a mode set command to Mode register for DLL reset 
	ldr r1, =0x0000ffff 
	ldr r2, [r0, #0x0c]
	bic r2, r2, r1
	
	ldr r1,=(1<<9)+(1<<8)+(0<<7)+(3<<4)
	orr r1, r1, r2	
	str r1, [r0, #0x0c]

	ldr r1, [r0, #0x4]
	bic r1, r1, #0x3
	orr r1, r1, #0x2
	str r1, [r0, #0x4]

#  issue a PLL command
	ldr r1, [r0, #0x4]
	bic r1, r1, #0x3
	orr r1, r1, #0x1
	str r1, [r0, #0x4]

#  issue a refresh cmd 
	ldr r1, =0x20
	str r1, [r0, #0x10]

#  issue a MRS command  
	ldr r1, =0x0000ffff 
	ldr r2, [r0, #0x0c]
	bic r2, r2, r1
	
	ldr r1,=(1<<9)+(0<<8)+(0<<7)+(3<<4)
	orr r1, r1, r2	
	str r1, [r0, #0x0c]

	ldr r1, [r0, #0x4]
	bic r1, r1, #0x3
	orr r1, r1, #0x2
	str r1, [r0, #0x4]

#wait 200 clock period.
	mov r2, #200
1:  subs r2, r2, #1
	bne 1b

#  excute OCD Calibration
	ldr r1, =0xffff0000 
	ldr r2, [r0, #0x0c]
	bic r2, r2, r1
	
	ldr r1,=(1<<30)+(0<<28)+(0<<27)+(1<<26)+(0<<23)+(0<<19)+(0<<18)+(0<<17)+(0<<16)
	orr r1, r1, r2	
	str r1, [r0, #0x0c]

	ldr r1, [r0, #0x4]
	orr r1, r1, #0x3
	str r1, [r0, #0x4]


#  set refresh cycle ,K4T51163QJ-BCE7's tREFI=7.8us (0~85 degree) 
	ldr r1, =1038
	str r1, [r0, #0x10]

#  issue normal work command
	ldr r1, [r0, #0x4]
	bic r1, r1, #0x3
	str r1, [r0, #0x4]

	/* everything is fine now */
	mov	pc, lr


