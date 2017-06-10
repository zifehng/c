//#define LOG_TAG "c787_ctrl"
//#include <cutils/log.h>

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <sys/ioctl.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "inc/declare_gPS.h"	//System specific variables
#include "inc/declare_gVarWP.h"	//Other globals and function prototypes(for WARP)
#include "inc/c787_reg.h"		//Scaler registers
#include "inc/c787_ioctl.h"

#define DEVICE_NAME     "/dev/c787"
#define FIRWMARE_NAME   "/data/c787_keystone_firmware.bin"

extern int g_spi_fd;
extern int g_firmware_fd;



	
