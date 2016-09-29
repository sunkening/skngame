// PLGFile.cpp: implementation of the PLGFile class.
//
//////////////////////////////////////////////////////////////////////

#include "PLGFile.h"
#include "g3dlib.h"
#include "GColor.h"
#include <IOSTREAM>
#include <STDIO.H>
#include <STRING>
#include <ctype.h>
#include <STDLIB.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLGFile::PLGFile()
{

}

PLGFile::~PLGFile()
{

}

char* PLGFile::getLine(char*buffer,int maxlength,FILE*fp)
{
	int index=0;
	int length=0;
	while (1)
	{
		if (!fgets(buffer,maxlength,fp))
		{
			return 0;
		}
		for (length=strlen(buffer),index=0;isspace(buffer[index]);index++);
		if (index>=length||buffer[index]=='#')
			continue;
		return &buffer[index];
	}
}

int PLGFile::load(G3DObjectIndex*obj,char*filename,GVector4D* scale,GVector4D*pos,GVector4D*rot)
{
	FILE*fp;
	char buffer[256];
	char *token_string;
	obj->state=OBJECT4DV1_STATE_ACTIVE|OBJECT4DV1_STATE_VISIBLE;
	obj->worldPosition.assign(pos);
	//
	if (!(fp=fopen(filename,"r")))
	{
		cout<<"Couldnt open pgl file "<<filename<<endl;
		return 0;
	}
	//
	if (!(token_string=getLine(buffer,255,fp)))
	{
		cout<<"plg object descriptor invalid filename="<<filename<<endl;
		return 0;
	}
	//
	sscanf(token_string,"%s %d %d",obj->name,&obj->numVertices,&obj->numPolys);
	//
	for (int vertex=0;vertex<obj->numVertices;vertex++)
	{
		//
		if (!(token_string=getLine(buffer,255,fp)))
		{
			cout<<"plg vertex list invalid "<<filename<<endl;
			return 0;
		}
		sscanf(token_string,"%f %f %f",&obj->vlistLocal[vertex].x,
			&obj->vlistLocal[vertex].y,
			&obj->vlistLocal[vertex].z);
		obj->vlistLocal[vertex].w=1;
		obj->vlistLocal[vertex].x*=scale->x;
		obj->vlistLocal[vertex].y*=scale->y;
		obj->vlistLocal[vertex].z*=scale->z;
	}
	obj->cumputeRadius();

	int poly_surface_desc=0;
	int poly_num_verts=0;
	char tmp_string[8];
	for (int poly=0;poly<obj->numPolys;poly++)
	{
		if (!(token_string=getLine(buffer,255,fp)))
		{
			cout<<"plg polygon descriptor invalid "<<filename<<endl;
			return 0;
		}
		sscanf(token_string,"%s %d %d %d %d",tmp_string,
			&poly_num_verts,
			&obj->plist[poly].vert[0],
			&obj->plist[poly].vert[1],
			&obj->plist[poly].vert[2]);
		if (tmp_string[0]=='0'&&toupper(tmp_string[1])=='X')
			sscanf(tmp_string,"%x",&poly_surface_desc);
		else
			poly_surface_desc=atoi(tmp_string);
		obj->plist[poly].vlist=obj->vlistLocal;
		if (poly_surface_desc&PLX_2SIDED_FLAG)
		{
			SET_BIT(obj->plist[poly].attr,POLY4DV1_ATTR_2SIDED);
		}
		if (poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG)
		{
			SET_BIT(obj->plist[poly].attr,POLY4DV1_ATTR_RGB16);
			int red   = ((poly_surface_desc & 0x0f00) >> 8);
			int green = ((poly_surface_desc & 0x00f0) >> 4);
			int blue  = (poly_surface_desc & 0x000f);
		 
			obj->plist[poly].color = RGB( blue*16,green*16, red*16);
 
		 
		}
		else
			cout<<"plg 不支持的颜色格式"<<endl;
		int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);
		switch(shade_mode)
		{
		case PLX_SHADE_MODE_PURE_FLAG: {
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_PURE);
									   } break;
			
		case PLX_SHADE_MODE_FLAT_FLAG: {
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_FLAT);
			
									   } break;
			
		case PLX_SHADE_MODE_GOURAUD_FLAG: {
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_GOURAUD);
										  } break;
			
		case PLX_SHADE_MODE_PHONG_FLAG: {
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_PHONG);
										} break;
			
		default: break;
		} // end switch
		
		// finally set the polygon to active
		obj->plist[poly].state = POLY4DV1_STATE_ACTIVE;    
	}
	fclose(fp);
	return 1;
}
