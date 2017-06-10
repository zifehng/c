// Write warp table
#include "inc/header.h"


void WriteWpTable(void)
{
	int		x,y,dtdtx,dtdty,tad;
	int		sftyad,x2knz,x2kad,sftyad2k;
	int		xmax,phwdmy,dmynz,xsft;
	int		sftn;
	ulong	dtct;
	int		dtsel;
	float	tx,ty;
	float	phwru;
	float	xstmin,xedmax;
	float	frx,brx,phwdmynz;
	float	hscl,vscl;

	hscl = 1.0;
	vscl = 1.0;

	sftn = PM_WPDTMD ?  5 :  4;

	//===== for dummy area process =====//
	if(DEF_WPDMYHW!=0){
		phwru  = (float)(PHWNZ<<sftn);
		xstmin = 1000000;
		xedmax = 0;

		for(y=PVWNZ; y>=0; y--){
			if(Px[0][y]<xstmin){	 // x = 0
				if(Px[0][y]<0) xstmin = 0;
				else xstmin = Px[0][y];
			}
			if(Px[PHWNZ][y]>xedmax){ // x = PHWNZ
				if(Px[PHWNZ][y]>phwru) xedmax = phwru;
				else xedmax = Px[PHWNZ][y];
			}
		}
	}

	sftyad   = PM_WPDTMD ? 6    : 7;
	x2knz    = PM_WPDTMD ? 64   : 128;
	x2kad    = PM_WPDTMD ? 2560 : 9984;
	sftyad2k = 1;

	frx      = (float)(DEF_WPDMYHW>>sftn);
	brx      = (float)(DEF_WPDMYHW>>sftn);
	xmax	 = PHWNZ + (DEF_WPDMYHW>>(sftn-1));
	phwdmy   = PS_PANEL_ACT_HW + DEF_WPDMYHW;
	phwdmynz = PHWNZ  + frx;
	dmynz    = (DEF_WPDMYHW>>sftn);

	dtct  = read_IWARP2(B14_DTCT,0)&0xffff;
    dtsel = (dtct>>4)&0x0f;
	if((PM_WPDTMD==0)&&(dtsel==0))      dtct = 0x0200;
	else if((PM_WPDTMD==0)&&(dtsel!=0)) dtct = 0x0110;
	else if((PM_WPDTMD!=0)&&(dtsel==0)) dtct = 0x0202;
	else				                dtct = 0x0112;
	write_IWARP2(B14_DTCT,dtct,0,0);

	for(y=0; y<=PVWNZ; y++){
		tad = (y<<sftyad);
		write_IWARP2(B14_DTAD,(tad&0xff),0,0);
		write_IWARP2(B14_DTAD,(tad>>8)&0xff,0,0);

		for(x=0; x<=xmax; x++){
			if(x==x2knz){
				tad = x2kad + (y<<sftyad2k);
				write_IWARP2(B14_DTAD,(tad&0xff),0,0);
				write_IWARP2(B14_DTAD,(tad>>8)&0xff,0,0);
			}

			//===== for dummy area process =====//
			if(DEF_WPDMYHW!=0){
				if((x<<sftn)<DEF_WPDMYHW){
					if(Px[0][y]<0) tx = Px[0][y];
					else tx = (Px[0][y]-xstmin)/frx*x + xstmin;
					ty = (Py[0][y]);
				}
				else if((x<<sftn)>phwdmy){
					if(Px[PHWNZ][y]>PS_PANEL_ACT_HW) tx = Px[PHWNZ][y];
					else tx = (xedmax-Px[PHWNZ][y])/brx*(x-phwdmynz) + Px[PHWNZ][y];
					ty = (Py[PHWNZ][y]);
				}
				else{
					xsft = x-dmynz;
					tx = (Px[xsft][y]);
					ty = (Py[xsft][y]);
				}
			}
			else{
				tx = Px[x][y];
				ty = Py[x][y];
			}

			tx = tx/hscl;
			ty = ty/vscl;

			// clip
			if(tx> 2060)	  dtdtx = 0x80c0;
			else if(tx<-1024) dtdtx = 0xc000;
			else			  dtdtx = (int)(tx*16+0.5);
			if(ty> 3071)	  dtdty = 0xbfff;
			else if(ty<-1024) dtdty = 0xc000;
			else			  dtdty = (int)(ty*16+0.5);

			// write warp table
			write_IWARP2(B14_DTDT,dtdtx&0xff,0,0);
			write_IWARP2(B14_DTDT,(dtdtx>>8)&0xff,0,0);
			write_IWARP2(B14_DTDT,dtdty&0xff,0,0);
			write_IWARP2(B14_DTDT,(dtdty>>8)&0xff,0,0);
		} // end for x
	} // end for y

	if((PM_WPDTMD==0)&&(dtsel==0))      dtct = 0x0010;
	else if((PM_WPDTMD==0)&&(dtsel!=0)) dtct = 0x0000;
	else if((PM_WPDTMD!=0)&&(dtsel==0)) dtct = 0x0012;
	else				                dtct = 0x0002;

	write_IWARP2(BN_RTCT,0x7777,0,1);
	write_IWARP2(B14_DTCT,dtct,0,0);
	write_IWARP2(BN_RTCT,0x0000,0,1);

	return;
}
