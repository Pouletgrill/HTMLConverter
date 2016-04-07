#include "combovertical.h"

ComboVertical::ComboVertical():
	texte_{},
	Largeur_{}
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

	istringstream iss(a_.GetTexteBrut());
	for (string temp; getline(iss, temp);)
	{
		texte_ += temp + string(Largeur_ - temp.length(), ' ') + "\n";
	}

	texte_ += CoucheMillieu(Largeur_);

	iss = istringstream(b_.GetTexteBrut());
	for (string temp; getline(iss, temp);)
	{
		texte_ += temp + string(Largeur_ - temp.length(), ' ') + "\n";
	}

	return texte_;
}

int ComboVertical::GetLargeur()
{
	return Largeur_;
}

string ComboVertical::GetTexteBrut()
{
	return texte_;
}


string ComboVertical::CoucheMillieu(int longueur)
{
	return  string(longueur, '-') + "\n";
}