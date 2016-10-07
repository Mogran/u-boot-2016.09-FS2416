/*
 * @filename    : nand_boot.c
 * @author      : <lumingliang.github@gmail.com>
 * @description : This file is used to copy U-boot.bin to DRAM  
 *
 * */

#define PAGE_SIZE 2048
#define PAGE_NUMS 64


void nand_chip_enable(void)
{

}

void nand_chip_disable(void)
{

}

void nand_clear_Rnb(void)
{

}

void nand_wait_Rnb_ready(void)
{

}

unsigned char nand_read_one_byte(void)
{
	return 0;
}

void nand_write_cmmd(unsigned char cmd)
{

}

void nand_write_addr(unsigned char addr)
{

}

void nand_reset(void)
{

}

static int nand_read_one_page(int addr, unsigned char *dat)
{
	int block_addr = 0;
	int page_addr  = 0;
	int i = 0;

	block_addr = addr/(PAGE_SIZE*PAGE_NUMS);
	page_addr  = (addr%(PAGE_SIZE*PAGE_NUMS))/(PAGE_SIZE);

	nand_chip_enable();
	nand_clear_Rnb();

	nand_write_cmmd(0x00);	
	nand_write_addr(0x00);
	nand_write_addr(0x00);
	nand_write_addr(((block_addr&0x3) << 6) | (page_addr & 0x40));
	nand_write_addr((block_addr >> 2)&0xff);
	nand_write_addr((block_addr >> 10)&0x03);
	nand_write_cmmd(0x30);

	nand_wait_Rnb_ready();

	for(i = 0; i < PAGE_SIZE; i++){
		*dat++ = nand_read_one_byte();	
	}

	nand_chip_disable();

	return 0;	
}

/*
 * @func        : copy_u_boot_to_sdram
 * @description : 用来拷贝u-boot到内存中去运行
 *
 * */
int copu_u_boot_to_sdram(int nand_addr, int dram_addr, int u_boot_size)
{
	int ofs = 0;



	return 0;
}

