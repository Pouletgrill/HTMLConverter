#ifndef COMBOHORIZONTAL_H_
#define COMBOHORIZONTAL_H_
#include "icombo.h"
#include "boite.h"

class ComboHorizontal: public icombo
{
	int Largeur_;
	string texte_;
	Boite a_, b_;
public:
	ComboHorizontal();
	ComboHorizontal(Boite a, Boite b);

	virtual string Emboiter() override;
};
#endif
#endif
