
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h> 
#include <time.h>

#define ANDROID_ALARM_SET_RTC               _IOW('a', 5, struct timespec)
#define ANDROID_ALARM_SET_RTC_BOOT_TIME     _IOW('a', 6, struct timespec)

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	int flag;
	unsigned int cmd;
	struct timespec ts;

	if (argc != 2) {
		printf("Usage: rtc_test 1/2\n");
		exit(-1);
	}

	flag = strtoul(argv[1], NULL, 10);

	clock_gettime(CLOCK_REALTIME, &ts);
	
	printf("ts.tv_sec = %d, ts.tv_nsec = %d\n", ts.tv_sec, ts.tv_nsec);

	fd = open("/dev/alarm", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(-2);
	}
	
	if (flag == 1) {
		ret = ioctl(fd, ANDROID_ALARM_SET_RTC, &ts);
		if (ret < 0) {
			perror("ioctl");
			exit(-3);
		}
	} else if (flag == 2) {
		ret = ioctl(fd, ANDROID_ALARM_SET_RTC_BOOT_TIME, &ts);
		if (ret < 0) {
			perror("ioctl");
			exit(-3);
		}		
	}

	return 0;
}