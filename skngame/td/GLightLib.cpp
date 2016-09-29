// GLightLib.cpp: implementation of the GLightLib class.
//
//////////////////////////////////////////////////////////////////////

#include "GLightLib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GLightLib::GLightLib()
{
	numLights=0;	
}

GLightLib::~GLightLib()
{

}

void GLightLib::reset()
{
	//memset(lights,0,);
	numLights=0;
}

int GLightLib::insert(GLight*light)
{
	if (numLights >= MAX_LIGHTS)
	{
		return 0;
	}
	lights[numLights]=light;
	numLights++;
	return 1;
}
