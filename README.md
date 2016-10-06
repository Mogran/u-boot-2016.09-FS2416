#\#
#\# (C) Copyright 2016~2016 
#\# Lu mingliang, Free Software Engineer
#\#


# Overview
==========

This's project used to adapt Samsung FS2416 Development Board.I clone
u-boot-2016.09 from u-boot official git page and I have removed some
unreleatived files to make u-boot-2016.09 project more smaller and renamed
u-boot-2016.09 to u-boot-2016.09-FS2416

# Constraint
============

- FS2416 board must use nand boot mode, not IROM boot mode.
- OM[4:0] must be 0x00110
- ARMCLK = 400MHZ HCLK=133MHZ PCLK=66MHZ

# How to use this?
==================

- Compile source code
	- make distclean 
	- make fs2416_defconfig
	- make

- ISP (In System Program)
	- use H-JTAG to write u-boot-spl.bin to the first 8Kb of Nandflash
	- use H-JTAG to write u-boot.bin to addr at the begin of 8KB of Nandflash.


# History Version
=================
- version 1.0 
	- add FS2416 DDR2 memory initialization where placed arm/board/samsung/fs2416/lowlevel_init.S
	- add FS2416 board.c 
