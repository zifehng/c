

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 

int main(void)
{
    int i;
    int fd = -1;
    char c = 21;
    char d;

    fd = open("/data/test.bin", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }

    ftruncate(fd, 0);
    lseek(fd, 0, SEEK_SET);
    for (i = 0; i < 255; i++) { 
        if (write(fd, &c, sizeof(char)) < 0)
            perror("write");

        //c++;
    }

#if 1
    lseek(fd, 0, SEEK_SET);
    for (i = 0; i < 255; i++) {
        if (read(fd, &d, sizeof(char)) < 0)
            perror("read");

        printf("%d:", i);
        printf("%d\n", d);
    }
#endif

    return 0;
}
