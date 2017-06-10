// Set 4-corner Keystone
#include "inc/header.h"

void wait1_povs()
{
	int		w1osts;
 
	write_IWARP2(B1_INTEN ,0x04,0,1);

	do{
		w1osts = read_IWARP2(B1_INTSTAT,0)&0x04;
	} while(w1osts!=0x04); 

	write_IWARP2(B1_INTEN ,0x00,0,1);

	return ;
}