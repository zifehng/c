#include "inc/header.h"

int PM_WPDTMD;		            
float Px[DEF_WPTBLMAX_H][DEF_WPTBLMAX_V];
float Py[DEF_WPTBLMAX_H][DEF_WPTBLMAX_V];
int PHWNZ;			
int PVWNZ;
float PHWHF;
float PVWHF;
int	GPTx[3];		
int	GPTy[3];	
int HMIN;
int my_VMIN;

struct wpkey_param my_wpkey_param;
struct wpkey_param my_wpkey_param_old;

void four_corner_keystone(int corner, int x, int y)
{
#define TOP_LEFT        0
#define TOP_RIGHT       1
#define BOTTOM_LEFT     2
#define BOTTOM_RIGHT    3
    //printf("corner = %d, x = %d, y = %d\n", corner, x, y);

    //printf("before\n");
    //printf("Top Left\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.tl_x, my_wpkey_param.wp_pos4c.tl_y);
    //printf("Top Right\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.tr_x, my_wpkey_param.wp_pos4c.tr_y);
    //printf("Bottom Left\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.bl_x, my_wpkey_param.wp_pos4c.bl_y);
    //printf("Bottom Right\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.br_x, my_wpkey_param.wp_pos4c.br_y);
  
    switch (corner) {
    case TOP_LEFT:
        my_wpkey_param.wp_pos4c.tl_x += x;
        my_wpkey_param.wp_pos4c.tl_y += y;
        break;
    case TOP_RIGHT:
        my_wpkey_param.wp_pos4c.tr_x += x;
        my_wpkey_param.wp_pos4c.tr_y += y;
        break;
    case BOTTOM_LEFT:
        my_wpkey_param.wp_pos4c.bl_x += x;
        my_wpkey_param.wp_pos4c.bl_y += y;
        break;
    case BOTTOM_RIGHT:
        my_wpkey_param.wp_pos4c.br_x += x;
        my_wpkey_param.wp_pos4c.br_y += y;
        break;
    default:
        printf("invalid parameter!\n");
    }
    
    //printf("after\n");
    //printf("Top Left\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.tl_x, my_wpkey_param.wp_pos4c.tl_y);
    //printf("Top Right\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.tr_x, my_wpkey_param.wp_pos4c.tr_y);
    //printf("Bottom Left\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.bl_x, my_wpkey_param.wp_pos4c.bl_y);
    //printf("Bottom Right\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.br_x, my_wpkey_param.wp_pos4c.br_y);

    int ret;
    ret = SetCurPos(&my_wpkey_param.wp_pos4c);
    if (ret == DEF_WPERR_CURPOS) {
        printf("Error : Can't move!!\n\n");
        my_wpkey_param = my_wpkey_param_old;
    } else {
        my_wpkey_param_old = my_wpkey_param;
        SetWpKey4c(&my_wpkey_param.wp_pos4c);
    }
}

int __set_wpkey_ang()
{
    int ret = 0;
  
    ret = Calc4Corner(my_wpkey_param.wpkey_ang_h,  my_wpkey_param.wpkey_ang_v, \
        &my_wpkey_param.pj_param, &my_wpkey_param.wp_pos4c);
    if (ret == DEF_WPERR_NGZ) {
		printf("Error : Projection distance is too short.\n\n");
        my_wpkey_param = my_wpkey_param_old;
    } else {
        ret = SetCurPos(&my_wpkey_param.wp_pos4c);
        if (ret == DEF_WPERR_CURPOS) {
            printf("Error : Can't move!!\n\n");
            my_wpkey_param = my_wpkey_param_old;
        } else {
            my_wpkey_param_old = my_wpkey_param;
            SetWpKey4c(&my_wpkey_param.wp_pos4c);
        }
    }

    return ret;
}

int __set_wpkey_h_ang(float h)
{
    my_wpkey_param.wpkey_ang_h = h;
    return __set_wpkey_ang();
}

int __set_wpkey_v_ang(float v)
{
    my_wpkey_param.wpkey_ang_v = v;
    return __set_wpkey_ang();
}

float __get_wpkey_h_ang()
{
    return my_wpkey_param.wpkey_ang_h;
}

float __get_wpkey_v_ang()
{
    return my_wpkey_param.wpkey_ang_v;
}

void init()
{
    int wpdot;
     
    my_wpkey_param.wpkey_ang_h = 0;
    my_wpkey_param.wpkey_ang_v = 0;
    my_wpkey_param.pj_param.axis = PS_PJPARAM_AXIS;
    my_wpkey_param.pj_param.dist = PS_PJPARAM_DIST;
    my_wpkey_param.pj_param.vw = PS_PJPARAM_VW;
    my_wpkey_param.wp_pos4c.tl_x = 0;
    my_wpkey_param.wp_pos4c.tl_y = 0;
    my_wpkey_param.wp_pos4c.tr_x = PS_PANEL_ACT_HW;
    my_wpkey_param.wp_pos4c.tr_y = 0;
    my_wpkey_param.wp_pos4c.bl_x = 0;
    my_wpkey_param.wp_pos4c.bl_y = PS_PANEL_ACT_VW;
    my_wpkey_param.wp_pos4c.br_x = PS_PANEL_ACT_HW;
    my_wpkey_param.wp_pos4c.br_y = PS_PANEL_ACT_VW;  

    my_wpkey_param_old = my_wpkey_param;


    PM_WPDTMD = 0;
	wpdot = PM_WPDTMD ? 32 : 16;

	// others
	PHWNZ			= (int)(ceilf(PS_PANEL_ACT_HW/(float)wpdot));
	PVWNZ			= (int)(ceilf(PS_PANEL_ACT_VW/(float)wpdot));
	PHWHF 			= PS_PANEL_ACT_HW/2.0;
	PVWHF 			= PS_PANEL_ACT_VW/2.0;
	
	InitWpGrid();				// initialize warp grid
	SetWpGrid(0,0,1);			// select Top Left
	SetCurPos(&my_wpkey_param.wp_pos4c);		// initialize cursor position=
	InitWpTable();				// initialize warp table
	WriteWpTable();				// write warp table
	SetLut();					// set filter coefficient
		
	return;
}


