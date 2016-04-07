#ifndef IBOITE_H_
#define IBOITE_H_
#include <string>
using namespace std;

struct icombo
{
public:
	icombo() {};
	virtual string Emboiter() { return{}; };
	virtual int GetLargeur() { return{}; };
	virtual string GetTexteBrut() { return{}; };
};
#endif