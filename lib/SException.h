#pragma once
namespace skn
{


class SException
{
protected :
	string name;
public:
	SException(void);
	SException(char*);
	virtual ~SException(void);
	int code;
	string msg;
	SException* father;
	void printStackTrace();
	void print();
};
class OutOfBoundsException :
	public SException
{
public:
	OutOfBoundsException(void);
	~OutOfBoundsException(void);
};
class NullException :
	public SException
{
public:
	NullException(void);
	~NullException(void);
};
}




