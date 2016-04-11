#include "combovertical.h"

ComboVertical::ComboVertical():
	texteBrut_{},
	Largeur_{}
{

}

ComboVertical::ComboVertical(Boite a, Boite b):
	a_(a),
	b_(b)
{	
	if (a_.GetLargeur() > b_.GetLargeur())
		Largeur_ = a_.GetLargeur();
	else
		Largeur_ = b_.GetLargeur();	
	texteBrut_ = Emboiter();
}

string ComboVertical::Emboiter()
{
	string texte_="";
	istringstream iss(a_.GetTexteBrut());
	for (string temp; getline(iss, temp);)
	{
		if (temp == string(temp.length(), '-'))
			texte_ += CoucheMillieu(Largeur_);
		else
			texte_ += temp + string(Largeur_ - temp.length(), ' ') + "\n";
	}

	texte_ += CoucheMillieu(Largeur_);

	iss = istringstream(b_.GetTexteBrut());
	for (string temp; getline(iss, temp);)
	{
		if (temp == string(temp.length(), '-'))
			texte_ += CoucheMillieu(Largeur_);
		else
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
	return texteBrut_;
}



string ComboVertical::CoucheMillieu(int longueur)
{
	return  string(longueur, '-') + "\n";
}