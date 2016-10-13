/*
 * @filename    : nand_boot.c
 * @author      : <lumingliang.github@gmail.com>
 * @description : This file is used to copy U-boot.bin to DRAM  
 *
 * */

#define NFCONF      (*(volatile unsigned int*)0x4E000000)
#define NFCONT      (*(volatile unsigned int*)0x4E000004)

#define NFCMMD      (*(volatile unsigned char*)0x4E000008)
#define NFADDR      (*(volatile unsigned char*)0x4E00000C)
#define NFDATA      (*(volatile unsigned char*)0x4E000010)

#define NFMECCD0    (*(volatile unsigned int*)0x4E000014)
#define NFMECCD1    (*(volatile unsigned int*)0x4E000018)

#define NFSECCD     (*(volatile unsigned int*)0x4E00001C)

#define NFSBLK      (*(volatile unsigned int*)0x4E000020)
#define NFEBLK      (*(volatile unsigned int*)0x4E000024)

#define NFSTAT      (*(volatile unsigned int*)0x4E000028)

#define NFECCERR0   (*(volatile unsigned int*)0x4E00002C)
#define NFECCERR1   (*(volatile unsigned int*)0x4E000030)

#define NFMECC0     (*(volatile unsigned int*)0x4E000034)
#define NFMECC1     (*(volatile unsigned int*)0x4E000038)
#define NFSECC      (*(volatile unsigned int*)0x4E00003C)

#define NFMLCBITPT  (*(volatile unsigned int*)0x4E000040)

#define NF8ECCERR0  (*(volatile unsigned int*)0x4E000044)
#define NF8ECCERR1  (*(volatile unsigned int*)0x4E000048)
#define NF8ECCERR2  (*(volatile unsigned int*)0x4E00004c)

#define NFM8ECC0    (*(volatile unsigned int*)0x4E000050)
#define NFM8ECC1    (*(volatile unsigned int*)0x4E000054)
#define NFM8ECC2    (*(volatile unsigned int*)0x4E000058)
#define NFM8ECC3    (*(volatile unsigned int*)0x4E00005c)

#define NFMLCBITPT0 (*(volatile unsigned int*)0x4E000060)
#define NFMLCBITPT1 (*(volatile unsigned int*)0x4E000064)

#define PAGE_SIZE 2048
#define PAGE_NUMS 64

extern void uart_tx_multiple_bytes(unsigned char *buf, int size);

void nand_write_cmmd(unsigned char cmmd)
{
	NFCMMD = cmmd;
}

void nand_write_addr(unsigned char addr)
{
	NFADDR = addr;
}

unsigned char nand_read_one_byte(void)
{
	return NFDATA&0xff;
}

void nand_chip_enable(void)
{
	NFCONT &= ~(1 << 1);
}

void nand_chip_disable(void)
{
	NFCONT |= (1 << 1);
}

void nand_clear_Rnb(void)
{
	NFSTAT &= (1 << 4);
}

void nand_wait_Rnb_ready(void)
{
	while(!(NFSTAT & (1 << 4)));
}

void nand_reset(void)
{
	nand_chip_enable();
	nand_clear_Rnb();

	nand_write_cmmd(0xff);
	nand_wait_Rnb_ready();
}


void nand_read_id(void)
{
	unsigned char maf_id[5];
	volatile unsigned char var = 0;

	nand_write_cmmd(0x90);
	nand_write_addr(0x00);
	
	for(var = 0; var < 5; var++){
		maf_id[var] = nand_read_one_byte();
	}
	
	nand_chip_disable();

	uart_tx_multiple_bytes(maf_id, 5);

}

 
int nand_read_one_page(int addr, int ram_addr)
{
	int block_addr = 0;
	int page_addr  = 0;
	int i = 0;
	unsigned char* dst_addr = (unsigned char*)ram_addr;

	block_addr = addr/(PAGE_SIZE*PAGE_NUMS);
	page_addr  = (addr%(PAGE_SIZE*PAGE_NUMS))/(PAGE_SIZE);

	nand_chip_enable();
	nand_clear_Rnb();

	nand_write_cmmd(0x00);	

	nand_write_addr(0x00);
	nand_write_addr(0x00);
	nand_write_addr(((block_addr&0x3) << 6) | (page_addr & 0xff));
	nand_write_addr((block_addr >> 2)&0xff);
	nand_write_addr((block_addr >> 10)&0x03);
	nand_write_cmmd(0x30);

	nand_wait_Rnb_ready();

	for(i = 0; i < PAGE_SIZE; i++){
		*dst_addr++ = nand_read_one_byte();	
	}

	nand_chip_disable();

	return 0;	
}

/*
 * @func        : copy_u_boot_to_sdram
 * @description : 用来拷贝u-boot到内存中去运行
 *
 *				1.传入的u-boot存放的地址要是nandflash的页边界对齐
 *				2.传入的u-boot的实际大小也要求是nandflash的页边界对齐
 * */
int copy_u_boot_to_dram(int uboot_start_addr, int ram_addr, int u_boot_size)
{
#if 1	
	volatile int ofs = 0;
	volatile unsigned int dram_addr = ram_addr;

	if(uboot_start_addr%PAGE_SIZE || u_boot_size%PAGE_SIZE){
		/* fix me? if PAGE_SIZE != 2048 */
		return 1;
	}

	nand_reset();
	
	nand_read_id();

	for(ofs = uboot_start_addr; ofs < uboot_start_addr + u_boot_size; ofs += PAGE_SIZE){
		nand_read_one_page(ofs, dram_addr);
		dram_addr += PAGE_SIZE;
	}

	return 0;
#else

	unsigned int memtst_addr = 0x30008000;
	volatile unsigned int memtst_val  = 0x0;	
	unsigned char mem_dbg[5];

	/* write */
	*(volatile unsigned int *)memtst_addr = 0xffeeddcc;

	mem_dbg[0] = 0xff;
	mem_dbg[1] = 0xee;
	mem_dbg[2] = 0xdd;
	mem_dbg[3] = 0xcc;

	uart_tx_multiple_bytes(mem_dbg, 4);

	/* read */
	memtst_val = *(volatile unsigned int*)memtst_addr;	

	mem_dbg[0] = memtst_val & 0xff;
	mem_dbg[1] = (memtst_val >> 8) & 0xff;
	mem_dbg[2] = (memtst_val >> 16)& 0xff;
	mem_dbg[3] = (memtst_val >> 24)& 0xff;
	
	uart_tx_multiple_bytes(mem_dbg, 4);


	if(memtst_val == 0xffeeddcc)
		return 0;
	else
		return 1;

#endif 

}

