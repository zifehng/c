// Calculate 4-corner position for H/V Keystone
#include "inc/header.h"

typedef struct {
	float x,y,z;
} str_pos3d;
static str_pos3d pos_i[4],pos_r,pos_a[4];

typedef struct {
	float x,y;
} str_pos2d;
static str_pos2d pos_o[4];

static float asp_vph_std;
static float asp_px[5];
static float asp_vlx[5], asp_hly[5];
static float asp_dif[5], asp_vw[5], asp_vph[5];
static float asp_p12a, asp_p12b;
static float asp_p34a, asp_p34b;
static float asp_p13a, asp_p13b;
static float asp_p24a, asp_p24b;

int  angle_to_coord(str_pos3d *pi, float angh, float angv, float dnratio, str_wppos4c *p4c);
void calc_aspect(str_pos2d *pi, float angh, float angv, str_pos3d *po, int *CP);
void rotate(str_pos3d *pi, float angh, float angv, int rev, str_pos3d *po);

void AspSearch(void);
void AspSearchCalc(float *px, float *vlx, float *hly, float *avw, float *avph, float *dif);

int Calc4Corner(float AngH, float AngV, str_pjparam *pjp, str_wppos4c *p4c)
{
	int		cerr=0;
	float	dnratio,upratio;
	float	pz;

	dnratio = pjp->axis;
	upratio = 100 - dnratio;

	pz = (float)PS_PANEL_ACT_VW / (float)pjp->vw * (float)pjp->dist;
	
	pos_i[0].x = (float)(-PS_PANEL_ACT_HW*0.5);
	pos_i[0].y = (float)( PS_PANEL_ACT_VW) * upratio * 0.01;
	pos_i[0].z = pz;

	pos_i[1].x = (float)( PS_PANEL_ACT_HW*0.5);
	pos_i[1].y = pos_i[0].y;
	pos_i[1].z = pz;

	pos_i[2].x = pos_i[0].x;
	pos_i[2].y = (float)(-PS_PANEL_ACT_VW) * dnratio * 0.01;
	pos_i[2].z = pz;

	pos_i[3].x = pos_i[1].x;
	pos_i[3].y = pos_i[2].y;
	pos_i[3].z = pz;

	cerr = angle_to_coord(pos_i,AngH,AngV,dnratio,p4c);
						
	return (cerr);
}


int angle_to_coord(str_pos3d *pi, float angh, float angv, float dnratio, str_wppos4c *p4c)
{
	float	fp1x,fp1y,fp2x,fp2y,fp3x,fp3y,fp4x,fp4y;
	int		CP;
	float	minmvx,minmvy,maxmvx,maxmvy;
	float	p12hw, p34hw, difhw, difmlt;
	float	udmlt;

	//rotate
	rotate(pi  ,angh,angv,0,&pos_r);
	pos_o[0].x = pos_r.x*pi->z/pos_r.z;
	pos_o[0].y = pos_r.y*pi->z/pos_r.z;
	pos_a[0].z = pi->z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	rotate(pi+1,angh,angv,0,&pos_r);
	pos_o[1].x = pos_r.x*pi->z/pos_r.z;
	pos_o[1].y = pos_r.y*pi->z/pos_r.z;
	pos_a[1].z = (pi+1)->z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	rotate(pi+2,angh,angv,0,&pos_r);
	pos_o[2].x = pos_r.x*pi->z/pos_r.z;
	pos_o[2].y = pos_r.y*pi->z/pos_r.z;
	pos_a[2].z = (pi+2)->z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	rotate(pi+3,angh,angv,0,&pos_r);
	pos_o[3].x = pos_r.x*pi->z/pos_r.z;
	pos_o[3].y = pos_r.y*pi->z/pos_r.z;
	pos_a[3].z = (pi+3)->z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	/*aspect conversion*/
	calc_aspect(pos_o,angh,angv,pos_a,&CP);

	//rotate rev
	rotate(pos_a  ,angh,angv,1,&pos_r);
	fp1x = pos_r.x*pi->z/pos_r.z;
	fp1y = pos_r.y*pi->z/pos_r.z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	rotate(pos_a+1,angh,angv,1,&pos_r);
	fp2x = pos_r.x*pi->z/pos_r.z;
	fp2y = pos_r.y*pi->z/pos_r.z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	rotate(pos_a+2,angh,angv,1,&pos_r);
	fp3x = pos_r.x*pi->z/pos_r.z;
	fp3y = pos_r.y*pi->z/pos_r.z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	rotate(pos_a+3,angh,angv,1,&pos_r);
	fp4x = pos_r.x*pi->z/pos_r.z;
	fp4y = pos_r.y*pi->z/pos_r.z;
	if(pos_r.z <= 0) return DEF_WPERR_NGZ;

	//upside-down
	fp1y = -fp1y;
	fp2y = -fp2y;
	fp3y = -fp3y;
	fp4y = -fp4y;

	//rotate_h -5 ~ 5
	p12hw = fp2x - fp1x;
	p34hw = fp4x - fp3x;
	difhw = (p12hw > p34hw) ? p12hw : p34hw;
	difmlt = ((angh < -5) | (angh > 5)) ? 0
			: (angh < 0) ? (5 + angh) * 0.2
			: (5 - angh) * 0.2;

	udmlt = ((dnratio>100)|(dnratio<0)) ? 1 : 0;
			
	difhw = ((float)PS_PANEL_ACT_HW - difhw) * udmlt * difmlt * 0.5;
	
	//Movement
	minmvx = (fp1x > fp3x) ? fp3x : fp1x;
	minmvx -= difhw;
	minmvy = (fp1y > fp2y) ? fp2y : fp1y;
	maxmvx = (fp2x > fp4x) ? fp2x - (float)PS_PANEL_ACT_HW : fp4x - (float)PS_PANEL_ACT_HW;
	maxmvx += difhw;
	maxmvy = (fp3y > fp4y) ? fp3y - (float)PS_PANEL_ACT_VW : fp4y - (float)PS_PANEL_ACT_VW;
			
	fp1x = ((CP == 1) | (CP == 3)) ? fp1x - minmvx : fp1x - maxmvx;
	fp2x = ((CP == 1) | (CP == 3)) ? fp2x - minmvx : fp2x - maxmvx;
	fp3x = ((CP == 1) | (CP == 3)) ? fp3x - minmvx : fp3x - maxmvx;
	fp4x = ((CP == 1) | (CP == 3)) ? fp4x - minmvx : fp4x - maxmvx;
	fp1y = ((CP == 1) | (CP == 2)) ? fp1y - minmvy : fp1y - maxmvy;
	fp2y = ((CP == 1) | (CP == 2)) ? fp2y - minmvy : fp2y - maxmvy;
	fp3y = ((CP == 1) | (CP == 2)) ? fp3y - minmvy : fp3y - maxmvy;
	fp4y = ((CP == 1) | (CP == 2)) ? fp4y - minmvy : fp4y - maxmvy;
	
	//Round
	p4c->tl_x = (int)floorf(fp1x+0.5);
	p4c->tr_x = (int)floorf(fp2x+0.5);
	p4c->bl_x = (int)floorf(fp3x+0.5);
	p4c->br_x = (int)floorf(fp4x+0.5);
	p4c->tl_y = (int)floorf(fp1y+0.5);
	p4c->tr_y = (int)floorf(fp2y+0.5);
	p4c->bl_y = (int)floorf(fp3y+0.5);
	p4c->br_y = (int)floorf(fp4y+0.5);

	//Overflow
	p4c->tl_x = (p4c->tl_x < 0) ? 0 : p4c->tl_x;
	p4c->tl_y = (p4c->tl_y < 0) ? 0 : p4c->tl_y;
	p4c->tr_x = (p4c->tr_x > PS_PANEL_ACT_HW) ? PS_PANEL_ACT_HW : p4c->tr_x;
	p4c->tr_y = (p4c->tr_y < 0) ? 0 : p4c->tr_y;
	p4c->bl_x = (p4c->bl_x < 0) ? 0 : p4c->bl_x;
	p4c->bl_y = (p4c->bl_y > PS_PANEL_ACT_VW) ? PS_PANEL_ACT_VW : p4c->bl_y;
	p4c->br_x = (p4c->br_x > PS_PANEL_ACT_HW) ? PS_PANEL_ACT_HW : p4c->br_x;
	p4c->br_y = (p4c->br_y > PS_PANEL_ACT_VW) ? PS_PANEL_ACT_VW : p4c->br_y;

	return 0;
}

void rotate(str_pos3d *pi, float angh, float angv, int rev, str_pos3d *po)
{
	float	x1,y1,z1;
	float	rad_h,rad_v;
	float	cos_rh,cos_rv,sin_rh,sin_rv;

	rad_h  = DEF_PI*angh/180.0;
	rad_v  = DEF_PI*angv/180.0;

	if(rev==0){
		// X ax roation
		cos_rv = cosf(-rad_v);
		sin_rv = sinf(-rad_v);
		x1 =  pi->x;
		y1 =  pi->y*cos_rv - pi->z*sin_rv;
		z1 =  pi->y*sin_rv + pi->z*cos_rv;
		// Y ax roation
		cos_rh = cosf(rad_h);
		sin_rh = sinf(rad_h);
		po->x =  x1*cos_rh + z1*sin_rh;
		po->y =  y1;
		po->z = -x1*sin_rh + z1*cos_rh;
	}
	else{
		// Y ax roation
		cos_rh = cosf(-rad_h);
		sin_rh = sinf(-rad_h);
		x1 =  pi->x*cos_rh + pi->z*sin_rh;
		y1 =  pi->y;
		z1 = -pi->x*sin_rh + pi->z*cos_rh;
		// X ax roation
		cos_rv = cosf(rad_v);
		sin_rv = sinf(rad_v);
		po->x =  x1;
		po->y =  y1*cos_rv - z1*sin_rv;
		po->z =  y1*sin_rv + z1*cos_rv;
	}	
	
	return;
}

void calc_aspect(str_pos2d *pi, float angh, float angv, str_pos3d *po, int *CP)
{
	float P1x_tmp, P1y_tmp;
	float P2x_tmp, P2y_tmp;
	float P3x_tmp, P3y_tmp;
	float P4x_tmp, P4y_tmp;

	float dlb = 0;
	float tmp, tmph;
	float hv, vv, dlv;

	float ASPHW, ASPVW;
	float as1y_tmp;
	float as2x_tmp;
	float as3x_tmp, as3y_tmp;
	int lp;

	asp_vph_std = (float)PS_PANEL_ACT_VW / (float)PS_PANEL_ACT_HW;

	*CP = ((angh<0) & (angv<=0)) ? 2
		: (angv<=0) ? 1
		: (angh<0)  ? 4
		: 3;

	P1x_tmp = (*CP == 1) ? (pi+2)->x
		: (*CP == 2) ? -(pi+3)->x
		: (*CP == 4) ? -(pi+1)->x
		: pi->x;
	P2x_tmp = (*CP == 1) ? (pi+3)->x
		: (*CP == 2) ? -(pi+2)->x
		: (*CP == 4) ? -pi->x
		: (pi+1)->x;
	P3x_tmp = (*CP == 1) ? pi->x
		: (*CP == 2) ? -(pi+1)->x
		: (*CP == 4) ? -(pi+3)->x
		: (pi+2)->x;
	P4x_tmp = (*CP == 1) ? (pi+1)->x
		: (*CP == 2) ? -pi->x
		: (*CP == 4) ? -(pi+2)->x
		: (pi+3)->x;

	P1y_tmp = (*CP == 1) ? -(pi+2)->y
		: (*CP == 2) ? -(pi+3)->y
		: (*CP == 4) ? (pi+1)->y
		: pi->y;
	P2y_tmp = (*CP == 1) ? -(pi+3)->y
		: (*CP == 2) ? -(pi+2)->y
		: (*CP == 4) ? pi->y
		: (pi+1)->y;
	P3y_tmp = (*CP == 1) ? -pi->y
		: (*CP == 2) ? -(pi+1)->y
		: (*CP == 4) ? (pi+3)->y
		: (pi+2)->y;
	P4y_tmp = (*CP == 1) ? -(pi+1)->y
		: (*CP == 2) ? -pi->y
		: (*CP == 4) ? (pi+2)->y
		: (pi+3)->y;

	asp_p12a = (P1x_tmp == P2x_tmp) ? 2147483648 // div 0
		: (P1y_tmp - P2y_tmp) / (P1x_tmp - P2x_tmp);
	asp_p12b = P1y_tmp - asp_p12a * P1x_tmp;

	asp_p34a = (P3x_tmp == P4x_tmp) ? 2147483648 // div 0
		: (P3y_tmp - P4y_tmp) / (P3x_tmp - P4x_tmp);
	asp_p34b = P4y_tmp - asp_p34a * P4x_tmp;

	asp_p13a = (P1x_tmp == P3x_tmp) ? 2147483648 // div 0
		: (P1y_tmp - P3y_tmp) / (P1x_tmp - P3x_tmp);
	asp_p13b = P1y_tmp - asp_p13a * P1x_tmp;

	asp_p24a = (P2x_tmp == P4x_tmp) ? 2147483648 // div 0
		: (P2y_tmp - P4y_tmp) / (P2x_tmp - P4x_tmp);
	asp_p24b = P4y_tmp - asp_p24a * P4x_tmp;

	if (asp_p34a <= 0) {
		dlb = P3y_tmp - asp_vph_std * P3x_tmp;

		tmp = (asp_p24a == 0) ? 2147483648 // div 0
			: (P3y_tmp - asp_p24b) / asp_p24a;
		tmph = tmp - P3x_tmp;
		hv = tmph * asp_vph_std;

		tmp = asp_p12a * P3x_tmp + asp_p12b;
		vv = tmp - P3y_tmp;

		tmp = (asp_p12a == asp_vph_std) ? 2147483648 // div 0
			: (dlb - asp_p12b) / (asp_p12a - asp_vph_std);
		tmph = tmp - P3x_tmp;
		dlv = tmph * asp_vph_std;

		ASPVW = ((hv <= vv) & (hv <= dlv)) ? hv
			: (vv <= dlv) ? vv
			: dlv;
		ASPHW = ASPVW / asp_vph_std;

		tmph = P4x_tmp - P3x_tmp;
		tmp = (angh == 0) ? tmph - ASPHW : 0;

		as3x_tmp = P3x_tmp + tmp*0.5;
		as3y_tmp = P3y_tmp;
	}
	else {
		asp_px[0] = P3x_tmp;
		asp_px[4] = P4x_tmp;
		AspSearchCalc(&asp_px[0], &asp_vlx[0], &asp_hly[0], &asp_vw[0], &asp_vph[0], &asp_dif[0]);
		AspSearchCalc(&asp_px[4], &asp_vlx[4], &asp_hly[4], &asp_vw[4], &asp_vph[4], &asp_dif[4]);

		for (lp = 0; lp < 8; lp++) {
			AspSearch();
		}

		if (asp_dif[4] >= 0) {
			tmp = (asp_vph[4] == 0) ? 2147483648 : asp_vph_std / asp_vph[4];
			ASPVW = asp_vw[4] * tmp;
			as3x_tmp = asp_vlx[4];
			as3y_tmp = asp_hly[4];
		}
		else {
			tmp = (asp_vph[0] == 0) ? 2147483648 : asp_vph_std / asp_vph[0];
			ASPVW = asp_vw[0] * tmp;
			as3x_tmp = asp_vlx[0];
			as3y_tmp = asp_hly[0];
		}

		ASPHW = ASPVW / asp_vph_std;
	}

	as1y_tmp = as3y_tmp + ASPVW;
	as2x_tmp = as3x_tmp + ASPHW;

	//output
	po->x     = ((*CP == 1) | (*CP == 3)) ? as3x_tmp : -as2x_tmp;
	po->y     = ((*CP == 1) | (*CP == 2)) ? -as3y_tmp : as1y_tmp;
	(po+1)->x = ((*CP == 1) | (*CP == 3)) ? as2x_tmp : -as3x_tmp;
	(po+1)->y = po->y;
	(po+2)->x = po->x;
	(po+2)->y = ((*CP == 1) | (*CP == 2)) ? -as1y_tmp : as3y_tmp;
	(po+3)->x = (po+1)->x;
	(po+3)->y = (po+2)->y;
}

void AspSearch(void)
{
	float tmp;
	int p, flg;

	tmp = (asp_px[4] - asp_px[0]) * 0.25;
	asp_px[1] = asp_px[0] + tmp;
	asp_px[2] = asp_px[1] + tmp;
	asp_px[3] = asp_px[2] + tmp;

	for (p = 1; p <= 3; p++) {
		AspSearchCalc(&asp_px[p], &asp_vlx[p], &asp_hly[p], &asp_vw[p], &asp_vph[p], &asp_dif[p]);
	}

	flg = ((asp_dif[0] < 0) | (asp_dif[1] < 0)) ? 0
		: (asp_dif[2] < 0) ? 1
		: (asp_dif[3] < 0) ? 2
		: 3;

	if(flg == 0) {
		asp_px[4] = asp_px[1];
		asp_vlx[4] = asp_vlx[1];
		asp_hly[4] = asp_hly[1];
		asp_vw[4] = asp_vw[1];
		asp_vph[4] = asp_vph[1];
		asp_dif[4] = asp_dif[1];
	}
	else if(flg == 1) {
		asp_px[0] = asp_px[1];
		asp_vlx[0] = asp_vlx[1];
		asp_hly[0] = asp_hly[1];
		asp_vw[0] = asp_vw[1];
		asp_vph[0] = asp_vph[1];
		asp_dif[0] = asp_dif[1];
		asp_px[4] = asp_px[2];
		asp_vlx[4] = asp_vlx[2];
		asp_hly[4] = asp_hly[2];
		asp_vw[4] = asp_vw[2];
		asp_vph[4] = asp_vph[2];
		asp_dif[4] = asp_dif[2];
	}
	else if(flg == 2) {
		asp_px[0] = asp_px[2];
		asp_vlx[0] = asp_vlx[2];
		asp_hly[0] = asp_hly[2];
		asp_vw[0] = asp_vw[2];
		asp_vph[0] = asp_vph[2];
		asp_dif[0] = asp_dif[2];
		asp_px[4] = asp_px[3];
		asp_vlx[4] = asp_vlx[3];
		asp_hly[4] = asp_hly[3];
		asp_vw[4] = asp_vw[3];
		asp_vph[4] = asp_vph[3];
		asp_dif[4] = asp_dif[3];
	}
	else {
		asp_px[0] = asp_px[3];
		asp_vlx[0] = asp_vlx[3];
		asp_hly[0] = asp_hly[3];
		asp_vw[0] = asp_vw[3];
		asp_vph[0] = asp_vph[3];
		asp_dif[0] = asp_dif[3];
	}
}

void AspSearchCalc(float *px, float *vlx, float *hly, float *avw, float *avph, float *dif)
{
	float hlpy;
	float ahw;

	*hly = asp_p34a * (*px) + asp_p34b;
	*vlx = (asp_p13a == 0) ? 2147483648 // div 0
		: (*hly - asp_p13b) / asp_p13a;
	hlpy = asp_p12a * (*vlx) + asp_p12b;
	ahw = (*px >= *vlx) ? floorf(*px - *vlx + 0.5) : floorf(*vlx - (*px) + 0.5);
	*avw = (*hly >= hlpy) ? floorf(*hly - hlpy + 0.5) : floorf(hlpy - *hly + 0.5);
	*avph = (ahw == 0) ? 2147483648 // div 0
		: (*avw) / ahw;
	*dif = *avph - asp_vph_std;
}
