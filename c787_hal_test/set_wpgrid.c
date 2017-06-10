// Set warp grid
#include "inc/header.h"


void SetWpGrid(int gx, int gy, int chg)
{
	int	cpuwad=0,offset;

	// 1st(make back ground)
	offset = (PS_WPOSDMWI<<7)*DEF_WPGDSIZE + DEF_WPGDSIZE;
	if((gy==0)&&(gx==0))      cpuwad = PS_WPOSDSAD0 - offset;
	else if((gy==0)&&(gx==1)) cpuwad = PS_WPOSDSAD0 + (GPTx[gx]-(DEF_WPGDSIZE>>1)) - offset;
	else if((gy==0)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;
	else if((gy==1)&&(gx==0)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[gy]-(DEF_WPGDSIZE>>1)) - offset;
	else if((gy==1)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[gy]-(DEF_WPGDSIZE>>1)) + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;
	else if((gy==2)&&(gx==0)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) - offset;
	else if((gy==2)&&(gx==1)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) + (GPTx[gx]-(DEF_WPGDSIZE>>1)) - offset;
	else if((gy==2)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;

	if(chg) write_IWARP2(B0_OSDFILL	,0xFF,0,0);
	else    write_IWARP2(B0_OSDFILL	,0x00,0,0);
	write_IWARP2(B0_BBACTHW		,(DEF_WPGDSIZE*3-1)&0x0fff,0,0);
	write_IWARP2(B0_BBACTVW		,(DEF_WPGDSIZE*3-1)&0xffff,0,0);
	write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
	write_IWARP2(B0_OSDCT		,0x01,0,1);
	do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);

	// 2nd(make frame)
	if(chg){
		offset = (PS_WPOSDMWI<<7)*((DEF_WPGDSIZE*3)>>2) + ((DEF_WPGDSIZE*3)>>2);
		if((gy==0)&&(gx==0))      cpuwad = PS_WPOSDSAD0 - offset;
		else if((gy==0)&&(gx==1)) cpuwad = PS_WPOSDSAD0 + (GPTx[gx]-(DEF_WPGDSIZE>>1)) - offset;
		else if((gy==0)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;
		else if((gy==1)&&(gx==0)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[gy]-(DEF_WPGDSIZE>>1)) - offset;
		else if((gy==1)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[gy]-(DEF_WPGDSIZE>>1)) + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;
		else if((gy==2)&&(gx==0)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) - offset;
		else if((gy==2)&&(gx==1)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) + (GPTx[gx]-(DEF_WPGDSIZE>>1)) - offset;
		else if((gy==2)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;

		write_IWARP2(B0_OSDFILL		,0x00,0,0);
		write_IWARP2(B0_BBACTHW		,(((DEF_WPGDSIZE*10)>>2)-1)&0x0fff,0,0);
		write_IWARP2(B0_BBACTVW		,(((DEF_WPGDSIZE*10)>>2)-1)&0xffff,0,0);
		write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
		write_IWARP2(B0_OSDCT		,0x01,0,1);
		do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);
	}

	// 3rd(make grid)
	offset = 0;
	if((gy==0)&&(gx==0))      cpuwad = PS_WPOSDSAD0 - offset;
	else if((gy==0)&&(gx==1)) cpuwad = PS_WPOSDSAD0 + (GPTx[gx]-(DEF_WPGDSIZE>>1)) - offset;
	else if((gy==0)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;
	else if((gy==1)&&(gx==0)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[gy]-(DEF_WPGDSIZE>>1)) - offset;
	else if((gy==1)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(GPTy[gy]-(DEF_WPGDSIZE>>1)) + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;
	else if((gy==2)&&(gx==0)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) - offset;
	else if((gy==2)&&(gx==1)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) + (GPTx[gx]-(DEF_WPGDSIZE>>1)) - offset;
	else if((gy==2)&&(gx==2)) cpuwad = PS_WPOSDSAD0 + (PS_WPOSDMWI<<7)*(PS_PANEL_ACT_VW-DEF_WPGDSIZE) + (PS_PANEL_ACT_HW-DEF_WPGDSIZE) - offset;

	write_IWARP2(B0_OSDFILL		,0xFF,0,0);
	write_IWARP2(B0_BBACTHW		,(DEF_WPGDSIZE-1)&0x0fff,0,0);
	write_IWARP2(B0_BBACTVW		,(DEF_WPGDSIZE-1)&0xffff,0,0);
	write_IWARP2(B0_CPUWAD		,(cpuwad&0x07ffffff),0,0);
	write_IWARP2(B0_OSDCT		,0x01,0,1);
	do { } while ((read_IWARP2(B0_BOSTAT,0)&0x01)==0x01);

	return;
}
