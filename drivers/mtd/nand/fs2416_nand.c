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

#define S3C2410_NFCONF_EN          (1<<15)
#define S3C2410_NFCONF_512BYTE     (1<<14)
#define S3C2410_NFCONF_4STEP       (1<<13)
#define S3C2410_NFCONF_INITECC     (1<<5)
#define S3C2410_NFCONF_nFCE        (1<<1)
#define S3C2410_NFCONF_TACLS(x)    ((x)<<8)
#define S3C2410_NFCONF_TWRPH0(x)   ((x)<<4)
#define S3C2410_NFCONF_TWRPH1(x)   ((x)<<0)

#define S3C2410_ADDR_NALE 4
#define S3C2410_ADDR_NCLE 8

static void s3c24x0_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

	debug("hwcontrol(): 0x%02x 0x%02x\n", cmd, ctrl);

	if (ctrl & NAND_CTRL_CHANGE) {

		if (!(ctrl & NAND_CLE))
			writeb(cmd, &nand->nfcmmd);
		if (!(ctrl & NAND_ALE))
			writeb(cmd, &nand->nfaddr);

		if (ctrl & NAND_NCE)
			writel(readl(&nand->nfconf) & ~S3C2410_NFCONF_nFCE,
			       &nand->nfconf);
		else
			writel(readl(&nand->nfconf) | S3C2410_NFCONF_nFCE,
			       &nand->nfconf);
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, chip->IO_ADDR_W);
}

static int s3c24x0_dev_ready(struct mtd_info *mtd)
{
	struct s3c24x0_nand *nand = s3c24x0_get_base_nand();

	debug("dev_ready\n");
	return readl(&nand->nfstat) & 0x01;
}

int board_nand_init(struct nand_chip *nand)
{
	struct s3c24x0_nand *nand_reg = s3c24x0_get_base_nand();

	debug("board_nand_init()\n");

	/* initialize nand_chip data structure */
#if 0	
	writel((0<<12)|(2<<8)|(1<<4)|(1<<1), &nand_reg->nfconf);
#else
	writel((7<<12)|(7<<8)|(7<<4)|(1<<1), &nand_reg->nfconf);
#endif
	writel((2<<12)|(1<<1)|(1<<0), &nand_reg->nfcont);

	nand->IO_ADDR_R = (void *)&nand_reg->nfdata;
	nand->IO_ADDR_W = (void *)&nand_reg->nfdata;

	nand->select_chip = NULL;

	/* hwcontrol always must be implemented */
	nand->cmd_ctrl = s3c24x0_hwcontrol;
	nand->dev_ready = s3c24x0_dev_ready;
	nand->ecc.mode = NAND_ECC_SOFT;


	debug("end of nand_init\n");

	return 0;
}
