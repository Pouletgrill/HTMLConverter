#ifndef COMBOHORIZONTAL_H_
#define COMBOHORIZONTAL_H_
#include "icombo.h"
#include "boite.h"

class ComboHorizontal: public icombo
{
	int Largeur_;
	int posmilieu_;
	string texteBrut_;
	Boite a_, b_;
public:
	ComboHorizontal();
	ComboHorizontal(Boite a, Boite b);

	virtual string Emboiter() override;
	virtual int GetLargeur() override;
	virtual int GetPosMilieu() override;
	virtual string GetTexteBrut() override;
};
#endif
