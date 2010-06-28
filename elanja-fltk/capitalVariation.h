#ifndef CAPITAL_VARIATION
#define CAPITAL_VARIATION

#include <stdlib.h>
#include "glStats.h"
#include "model.h"

class capitalVariation: public glStats{
public:
	capitalVariation(int w,int h,const char *l=0);
	double *capital_history;
	double *capital_avg_history;
protected:
	void paint();
};

#endif
