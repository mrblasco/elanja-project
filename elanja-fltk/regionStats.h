#ifndef GRAPHIC_1_H
#define GRAPHIC_1_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glStats.h"
#include "model.h"

class regionStats : public glStats
{
public:
	regionStats(int w,int h,const char *l=0);
protected:
	void paint();
};

#endif
