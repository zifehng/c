// Set LUT of pixel interpolation filter coefficient
#include "inc/header.h"

void calclut(float fratio, float fwindow, int symbol, int LUT[24]);
void lutset_6s_c03w00(int LUT[24]); // 6symbol, cutoff=0.3, window=0.0
void lutset_6s_c04w00(int LUT[24]); // 6symbol, cutoff=0.4, window=0.0
void lutset_6s_c05w00(int LUT[24]); // 6symbol, cutoff=0.5, window=0.0
void lutset_6s_c06w00(int LUT[24]); // 6symbol, cutoff=0.6, window=0.0
void lutset_6s_c07w00(int LUT[24]); // 6symbol, cutoff=0.7, window=0.0
void lutset_6s_c08w00(int LUT[24]); // 6symbol, cutoff=0.8, window=0.0
void lutset_6s_c09w00(int LUT[24]); // 6symbol, cutoff=0.9, window=0.0
void lutset_6s_c10w00(int LUT[24]); // 6symbol, cutoff=1.0, window=0.0
void lutset_6s_c10w10(int LUT[24]); // 6symbol, cutoff=1.0, window=1.0
void lutset_6s_c10w15(int LUT[24]); // 6symbol, cutoff=1.0, window=1.5

void SetLut(void)
{
	int		HLUT[24],VLUT[24];
	int		i;
	float	hscl,vscl,hwin,vwin;
	float	max,r;

	// +++++ HLUT +++++ //
	max = 1;
	for(i=PVWNZ; i>=0; i--){
		r = fabsf(Px[PHWNZ][i] - Px[0][i]);
		if(max<r) max = r;
	}
	hscl = PS_PANEL_ACT_HW/max - 0.1;
	hscl = (hscl>DEF_LUTCUT_MAX) ? DEF_LUTCUT_MAX :
		   (hscl<DEF_LUTCUT_MIN) ? DEF_LUTCUT_MIN : hscl; // limit
	hwin = (hscl<1.0) ? 0 : (hscl+1)*0.5;
	hwin = (hwin>DEF_LUTWIN_MAX) ? DEF_LUTWIN_MAX :
		   (hwin<DEF_LUTWIN_MIN) ? DEF_LUTWIN_MIN : hwin; // limit

	calclut(hscl,hwin,DEF_LUTSYM,HLUT);

	// +++++ VLUT +++++ //
	max = 1;
	for(i=PHWNZ; i>=0; i--){
		r = fabsf(Py[i][PVWNZ] - Py[i][0]);
		if(max<r) max = r;
	}
	vscl = PS_PANEL_ACT_VW/max; - 0.1;
	vscl = (vscl>DEF_LUTCUT_MAX) ? DEF_LUTCUT_MAX :
		   (vscl<DEF_LUTCUT_MIN) ? DEF_LUTCUT_MIN : vscl; // limit
	vwin = (vscl<1.0) ? 0 : (vscl+1)*0.5;
	vwin = (vwin>DEF_LUTWIN_MAX) ? DEF_LUTWIN_MAX :
		   (vwin<DEF_LUTWIN_MIN) ? DEF_LUTWIN_MIN : vwin; // limit

	calclut(vscl,vwin,DEF_LUTSYM,VLUT);

	// +++++ set LUT registers +++++ //
	write_IWARP2(BN_RTCT,0x0707,0,1);
	for(i=23; i>=0; i--) write_IWARP2(B15_HLUT0+(i<<8),HLUT[i]&0xff,0,0);	// ch1 HLUT0-23
	for(i=23; i>=0; i--) write_IWARP2(B15_VLUT0+(i<<8),VLUT[i]&0xff,0,0);	// ch1 VLUT0-23
	write_IWARP2(BN_RTCT,0x0105,0,1);
	wait1_povs();
	write_IWARP2(BN_RTCT,0x0000,0,1);

	return;
}



void calclut(float fratio, float fwindow, int symbol, int LUT[24])
{
	if(fratio<0.4)      lutset_6s_c03w00(LUT);
	else if(fratio<0.5) lutset_6s_c04w00(LUT);
	else if(fratio<0.6) lutset_6s_c05w00(LUT);
	else if(fratio<0.7) lutset_6s_c06w00(LUT);
	else if(fratio<0.8) lutset_6s_c07w00(LUT);
	else if(fratio<0.9) lutset_6s_c08w00(LUT);
	else if(fratio<1.0) lutset_6s_c09w00(LUT);
	else if(fratio<1.1) lutset_6s_c10w00(LUT);
	else if(fratio<1.5) lutset_6s_c10w10(LUT);
	else                lutset_6s_c10w15(LUT);

	return;
}

void lutset_6s_c03w00(int LUT[24])
{
	LUT[0]  = 0x02;
	LUT[1]  = 0x03;
	LUT[2]  = 0x04;
	LUT[3]  = 0x04;
	LUT[4]  = 0x05;
	LUT[5]  = 0x06;
	LUT[6]  = 0x07;
	LUT[7]  = 0x08;
	LUT[8]  = 0x09;
	LUT[9]  = 0x09;
	LUT[10] = 0x0a;
	LUT[11] = 0x0b;
	LUT[12] = 0x0c;
	LUT[13] = 0x0c;
	LUT[14] = 0x0d;
	LUT[15] = 0x0e;
	LUT[16] = 0x0e;
	LUT[17] = 0x0f;
	LUT[18] = 0x0f;
	LUT[19] = 0x11;
	LUT[20] = 0x12;
	LUT[21] = 0x13;
	LUT[22] = 0x13;
	LUT[23] = 0x14;

	return;
}

void lutset_6s_c04w00(int LUT[24])
{
	LUT[0]  = 0xfe;
	LUT[1]  = 0xff;
	LUT[2]  = 0xff;
	LUT[3]  = 0x00;
	LUT[4]  = 0x01;
	LUT[5]  = 0x02;
	LUT[6]  = 0x03;
	LUT[7]  = 0x05;
	LUT[8]  = 0x06;
	LUT[9]  = 0x08;
	LUT[10] = 0x09;
	LUT[11] = 0x0b;
	LUT[12] = 0x0c;
	LUT[13] = 0x0e;
	LUT[14] = 0x0f;
	LUT[15] = 0x10;
	LUT[16] = 0x12;
	LUT[17] = 0x13;
	LUT[18] = 0x14;
	LUT[19] = 0x15;
	LUT[20] = 0x17;
	LUT[21] = 0x16;
	LUT[22] = 0x18;
	LUT[23] = 0x16;

	return;
}

void lutset_6s_c05w00(int LUT[24])
{
	LUT[0]  = 0xfa;
	LUT[1]  = 0xfa;
	LUT[2]  = 0xfa;
	LUT[3]  = 0xfb;
	LUT[4]  = 0xfc;
	LUT[5]  = 0xfd;
	LUT[6]  = 0xff;
	LUT[7]  = 0x00;
	LUT[8]  = 0x02;
	LUT[9]  = 0x04;
	LUT[10] = 0x06;
	LUT[11] = 0x09;
	LUT[12] = 0x0c;
	LUT[13] = 0x0e;
	LUT[14] = 0x11;
	LUT[15] = 0x11;
	LUT[16] = 0x16;
	LUT[17] = 0x18;
	LUT[18] = 0x1a;
	LUT[19] = 0x1c;
	LUT[20] = 0x1e;
	LUT[21] = 0x1f;
	LUT[22] = 0x1e;
	LUT[23] = 0x1e;

	return;
}

void lutset_6s_c06w00(int LUT[24])
{
	LUT[0]  = 0xfb;
	LUT[1]  = 0xf9;
	LUT[2]  = 0xf8;
	LUT[3]  = 0xf8;
	LUT[4]  = 0xf7;
	LUT[5]  = 0xf8;
	LUT[6]  = 0xf9;
	LUT[7]  = 0xfb;
	LUT[8]  = 0xfc;
	LUT[9]  = 0xff;
	LUT[10] = 0x01;
	LUT[11] = 0x04;
	LUT[12] = 0x08;
	LUT[13] = 0x0c;
	LUT[14] = 0x10;
	LUT[15] = 0x13;
	LUT[16] = 0x18;
	LUT[17] = 0x1d;
	LUT[18] = 0x21;
	LUT[19] = 0x24;
	LUT[20] = 0x27;
	LUT[21] = 0x27;
	LUT[22] = 0x28;
	LUT[23] = 0x24;

	return;
}

void lutset_6s_c07w00(int LUT[24])
{
	LUT[0]  = 0x00;
	LUT[1]  = 0xff;
	LUT[2]  = 0xfc;
	LUT[3]  = 0xfa;
	LUT[4]  = 0xf8;
	LUT[5]  = 0xf7;
	LUT[6]  = 0xf6;
	LUT[7]  = 0xf6;
	LUT[8]  = 0xf7;
	LUT[9]  = 0xf8;
	LUT[10] = 0xfb;
	LUT[11] = 0xfe;
	LUT[12] = 0x01;
	LUT[13] = 0x06;
	LUT[14] = 0x0c;
	LUT[15] = 0x12;
	LUT[16] = 0x17;
	LUT[17] = 0x1d;
	LUT[18] = 0x23;
	LUT[19] = 0x28;
	LUT[20] = 0x2d;
	LUT[21] = 0x2f;
	LUT[22] = 0x30;
	LUT[23] = 0x30;

	return;
}

void lutset_6s_c08w00(int LUT[24])
{
	LUT[0]  = 0x05;
	LUT[1]  = 0x04;
	LUT[2]  = 0x02;
	LUT[3]  = 0x00;
	LUT[4]  = 0xfe;
	LUT[5]  = 0xfb;
	LUT[6]  = 0xf8;
	LUT[7]  = 0xf5;
	LUT[8]  = 0xf5;
	LUT[9]  = 0xf5;
	LUT[10] = 0xf6;
	LUT[11] = 0xf8;
	LUT[12] = 0xfc;
	LUT[13] = 0x00;
	LUT[14] = 0x05;
	LUT[15] = 0x0d;
	LUT[16] = 0x13;
	LUT[17] = 0x1a;
	LUT[18] = 0x21;
	LUT[19] = 0x28;
	LUT[20] = 0x2d;
	LUT[21] = 0x32;
	LUT[22] = 0x36;
	LUT[23] = 0x3c;

	return;
}

void lutset_6s_c09w00(int LUT[24])
{
	LUT[0]  = 0x06;
	LUT[1]  = 0x07;
	LUT[2]  = 0x06;
	LUT[3]  = 0x05;
	LUT[4]  = 0x03;
	LUT[5]  = 0x00;
	LUT[6]  = 0xfe;
	LUT[7]  = 0xfa;
	LUT[8]  = 0xf8;
	LUT[9]  = 0xf6;
	LUT[10] = 0xf5;
	LUT[11] = 0xf5;
	LUT[12] = 0xf7;
	LUT[13] = 0xfb;
	LUT[14] = 0x00;
	LUT[15] = 0x06;
	LUT[16] = 0x0e;
	LUT[17] = 0x16;
	LUT[18] = 0x1e;
	LUT[19] = 0x26;
	LUT[20] = 0x2d;
	LUT[21] = 0x32;
	LUT[22] = 0x36;
	LUT[23] = 0x40;

	return;
}

void lutset_6s_c10w00(int LUT[24])
{
	LUT[0]  = 0x02;
	LUT[1]  = 0x04;
	LUT[2]  = 0x06;
	LUT[3]  = 0x07;
	LUT[4]  = 0x07;
	LUT[5]  = 0x05;
	LUT[6]  = 0x03;
	LUT[7]  = 0x00;
	LUT[8]  = 0xfd;
	LUT[9]  = 0xf9;
	LUT[10] = 0xf6;
	LUT[11] = 0xf4;
	LUT[12] = 0xf4;
	LUT[13] = 0xf6;
	LUT[14] = 0xfa;
	LUT[15] = 0x00;
	LUT[16] = 0x08;
	LUT[17] = 0x11;
	LUT[18] = 0x1b;
	LUT[19] = 0x25;
	LUT[20] = 0x2e;
	LUT[21] = 0x37;
	LUT[22] = 0x3c;
	LUT[23] = 0x40;

	return;
}

void lutset_6s_c10w10(int LUT[24])
{
    LUT[0] 	= 0x00;
    LUT[1] 	= 0x00;
    LUT[2]	= 0x00;
    LUT[3]	= 0x01;
    LUT[4]	= 0x01;
    LUT[5]	= 0x01;
    LUT[6]	= 0x01;
    LUT[7]	= 0x00;
    LUT[8]	= 0xff;
    LUT[9]	= 0xfd;
    LUT[10]	= 0xfb;
    LUT[11]	= 0xf9;
    LUT[12]	= 0xf8;
    LUT[13]	= 0xf9;
    LUT[14]	= 0xfc;
    LUT[15]	= 0x00;
    LUT[16]	= 0x06;
    LUT[17]	= 0x0f;
    LUT[18]	= 0x1a;
    LUT[19]	= 0x26;
    LUT[20]	= 0x32;
    LUT[21]	= 0x3a;
    LUT[22]	= 0x3e;
    LUT[23]	= 0x40;

	return;
}

void lutset_6s_c10w15(int LUT[24])
{
    LUT[0] 	= 0x00;
    LUT[1]	= 0x00;
    LUT[2]	= 0x00;
    LUT[3]	= 0x00;
    LUT[4]	= 0x00;
    LUT[5]	= 0x00;
    LUT[6]	= 0x00;
    LUT[7]	= 0x00;
    LUT[8]	= 0x00;
    LUT[9]	= 0xff;
    LUT[10]	= 0xfe;
    LUT[11]	= 0xfd;
    LUT[12]	= 0xfc;
    LUT[13]	= 0xfc;
    LUT[14]	= 0xfd;
    LUT[15]	= 0x00;
    LUT[16]	= 0x05;
    LUT[17]	= 0x0d;
    LUT[18]	= 0x18;
    LUT[19]	= 0x23;
    LUT[20]	= 0x2e;
    LUT[21]	= 0x38;
    LUT[22]	= 0x3e;
    LUT[23] = 0x40;

	return;
}
