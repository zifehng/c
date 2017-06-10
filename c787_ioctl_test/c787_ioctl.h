#ifndef __C787_IOCTL_H__
#define __C787_IOCTL_H__

//#include <linux/ioctl.h>

#define C787_IOC_MAGIC  'c'
#define C787_IOCINIT    _IO(C787_IOC_MAGIC, 0)
#define C787_IOCGREG    _IOW(C787_IOC_MAGIC, 1, int)
#define C787_IOCWREG    _IOR(C787_IOC_MAGIC, 2, int)
#define C787_IOC_MAXNR  3

struct spi_msg {
    int addr;
    int bk_offset;
    unsigned int data;
};


#endif
