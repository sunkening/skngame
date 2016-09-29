// GObject.h: interface for the GObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOBJECT_H__D96453C6_4885_4842_853E_6DE9FD76A596__INCLUDED_)
#define AFX_GOBJECT_H__D96453C6_4885_4842_853E_6DE9FD76A596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GObject  
{
public:
	GObject();
	virtual ~GObject();
	virtual bool equals(GObject *o);

};

#endif // !defined(AFX_GOBJECT_H__D96453C6_4885_4842_853E_6DE9FD76A596__INCLUDED_)
