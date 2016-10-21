/*
 * (C) Copyright 2006 OpenMoko, Inc.
 * Author: Harald Welte <laforge@openmoko.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#include <nand.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <asm/io.h>

#define S3C2410_NFCONF_nFCE        (1<<1)

static void s3c24x0_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

#if 0
	debug("hwcontrol() cmd = %x ctrl = %x \n", cmd, ctrl);
#endif

	if (ctrl & NAND_CTRL_CHANGE) {
		if (ctrl & NAND_NCE){
			writel(readl(&nand->nfcont) & ~S3C2410_NFCONF_nFCE,
			       &nand->nfcont);
		}else{
			debug("hwcontrol() disselect chip \n");
			writel(readl(&nand->nfcont) | S3C2410_NFCONF_nFCE,
			       &nand->nfcont);
		}
	}

	if(cmd == NAND_CMD_NONE){
		debug(" do nothing \n");
		return;
	}

	switch(ctrl&0x0f){
	case NAND_CTRL_CLE:
		debug("hwcontrol(): write command : 0x%02x \n", cmd);
		writeb(cmd, &nand->nfcmmd);
	break;	
	case NAND_CTRL_ALE:
		debug("hwcontrol(): write addr : 0x%02x \n", cmd);
		writeb(cmd, &nand->nfaddr);
	break;
	
	default:
#if 0	
		writeb(cmd, chip->IO_ADDR_W);
#else
		debug("neither cmmd nor addr .. so, i don't do anything\n");	
#endif		
	break;	
	
	}
}

static int s3c24x0_dev_ready(struct mtd_info *mtd)
{
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

	/* debug("dev_ready\n");*/
	return (readl(&nand->nfstat)&(1 << 0));
}

int board_nand_init(struct nand_chip *nand)
{
	struct s3c24x0_nand *nand_reg = s3c24x0_get_base_nand();

	debug("board_nand_init()\n");

	/* initialize nand_chip data structure */
	/*writel((0<<12)|(2<<8)|(1<<4)|(1<<1), &nand_reg->nfconf); */
	writel((7<<12)|(7<<8)|(7<<4)|(1<<1), &nand_reg->nfconf); 
	writel((0<<8)|(1<<1)|(1<<0), &nand_reg->nfcont);

	nand->IO_ADDR_R = (void *)&nand_reg->nfdata;
	nand->IO_ADDR_W = (void *)&nand_reg->nfdata;

	nand->select_chip = NULL;

	/* hwcontrol always must be implemented */
	nand->cmd_ctrl = s3c24x0_hwcontrol;
	nand->dev_ready = s3c24x0_dev_ready;
	nand->ecc.mode = NAND_ECC_NONE;
	nand->options = 0;

	debug("end of nand_init\n");

	return 0;
}
