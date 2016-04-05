#ifndef IBOITE_H_
#define IBOITE_H_
#include "boite.h"

struct Iboite
{
protected:
	Boite a_, b_;
public:
	Iboite();
	Iboite(Boite a, Boite b);
	virtual string Emboiter() = 0;
};
#endif