// GRect.h: interface for the GRect class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GRENCT_H
#define GRECCT_H
#include "G2DPoint.h"


class GRect  
{
private:
	G2DPoint leftTop;
	G2DPoint rightBottom;
public:
	GRect(G2DPoint lefttop,G2DPoint rightbottom);
	GRect();
	virtual ~GRect();

};

#endif  
