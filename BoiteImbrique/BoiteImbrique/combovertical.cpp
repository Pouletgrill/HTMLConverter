#include "combovertical.h"

ComboVertical::ComboVertical()
{
	if (a_.GetLargeur() > b_.GetLargeur())
		Largeur_ = a_.GetLargeur();
	else
		Largeur_ = b_.GetLargeur();
}

string ComboVertical::Emboiter()
{
	texte_ = a_.Couche(Largeur_);
	
	istringstream iss(a_.GetTexte());
	for (string temp; getline(iss, temp);)
	{
		texte_ += "|" + temp + string(Largeur_ - temp.length(), ' ') + "|\n";
	}

	texte_ += a_.Couche(Largeur_);

	iss.str(b_.GetTexte());
	for (string temp; getline(iss, temp);)
	{
		texte_ += "|" + temp + string(Largeur_ - temp.length(), ' ') + "|\n";
	}
	
	return texte_ + a_.Couche(Largeur_);
}

