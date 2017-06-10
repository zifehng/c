// Init warp grid
#include "inc/header.h"


void InitWpGrid(void)
{
	int	x,y,cpuwad=0;

	// OSD-plane initialize
	write_IWARP2(B0_OSDCT		,0x00,0,0);
	write_IWARP2(B0_BBACTHW		,0x07ff,0,0);	// BitBLT ACT HW(2048)
	write_IWARP2(B0_BBACTVW		,0x04df,0,0);	// BitBLT ACT VW(1248)
	write_IWARP2(B0_CPUWAD		,(PS_WPOSDSAD0&0x07ffffff),0,0);
	write_IWARP2(B0_BBWMWI		,0x10,0,0);		// BitBLT WMWI(2048)
	write_IWARP2(B0_BBRMWI		,0x10,0,0);		// BitBLT RMWI(2048)
	write_IWARP2(B0_OSDFILL		,0x00,0,0);		// OSDFILL(trans)
	write_IWARP2(B0_OSDCT		,0x01,0,1);		// OSDFILL exe
	do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);

	// write grid
	// top
	for(x=0; x<3; x++){
		if(x==0)      cpuwad = PS_WPOSDSAD0;
		else if(x==1) cpuwad = PS_WPOSDSAD0 + (GPTx[x]-(DEF_WPGDSIZE>>1));
		else		  cpuwad = PS_WPOSDSAD0 + (PS_PANEL_ACT_HW-DEF_WPGDSIZE);

		write_IWARP2(B0_OSDFILL		,0xFF,0,0);
		write_IWARP2(B0_BBACTHW		,(DEF_WPGDSIZE-1)&0x0fff,0,0);
		write_IWARP2(B0_BBACTVW		,(DEF_WPGDSIZE-1)&0xffff,0,0);
		write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
		write_IWARP2(B0_OSDCT		,0x01,0,1);
		do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);
	}

	// bottom
	cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE);

	write_IWARP2(B0_OSDFILL		,0xFF,0,0);
	write_IWARP2(B0_BBACTHW		,(PS_PANEL_ACT_HW-1)&0x0fff,0,0);
	write_IWARP2(B0_BBACTVW		,(DEF_WPGDSIZE-1)&0xffff,0,0);
	write_IWARP2(B0_CPURAD		,(PS_WPOSDSAD0&0x07ffffff),0,0);
	write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
	write_IWARP2(B0_OSDCT		,0x02,0,1);
	do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);

	// left
	for(y=0; y<3; y++){
		if(y==0)      cpuwad = PS_WPOSDSAD0;
		else if(y==1) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[y]-(DEF_WPGDSIZE>>1));
		else		  cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE);

		write_IWARP2(B0_OSDFILL		,0xFF,0,0);
		write_IWARP2(B0_BBACTHW		,(DEF_WPGDSIZE-1)&0x0fff,0,0);
		write_IWARP2(B0_BBACTVW		,(DEF_WPGDSIZE-1)&0xffff,0,0);
		write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
		write_IWARP2(B0_OSDCT		,0x01,0,1);
		do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);
	}

	// right
	cpuwad = PS_WPOSDSAD0 + (PS_PANEL_ACT_HW-DEF_WPGDSIZE);

	write_IWARP2(B0_OSDFILL		,0x11,0,0);
	write_IWARP2(B0_BBACTHW		,(DEF_WPGDSIZE-1)&0x0fff,0,0);
	write_IWARP2(B0_BBACTVW		,(PS_PANEL_ACT_VW-1)&0xffff,0,0);
	write_IWARP2(B0_CPURAD		,(PS_WPOSDSAD0&0x07ffffff),0,0);
	write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
	write_IWARP2(B0_OSDCT		,0x02,0,1);
	do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);
	
	return;
}
