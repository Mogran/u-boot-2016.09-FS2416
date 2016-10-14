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


static void s3c2416_clear_Rnb(void)
{
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

	writel(readl(&nand->nfstat) | (1 << 4), &nand->nfstat);
}

static void s3c24x0_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

	if (ctrl & NAND_CTRL_CHANGE) {

		if ((ctrl & NAND_CLE)){
			debug("hwcontrol(): write command : 0x%02x \n", cmd);
			writeb(cmd, &nand->nfcmmd);
			if(cmd == NAND_CMD_RESET || cmd == NAND_CMD_ERASE2 
				|| cmd == NAND_CMD_READSTART || cmd == NAND_CMD_PAGEPROG)
			{
				s3c2416_clear_Rnb();
			}
		}
		if ((ctrl & NAND_ALE)){
			debug("hwcontrol(): write addr : 0x%02x \n", cmd);
			writeb(cmd, &nand->nfaddr);
		}

		if (ctrl & NAND_NCE){
			writel(readl(&nand->nfcont) & ~S3C2410_NFCONF_nFCE,
			       &nand->nfcont);
		}else{
			debug("hwcontrol() disselect chip \n");
			writel(readl(&nand->nfcont) | S3C2410_NFCONF_nFCE,
			       &nand->nfcont);
		}
	}

	if (cmd != NAND_CMD_NONE && cmd != 0x03)
		writeb(cmd, chip->IO_ADDR_W);
}

static int s3c24x0_dev_ready(struct mtd_info *mtd)
{
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

	/*while(!(readl(&nand->nfstat)&(1 << 4)));*/

	/* debug("dev_ready\n");*/
	return (readl(&nand->nfstat)&(1 << 4));
}

int board_nand_init(struct nand_chip *nand)
{
	struct s3c24x0_nand *nand_reg = s3c24x0_get_base_nand();

	debug("board_nand_init()\n");

	/* initialize nand_chip data structure */
	writel((0<<12)|(2<<8)|(1<<4)|(1<<1), &nand_reg->nfconf);
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
