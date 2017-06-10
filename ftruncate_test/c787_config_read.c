#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 

#define FIRMWARE_SIZE   1016 
#define REGDATA_SIZE    82

struct spi_msg {
    int addr;
    int bk_offset;
    unsigned int data;
};

struct wp_pos4c {
	int tl_x,tl_y;					
	int tr_x,tr_y;					
	int bl_x,bl_y;					
	int br_x,br_y;					
};


int main(void)
{
    int i = 0;
    int fd = -1;
	int ret = -1;
    int currpos = -1;

    struct spi_msg spi_msg;
    struct wp_pos4c wp_pos4c; 
    
    fd = open("/data/projector/ichip/c787_keystone_firmware.bin", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }

    currpos = lseek(fd, 0, SEEK_END);
	printf("firmware size = %d\n", currpos);
	lseek(fd, 0, SEEK_SET);

    //lseek(fd, 0, SEEK_SET);
    ret = read(fd, &wp_pos4c, sizeof(struct wp_pos4c));
	if (ret < 0) {
		perror("read");
		exit(-1);
	}

    printf("top left    \t: x = %d, y = %d\n", wp_pos4c.tl_x, wp_pos4c.tl_y);
    printf("top right   \t: x = %d, y = %d\n", wp_pos4c.tr_x, wp_pos4c.tr_y);
    printf("bottom left \t: x = %d, y = %d\n", wp_pos4c.bl_x, wp_pos4c.bl_y);
    printf("bottom right\t: x = %d, y = %d\n", wp_pos4c.br_x, wp_pos4c.br_y);

	while (1) {
		memset(&spi_msg, 0, sizeof(struct spi_msg));
		ret = read(fd, &spi_msg, sizeof(struct spi_msg));	
		if (ret < 0) {
			perror("read");
			exit(-1);
		}

		if (ret == 0)
			break;

        printf("[%d] bk_offset = %d, addr = %#x, data = %#x\n", \
			i++, spi_msg.bk_offset, spi_msg.addr, spi_msg.data);
	}

    return 0;
}
