


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 

#include "c787_ioctl.h"

int main(int argc, char **argv)
{

    int fd;
    int flag;
    
    struct spi_msg spi_msg;
    if (argc != 4) {
        printf("argc = %d\n", argc);
        exit(-1);
    }
	
	
    //printf("argv[1] = %s, argv[2] = %s, argv[3] = %s\n", argv[1], argv[2], argv[3]);
    
    flag = strtoul(argv[1], NULL, 10);
    spi_msg.addr = strtoul(argv[2], NULL, 16);
    spi_msg.data = strtoul(argv[3], NULL, 16);
    
    //printf("convert: flag = %d, addr = 0x%x, data = 0x%x\n", flag, spi_msg.addr, spi_msg.data);
    sleep(1);
    
    fd = open("/dev/i-Chip_C787", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(-2);
    }

    printf("fd = %d\n", fd);
    
    switch(flag) {
    case 0:
        ioctl(fd, C787_IOCINIT);
        break;
    case 1:
        ioctl(fd, C787_IOCGREG, &spi_msg);
        sleep(1);
        printf("read: addr = 0x%x, data = 0x%x\n", spi_msg.addr, spi_msg.data);
        sleep(1);
        
        break;
    case 2:
        ioctl(fd, C787_IOCWREG, &spi_msg);
        break;
    default:
        printf("unknown cmd!\n");

    }

    return 0;
}
