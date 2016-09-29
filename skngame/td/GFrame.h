// GFrame.h: interface for the GFrame class.
//
//////////////////////////////////////////////////////////////////////
#ifndef GFRAM_H
#define GFRAM_H

#include "GObject.h"
#include "gl.h"
class GFrame : public GObject  
{

protected :
	int width;
	int height;
	int referenceCount;
	
public:
	int id;
	bool transparent;
public:
	GFrame();
	virtual ~GFrame();
	virtual void* getSurface();
	int getWidth();
	int getHeight();
	int getReferenceCount();
	void setReferenceCount(int count);
	void increaseCount(){referenceCount++;};
	void reduceCount(){referenceCount--;};
	

};

#endif  
