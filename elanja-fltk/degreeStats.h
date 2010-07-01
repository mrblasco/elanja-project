#ifndef GRAPHIC_1_H
#define GRAPHIC_1_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glStats.h"
#include "model.h"

class degreeStats : public glStats
{
public:
	degreeStats(int w,int h,const char *l=0);
	double degreeHistory[5][20];
protected:
	void paint();
};

#endif
