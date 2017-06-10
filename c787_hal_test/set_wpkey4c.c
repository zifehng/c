// Set 4-corner Keystone
#include "inc/header.h"

int SetWpKey4c(str_wppos4c *p4c)
{
	CalcHomography(p4c);

	SetLut_wplg();

	return 0;
}
