#ifndef GRAPHIC_2_H
#define GRAPHIC_2_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glStats.h"
#include "model.h"

class regionCountStats : public glStats
{
public:
	regionCountStats(int w,int h,const char *l=0);
     	double regionHistory[STATS2_W];		

protected:
	void paint();
};

#endif
