#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 


typedef long __kernel_time_t;
typedef long __kernel_suseconds_t;
typedef unsigned short __u16;
typedef int __s32;

struct mytimeval {
	__kernel_time_t		tv_sec;		/* seconds */
	__kernel_suseconds_t	tv_usec;	/* microseconds */
};

struct input_event {
	struct mytimeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: event_test /dev/input/eventX\n");
        exit(-1);
    }

    int fd;
    int ret;
    struct input_event event;

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("open %s error!\n", argv[1]);
        //perror("open");
        exit(-2);
    }

    while(1) {
        memset(&event, 0, sizeof(event));
        ret = read(fd, &event, sizeof(event));
        if (ret < 0) {
            perror("read");
            exit(-3);
        }
        printf("type = %#x,\t code = %#x,\t value = %#x\n\n", event.type, event.code, event.value);
    }
    
    return 0;
}

