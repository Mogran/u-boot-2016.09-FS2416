/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <garyj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK2410 board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_S3C24X0		/* This is a SAMSUNG S3C24x0-type SoC */
#define CONFIG_S3C2416		/* specifically a SAMSUNG S3C2416 SoC */
#define CONFIG_FS2416		/* on a SAMSUNG FS2416 Board */

#define CONFIG_SYS_ARM_CACHE_WRITETHROUGH

/* input clock of PLL (the FS2416 has 12MHz input clock) */
#define CONFIG_SYS_CLK_FREQ	12000000

#define CONFIG_CMDLINE_TAG	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/*
 * Hardware drivers
 */
#if 0
#define CONFIG_CS8900		/* we have a CS8900 on-board */
#define CONFIG_CS8900_BASE	0x19000300
#define CONFIG_CS8900_BUS16	/* the Linux driver does accesses as shorts */
#endif
/*
 * select serial console configuration
 */
#define CONFIG_S3C24X0_SERIAL
#define CONFIG_SERIAL1		0	/* we use SERIAL 1 on SMDK2410 */
#define CONFIG_BAUDRATE		115200

/************************************************************
 * USB support (currently only works with D-cache off)
 ************************************************************/
#if 0
#define CONFIG_USB_OHCI
#define CONFIG_USB_OHCI_S3C24XX
#define CONFIG_USB_KEYBOARD
#define CONFIG_DOS_PARTITION
#endif
/************************************************************
 * RTC
 ************************************************************/
#if 0
#define CONFIG_CMD_DATE
#define CONFIG_RTC_S3C24X0
#endif

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/*
 * Command line configuration.
 */

#define CONFIG_CMD_BSP
#define CONFIG_CMD_REGINFO
#define CONFIG_CMDLINE_EDITING
#define CONFIG_BOOT_RETRY_TIME	3
#define CONFIG_RESET_TO_RETRY

#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.8.221
#define CONFIG_SERVERIP		192.168.8.219

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port */
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_CBSIZE	256
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
				sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#define CONFIG_DISPLAY_CPUINFO				/* Display cpu info */
#define CONFIG_SYS_MEMTEST_START	0x30000000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x33F00000	/* 63 MB in DRAM */
#define CONFIG_SYS_LOAD_ADDR		0x30008000

/* support additional compression methods */
#define CONFIG_BZIP2
#define CONFIG_LZO
#define CONFIG_LZMA

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	2          /* we have 2 bank of DDR2 RAM */
#define PHYS_SDRAM_1		0x30000000     /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000     /* 32 MB * 16 = 64Mb */
#define PHYS_SDRAM_2		0x38000000     /* SDRAM Bank #2 */
#define PHYS_SDRAM_2_SIZE	0x04000000     /* 32 MB * 16 = 64Mb */ 

/*---------------------------------------
 *BANKCONFIG register  : DDR2 SDRAM configure
 */
#define RASBW0							2			/*	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit */
#define RASBW1							2			/*	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit */
#define CASBW0							2			/*	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit */
#define CASBW1							2			/*	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit */
#define ADDRCFG0						1			/* 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS} */
#define ADDRCFG1						1			/* 	addre configure 00={BA,RAS,CAS}, 01={RAS,BA,CAS} */
#define MEMCFG							1			/* 	Ext.Mem 000=SDR,010=MSDR,100=DDRz,110=MDDR,001=DDR2 */
#define BW								1			/* 	Bus width 00=32bit,01=16bit */

/*---------------------------------------
 * BANKCON1 register : DDR2 SDRAM timing control
 */
#define PADLOAD							1
#define BStop							0			//	read burst stop control
#define WBUF							1			//	write buffer control
#define AP								0			//	enable auto precharge control
#define PWRDN							1			//	support power down mode
#define DQSDelay						4			//	DQS delay

/*---------------------------------------
 * BANKCON2 register : DDR2 SDRAM timing control
 */
#define tRAS							5			//	Row active time
#define tARFC							13			//	Row cycle time
#define CL								3			//	CAS latency control
#define tRCD							1			//	RAS to CAS delay
#define tRP								1			// 	Row pre-charge time

/*---------------------------------------
 * BANKCON3 register : DDR2 SDRAM MRS/EMRS register
 */
#define BA_EMRS1						1			//	BA : EMRS
#define DLL_DIS							1
#define DLL_EN							0
#define nDQS_DIS						1
#define RDQS_DIS						0
#define OCD_MODE_EXIT					0
#define OCD_MODE_DEFAULT				7
#define BA_EMRS2						2			//	BA : EMRS
#define BA_EMRS3						3			//	BA : EMRS
#define DS								0			//	Driver strength
#define PASR							0			//	PASR
#define BA_MRS							0			//	BA : MRS
#define TM								0			// 	Test Mode - mode register set
#define CL_MRS							3			// 	CAS Latency
#define DLL_RESET_HIGH					1
#define DLL_RESET_LOW					0

/*---------------------------------------
 * REFRESH register : DDR2 SDRAM refresh register
 */
#define REFCYC							1037			// 	refresh cycle

/*---------------------------------------
 *  Calc DDR2 DRAMC register
 */
#define BANKCFGVAL						((RASBW0<<17)+(RASBW1<<14)+(CASBW0<<11)+(CASBW1<<8)+(ADDRCFG0<<6)+(ADDRCFG1<<4)+(MEMCFG<<1)+(BW<<0))
#define BANKCON1VAL						((DQSDelay<<28)+(1<<26)+(BStop<<7)+(WBUF<<6)+(AP<<5)+(PWRDN<<4))
#define BANKCON2VAL						((tRAS<<20)+(tARFC<<16)+(CL<<4)+(tRCD<<2)+(tRP<<0))


/*-----------------------------------------------------------------------
 * NAND-FLASH and environment organization
 */
#define CONFIG_SYS_NO_FLASH 

#define CONFIG_CMD_NAND
#define CONFIG_NAND_S3C2410
#define CONFIG_SYS_S3C2410_NAND_HWECC
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x4E000000

#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET				0x0
#define CONFIG_ENV_ADDR			(CONFIG_ENV_OFFSET + 0x80000)
#define CONFIG_ENV_SIZE			0x20000
#define CONFIG_ENV_OVERWRITE

/*
 * Size of malloc() pool
 * BZIP2 / LZO / LZMA need a lot of RAM
 */
#define CONFIG_SYS_MALLOC_LEN	(4 * 1024 * 1024)
#define CONFIG_SYS_MONITOR_LEN	(448 * 1024)
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE

/*
 * File system
 */
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_YAFFS2
#define CONFIG_RBTREE

/* additions for new relocation code, must be added to all boards */
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_SDRAM_BASE + 0x1000 - \
				GENERATED_GBL_DATA_SIZE)

/* SPL relatived */
#define CONFIG_SPL_STACK             0x2000
#define CONFIG_SYS_TEXT_BASE         0x30008000
#define CONFIG_SYS_NAND_U_BOOT_START  0x20000
#define CONFIG_SYS_NAND_U_BOOT_SIZE   0x800

#endif /* __CONFIG_H */
