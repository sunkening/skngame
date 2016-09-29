// GPoly.h: interface for the GPoly class.
//
//////////////////////////////////////////////////////////////////////
#ifndef GPOLY_H
#define GPOLY_H

#include "GObject.h"
#include "GVector4D.h"
class GPoly : public GObject  
{
public://member variable
	int state;
	int attr;
	int color;
	GVector4D vlist[3];
	GVector4D tvlist[3];
	GPoly * next;
	GPoly * prev;

public:
	GPoly();
	virtual ~GPoly();

};

#endif 
