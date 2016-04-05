#include "combovertical.h"

ComboVertical::ComboVertical()
{

}

ComboVertical::ComboVertical(Boite a, Boite b):
	texte_{},
	a_(a),
	b_(b)
{
	if (a_.GetLargeur() > b_.GetLargeur())
		Largeur_ = a_.GetLargeur();
	else
		Largeur_ = b_.GetLargeur();
}

string ComboVertical::Emboiter()
{

	istringstream iss(a_.GetTexte());
	for (string temp; getline(iss, temp);)
	{
		texte_ += "|" + temp + string(Largeur_ - temp.length(), ' ') + "|\n";
	}

	texte_ += a_.Couche(Largeur_);

	iss = istringstream(b_.GetTexte());
	for (string temp; getline(iss, temp);)
	{
		texte_ += "|" + temp + string(Largeur_ - temp.length(), ' ') + "|\n";
	}

	return a_.Couche(Largeur_) + texte_ + a_.Couche(Largeur_);
}

