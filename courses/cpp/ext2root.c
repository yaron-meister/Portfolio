/*
 * ext2root.c
 *
 * Read root directory inode (#2) from the inode table of the floppy
 * disk.
 *
 * Questions?
 * Emanuele Altieri
 * ealtieri@hampshire.edu
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/ext2_fs.h>
#include <string.h>

#define BASE_OFFSET 1024                   /* locates beginning of the super block (first group) */
#define FD_DEVICE "/dev/ram0"               /* the floppy disk device */
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size)




static int read_dir(char* name, int fd, const struct ext2_inode *inode,
										   const struct ext2_group_desc *group);





static unsigned int block_size = 0;        /* block size (to be calculated) */



static void read_inode(fd, inode_no, group, inode)
     int                           fd;        /* the floppy disk file descriptor */
     int                           inode_no;  /* the inode number to read  */
     const struct ext2_group_desc *group;     /* the block group to which the inode belongs */
     struct ext2_inode            *inode;     /* where to put the inode from disk  */
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no-1)*sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
} /* read_inode() */



int main(int argc, char* argv[])
{
	struct ext2_super_block super;
	struct ext2_group_desc group;
	struct ext2_inode inode;
	int fd;
	int i;
	char buff[1024] = "";

	/* open floppy device */

	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0) {
		perror(FD_DEVICE);
		exit(1);  /* error while opening the floppy device */
	}

	/* read super-block */

	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, &super, sizeof(super));

	if (super.s_magic != EXT2_SUPER_MAGIC) {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}
		
	block_size = 1024 << super.s_log_block_size;

	/* read group descriptor */

	lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
	read(fd, &group, sizeof(group));

	/* read root inode */
	lseek(fd, 1049600, SEEK_SET);  /* position head above the group descriptor block */
	read(fd, buff, 5);

	printf("Reading a file with direct offset (Ex.2): %s\n", buff);

	read_inode(fd, 2, &group, &inode);
	read_inode(fd, read_dir(argv[1], fd, &inode, &group), &group, &inode);
	
	lseek(fd, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
	read(fd, buff, 20);

	printf("Reading a file through inode (Ex.3): %s\n", buff);

	close(fd);
	exit(0);
} /* main() */






static int read_dir(char* name, int fd, const struct ext2_inode *inode, const struct ext2_group_desc *group)
{
	void *block;
	int ret = 0;

	if (S_ISDIR(inode->i_mode)) 
	{
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		if ((block = malloc(block_size)) == NULL) 
		{ /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		read(fd, block, block_size);                /* read block from disk*/

		entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory */
                /* Notice that the list may be terminated with a NULL
                   entry (entry->inode == NULL)*/
		while ((size < inode->i_size) && entry->inode) 
		{
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len);

			if (0 == strcmp(name, entry->name))
			{
				ret = entry->inode;
			}

			file_name[entry->name_len] = 0;     /* append null character to the file name */
			entry = (void*) entry + entry->rec_len;
			size += entry->rec_len;
		}

		free(block);
	}

	return (ret);
} /* read_dir() */
