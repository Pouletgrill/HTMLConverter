#ifndef COMBOVERTICAL_H_
#define COMBOVERTICAL_H_
#include "icombo.h"
#include "boite.h"

class ComboVertical : public icombo
{
	int Largeur_;
	string texte_;
	Boite a_, b_;
public:
	ComboVertical();
	ComboVertical(Boite a, Boite b);

	virtual string Emboiter() override;
};
#endif