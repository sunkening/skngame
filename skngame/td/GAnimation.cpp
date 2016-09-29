// GAnimation.cpp: implementation of the GAnimation class.
//
//////////////////////////////////////////////////////////////////////

#include "GAnimation.h"
#include "GameApp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GAnimation::GAnimation()
{
	totalFrames=0;
	id=0;
}

GAnimation::GAnimation(int size)
{
	framesVector.resize(size);
	totalFrames=size;
	id=0;
}

GAnimation::~GAnimation()
{
	vector<GFrame*> ::iterator iter;
	for (iter=framesVector.begin();iter!=framesVector.end();iter++)
	{
		delete (*iter);
	}
}

void GAnimation::addFrame(GFrame* frame)
{
	framesVector.push_back(frame);
	totalFrames++;
}

 

GFrame* GAnimation::getFrame(int index)
{
	if(index<0||index>(totalFrames-1))
		return null;
	return framesVector.at(index);
}

void GAnimation::init(BitMapFile *bitmap,int cell_width,int l,int h)
{
	if (framesVector.size()>0)
	{
		return;
	}
	GRenderer *render=GameApp::getInstance()->getRender();
	int width=bitmap->bitmapinfoheader.biWidth;
	int height=bitmap->bitmapinfoheader.biHeight;
	totalFrames=width/cell_width;
	//framesVector.clear();
	for(int index_x=0;index_x<totalFrames;index_x++){
		BitMapFile *sub=bitmap->getSubImageByIndex(index_x,0,cell_width,height);
		GFrame * frame=render->createFrame(sub,l,h);
		framesVector.push_back(frame);
		delete sub;
	}
}
