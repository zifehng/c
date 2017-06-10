// Init warp table
#include "inc/header.h"


void InitWpTable(void)
{
	int x,y;
	int sftn;

	sftn = PM_WPDTMD ? 5 : 4;
	
	for(y=PVWNZ; y>=0; y--){
		for(x=PHWNZ; x>=0; x--){
			Px[x][y] = (x<<sftn);
			Py[x][y] = (y<<sftn);
		}
	}
	
	return;
}
