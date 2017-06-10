// Set LUT of pixel interpolation filter coefficient
#include "inc/header.h"

extern void calclut(float fratio, float fwindow, int symbol, int LUT[24]);
extern void lutset_6s_c03w00(int LUT[24]); // 6symbol, cutoff=0.3, window=0.0
extern void lutset_6s_c04w00(int LUT[24]); // 6symbol, cutoff=0.4, window=0.0
extern void lutset_6s_c05w00(int LUT[24]); // 6symbol, cutoff=0.5, window=0.0
extern void lutset_6s_c06w00(int LUT[24]); // 6symbol, cutoff=0.6, window=0.0
extern void lutset_6s_c07w00(int LUT[24]); // 6symbol, cutoff=0.7, window=0.0
extern void lutset_6s_c08w00(int LUT[24]); // 6symbol, cutoff=0.8, window=0.0
extern void lutset_6s_c09w00(int LUT[24]); // 6symbol, cutoff=0.9, window=0.0
extern void lutset_6s_c10w00(int LUT[24]); // 6symbol, cutoff=1.0, window=0.0
extern void lutset_6s_c10w10(int LUT[24]); // 6symbol, cutoff=1.0, window=1.0
extern void lutset_6s_c10w15(int LUT[24]); // 6symbol, cutoff=1.0, window=1.5

void SetLut_wplg(void)
{
	int		HLUT[24],VLUT[24];
	int		i;
	float	hscl,vscl,hwin,vwin;
	float	max;

	// +++++ HLUT +++++ //
	max = 1;

	hscl = (double)HMIN/PS_PANEL_ACT_HW - 0.1;
	hscl = (hscl>DEF_LUTCUT_MAX) ? DEF_LUTCUT_MAX :
		   (hscl<DEF_LUTCUT_MIN) ? DEF_LUTCUT_MIN : hscl; // limit
	hwin = (hscl<1.0) ? 0 : (hscl+1)*0.5;
	hwin = (hwin>DEF_LUTWIN_MAX) ? DEF_LUTWIN_MAX :
		   (hwin<DEF_LUTWIN_MIN) ? DEF_LUTWIN_MIN : hwin; // limit

	calclut(hscl,hwin,DEF_LUTSYM,HLUT);

	// +++++ VLUT +++++ //
	max = 1;

	vscl = (double)my_VMIN/PS_PANEL_ACT_VW - 0.1;
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

