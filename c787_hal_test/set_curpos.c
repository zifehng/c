// Set cursor position
#include "inc/header.h"


int check_curpos(str_wppos4c *p4c);
void move_cursor(str_wppos4c *p4c);

int SetCurPos(str_wppos4c *p4c)
{
	int poserr=0;
	
	poserr = check_curpos(p4c);
	
	if(!poserr) move_cursor(p4c);
	
	return (poserr);
}


int check_curpos(str_wppos4c *p4c)
{
	if((p4c->tl_x >  (PS_PANEL_ACT_HW>>1) - DEF_CURSIZE)||(p4c->tl_x <  0)||
	   (p4c->tl_y >= p4c->bl_y)||(p4c->tl_y <  0)||
	   (p4c->tr_x >  PS_PANEL_ACT_HW)||(p4c->tr_x < ((PS_PANEL_ACT_HW>>1) + DEF_CURSIZE))||
	   (p4c->tr_y >= p4c->br_y)||(p4c->tr_y <  0)||
	   (p4c->bl_x >  (PS_PANEL_ACT_HW>>1) - DEF_CURSIZE)||(p4c->bl_x <  0)||
	   (p4c->bl_y >  PS_PANEL_ACT_VW)||(p4c->bl_y <= p4c->tl_y)||
	   (p4c->br_x >  PS_PANEL_ACT_HW)||(p4c->br_x < ((PS_PANEL_ACT_HW>>1) + DEF_CURSIZE))||
	   (p4c->br_y >  PS_PANEL_ACT_VW)||(p4c->br_y <= p4c->tr_y)) return DEF_WPERR_CURPOS;

	return 0;
}

void move_cursor(str_wppos4c *p4c)
{
	write_IWARP2(BN_RTCT,0x0707,0,1);

	write_IWARP2(B16_CURTLX ,p4c->tl_x,0,0);
	write_IWARP2(B16_CURTLY ,p4c->tl_y,0,0);
	write_IWARP2(B16_CURBLX ,p4c->bl_x,0,0);
	write_IWARP2(B16_CURBLY ,(p4c->bl_y - DEF_CURSIZE),0,0);
	write_IWARP2(BN_RTCT,0x0105,0,1);
	wait1_povs();
	write_IWARP2(BN_RTCT,0x0000,0,1);

	return;
}
