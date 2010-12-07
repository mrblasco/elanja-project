#ifndef GRAPHIC_3_H
#define GRAPHIC_3_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glStats.h"
#include "model.h"

class maxRegionStats : public glStats
{
public:
	maxRegionStats(int w,int h,const char *l=0);
	int maxRegionHistory[STATS2_W];
protected:
	void paint();
};

#endif
