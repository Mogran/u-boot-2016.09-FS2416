cmd_fs/built-in.o :=  arm-none-linux-gnueabi-ld     -r -o fs/built-in.o fs/fs.o fs/ext4/built-in.o fs/fat/built-in.o fs/ubifs/built-in.o fs/yaffs2/built-in.o 
