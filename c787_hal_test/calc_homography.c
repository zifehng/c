// Calculate Homography
#include "inc/header.h"

#define min(x, y)   ((x) > (y) ? (y) : (x))

void CalcHomography(str_wppos4c *p4c)
{
	double	FHW,FVW;
	double	hg_sx,hg_sy,hg_dx1,hg_dx2,hg_dy1,hg_dy2,hg_z,hg_g,hg_h;
	double	hg_sys0,hg_sys1,hg_sys2,hg_sys3,hg_sys4,hg_sys5,hg_sys6,hg_sys7;
	int		sftn;
	ulong	wplgct;
	ulong	dtct;
	int		dtsel;

	double P[3][3],Q[3][3];
	double det;

	FHW  = (double)PS_PANEL_ACT_HW;
	FVW	 = (double)PS_PANEL_ACT_VW;
	sftn = PM_WPDTMD ? 5 : 4;

	HMIN = min((int)(p4c->tr_x - p4c->tl_x) , (int)(p4c->br_x - p4c->bl_x) );
	my_VMIN = min((int)(p4c->bl_y - p4c->tl_y) , (int)(p4c->br_y - p4c->tr_y) );

	//===== calculate homography coefficient =====//
	hg_sx	= (double)((p4c->tl_x - p4c->tr_x) + (p4c->br_x - p4c->bl_x));
	hg_sy	= (double)((p4c->tl_y - p4c->tr_y) + (p4c->br_y - p4c->bl_y));
	hg_dx1	= (double)(p4c->tr_x - p4c->br_x);
	hg_dx2	= (double)(p4c->bl_x - p4c->br_x);
	hg_dy1	= (double)(p4c->tr_y - p4c->br_y);
	hg_dy2	= (double)(p4c->bl_y - p4c->br_y);
	hg_z	= (hg_dx1*hg_dy2) - (hg_dy1*hg_dx2);
	hg_g	= ((hg_sx*hg_dy2) - (hg_sy*hg_dx2)) / hg_z;
	hg_h	= ((hg_sy*hg_dx1) - (hg_sx*hg_dy1)) / hg_z;
 
	hg_sys0	= p4c->tr_x*(1 + hg_g) - p4c->tl_x;
	hg_sys1	= p4c->bl_x*(1 + hg_h) - p4c->tl_x;
	hg_sys2	= p4c->tl_x;
	hg_sys3	= p4c->tr_y*(1 + hg_g) - p4c->tl_y;
	hg_sys4	= p4c->bl_y*(1 + hg_h) - p4c->tl_y;
	hg_sys5	= p4c->tl_y;
	hg_sys6 = hg_g;
	hg_sys7	= hg_h;

	P[0][0] = hg_sys0;
	P[0][1] = hg_sys1;
	P[0][2] = hg_sys2;
	P[1][0] = hg_sys3;
	P[1][1] = hg_sys4;
	P[1][2] = hg_sys5;
	P[2][0] = hg_sys6;
	P[2][1] = hg_sys7;
	P[2][2] = 1;

	det=P[0][0]*P[1][1]*P[2][2]
			+P[1][0]*P[2][1]*P[0][2]
			+P[2][0]*P[0][1]*P[1][2]
			-P[0][0]*P[2][1]*P[1][2]
			-P[2][0]*P[1][1]*P[0][2]
			-P[1][0]*P[0][1]*P[2][2];

	Q[0][0]=(P[1][1]*P[2][2]-P[1][2]*P[2][1])/det * FHW;
	Q[1][0]=(P[1][2]*P[2][0]-P[1][0]*P[2][2])/det * FVW;
	Q[2][0]=(P[1][0]*P[2][1]-P[1][1]*P[2][0])/det;

	Q[0][1]=(P[0][2]*P[2][1]-P[0][1]*P[2][2])/det * FHW;
	Q[1][1]=(P[0][0]*P[2][2]-P[0][2]*P[2][0])/det * FVW;
	Q[2][1]=(P[0][1]*P[2][0]-P[0][0]*P[2][1])/det;

	Q[0][2]=(P[0][1]*P[1][2]-P[0][2]*P[1][1])/det * FHW;
	Q[1][2]=(P[0][2]*P[1][0]-P[0][0]*P[1][2])/det * FVW;
	Q[2][2]=(P[0][0]*P[1][1]-P[0][1]*P[1][0])/det;

/*	printf("%.15f,",Q[0][0]*FHW);
	printf("%.15f,",Q[0][1]*FHW);
	printf("%.15f,",Q[0][2]*FHW);
	printf("%.15f,",Q[1][0]*FVW);
	printf("%.15f,",Q[1][1]*FVW);
	printf("%.15f,",Q[1][2]*FVW);
	printf("%.15f,",Q[2][0]);
	printf("%.15f,",Q[2][1]);
	printf("%.15f,",Q[2][2]);		
	printf("\n\n");*/


	write_IWARP2(B17_WPLGCT,0x0010,0,0);
	if((FHW>=2064)|( (int)(FHW/16)*16 == (int)(FHW) )){
		write_IWARP2(B17_WPLGACTHW,(int)(FHW/16),0,0);
	}else{
		write_IWARP2(B17_WPLGACTHW,(int)(FHW/16)+1,0,0);
	}
	if((FVW>=1232)|( (int)(FVW/16)*16 == (int)(FVW) )){
		write_IWARP2(B17_WPLGACTVW,(int)(FVW/16),0,0);
	}else{
		write_IWARP2(B17_WPLGACTVW,(int)(FVW/16)+1,0,0);
	}

	write_IWARP2(B17_WPLGA,(int)(Q[0][0]*pow(2.0,19)+0.5)&0x07ffffff,0,0);
	write_IWARP2(B17_WPLGB,(int)(Q[0][1]*pow(2.0,19)+0.5)&0x07ffffff,0,0);
	write_IWARP2(B17_WPLGC,(int)(Q[0][2]*pow(2.0,10)+0.5)&0x07ffffff,0,0);

	write_IWARP2(B17_WPLGD,(int)(Q[1][0]*pow(2.0,19)+0.5)&0x07ffffff,0,0);
	write_IWARP2(B17_WPLGE,(int)(Q[1][1]*pow(2.0,19)+0.5)&0x07ffffff,0,0);
	write_IWARP2(B17_WPLGF,(int)(Q[1][2]*pow(2.0,10)+0.5)&0x07ffffff,0,0);

	write_IWARP2(B17_WPLGG,(int)(Q[2][0]*pow(2.0,25)+0.5)&0x07ffffff,0,0);
	write_IWARP2(B17_WPLGH,(int)(Q[2][1]*pow(2.0,25)+0.5)&0x07ffffff,0,0);
	write_IWARP2(B17_WPLGI,(int)(Q[2][2]*pow(2.0,19)+0.5)&0x07ffffff,0,1);

	dtct  = read_IWARP2(B14_DTCT,0)&0xffff;
    dtsel = (dtct>>4)&0x0f;
	if((PM_WPDTMD==0)&&(dtsel==0))      dtct = 0x0000;
	else if((PM_WPDTMD==0)&&(dtsel!=0)) dtct = 0x0010;
	else if((PM_WPDTMD!=0)&&(dtsel==0)) dtct = 0x0002;
	else				                dtct = 0x0012;
	
	if(dtsel==0){
		write_IWARP2(B17_WPLGCT,0x0021,0,1);
	}else{
		write_IWARP2(B17_WPLGCT,0x0011,0,1);
	}

	do{
		wplgct = read_IWARP2(B17_WPLGCT,0)&0xffff;
		//printf("B17_WPLGCT = %04x\n",wplgct);
	}while( (wplgct&0x0002) == 0x0002 );

	write_IWARP2(B17_WPLGCT,wplgct&0xfffe,0,1);

	if((PM_WPDTMD==0)&&(dtsel==0))      dtct = 0x0010;
	else if((PM_WPDTMD==0)&&(dtsel!=0)) dtct = 0x0000;
	else if((PM_WPDTMD!=0)&&(dtsel==0)) dtct = 0x0012;
	else				                dtct = 0x0002;

	write_IWARP2(BN_RTCT,0x0707,0,1);
	write_IWARP2(B14_DTCT,dtct,0,0);
	write_IWARP2(BN_RTCT,0x0105,0,1);
    wait1_povs();
	write_IWARP2(BN_RTCT,0x0000,0,1);

	return;
}
