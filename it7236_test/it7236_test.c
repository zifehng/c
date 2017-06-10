
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 

typedef unsigned char u8;

struct it7236_msg {
    u8 reg;
    u8 data;
};

int main(int argc, char *argv[])
{
    int fd;
    int ret;
    struct it7236_msg it7236_msg;

    if (argc != 4) {
        printf("usage: ./it7236_test r/w reg data\n");
        exit(-1);
    }

    printf("argv[1] = %s, argv[2] = %s, argv[3] = %s\n",argv[1], argv[2], argv[3]);
    it7236_msg.reg = strtoul(argv[2], NULL, 16);
    it7236_msg.data = strtoul(argv[3], NULL, 16);

    sleep(1);
    
    fd = open("/dev/IT7236", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(-2);
    }

    if (!strcmp("r", argv[1])) {
        ret = read(fd, &it7236_msg, sizeof(struct it7236_msg));
        if (ret < 0) {
            perror("read");
            exit(-3);
        }
        printf("read: it7236_msg.reg = %#x, it7236_msg.data = %#x\n", \
            it7236_msg.reg, it7236_msg.data);
    } else if (!strcmp("w", argv[1])) {
        ret = write(fd, &it7236_msg, sizeof(struct it7236_msg));
        if (ret < 0) {
            perror("write");
            exit(-4);        
        }
    } else
        printf("unknown cmd!\n");
    
    
    return 0;    
    
}
