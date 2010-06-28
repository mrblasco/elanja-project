#ifndef GRAPHIC_2_H
#define GRAPHIC_2_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glStats.h"
#include "model.h"

class clusteringStats : public glStats
{
public:
	clusteringStats(int w,int h,const char *l=0);
	int sides;
	bool grow;
protected:
	void paint();
};

#endif
