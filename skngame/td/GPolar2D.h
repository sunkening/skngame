// GPolar2D.h: interface for the GPolar2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPOLAR2D_H__6A626CA4_C46F_44E8_9E3E_345087593B3F__INCLUDED_)
#define AFX_GPOLAR2D_H__6A626CA4_C46F_44E8_9E3E_345087593B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"
//2D¼«×ø±ê
class GPolar2D : public GObject  
{
public:
	GPolar2D();
	virtual ~GPolar2D();
	float r;//°ë¾¶
	float theta;//½Ç¶È
};

#endif // !defined(AFX_GPOLAR2D_H__6A626CA4_C46F_44E8_9E3E_345087593B3F__INCLUDED_)
