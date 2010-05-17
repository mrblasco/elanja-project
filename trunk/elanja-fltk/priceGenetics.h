#ifndef GRAPHIC_1_H
#define GRAPHIC_1_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glStats.h"
#include "model.h"

//extern agent agents[];

class priceGenetics : public glStats
{
public:
	priceGenetics(int w,int h,const char *l=0);
	int sides;
	bool grow;
protected:
	void paint();
};

#endif
