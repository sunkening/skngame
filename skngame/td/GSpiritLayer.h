// GSpiritLayer.h: interface for the GSpiritLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSPIRITLAYER_H__C0BA1DFA_1AC0_4085_B779_4F5FC05CECF3__INCLUDED_)
#define AFX_GSPIRITLAYER_H__C0BA1DFA_1AC0_4085_B779_4F5FC05CECF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLayer.h"
#include "gl.h"
class GSpiritLayer : public GLayer  
{
protected:


public:
	GSpiritLayer();
	GSpiritLayer(int id);
	virtual ~GSpiritLayer();
	map<int,GParticleEngine*> particleEngineMap;
	GFrame* grid;
public:

	void particleProcess();
	int addParticleEngine(GParticleEngine*);
	void deleteParticleEngine(int id);
	
	virtual GFrame* getGrid(GViewPort* view);
	
};

#endif // !defined(AFX_GSPIRITLAYER_H__C0BA1DFA_1AC0_4085_B779_4F5FC05CECF3__INCLUDED_)
