#include "inc/header.h"

unsigned int read_IWARP2(int ad, int ch_offset)
{

    struct spi_msg spi_msg;
    
    memset(&spi_msg, 0, sizeof(struct spi_msg));

    spi_msg.addr = ad;
    spi_msg.bk_offset = ch_offset;

    ioctl(g_spi_fd, C787_IOCGREG, &spi_msg);

    //printf("[%s] ad = 0x%x, dt = 0x%x\n", __FUNCTION__, spi_msg.addr, spi_msg.data);

    return spi_msg.data;
}

void write_IWARP2(int ad, int dt, int ch_offset, int force)
{
    //printf("[%s] ad = 0x%x, dt = 0x%x\n", __FUNCTION__, ad, dt);

    struct spi_msg spi_msg;
    
    memset(&spi_msg, 0, sizeof(struct spi_msg));

    spi_msg.addr = ad;
    spi_msg.data = dt;
    spi_msg.bk_offset = ch_offset;
        
    ioctl(g_spi_fd, C787_IOCWREG, &spi_msg);
    
	return;
}
