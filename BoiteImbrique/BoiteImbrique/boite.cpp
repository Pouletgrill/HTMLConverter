#include "boite.h";

Boite::Boite()
{
	texte_ = "++\n++";
	textBrut_ = "";
	largeur_ = 0;
	posmilieu_ = 0;	
}

Boite::Boite(string t)
{
	largeur_ = Largeur(t);
	posmilieu_= 0;
	textBrut_ = t;
	texte_ = Couche(largeur_) + Emboiter(t)+ Couche(largeur_);
}

Boite::Boite(icombo &combo)
	:largeur_(combo.GetLargeur()),
	posmilieu_(combo.GetPosMilieu()),
	textBrut_(combo.GetTexteBrut())
{	
	istringstream iss(textBrut_);
	texte_ =  "+" + string(combo.GetLargeur(), '-') + "+\n";
	for (string temp; getline(iss, temp);)
	{
		texte_ += "|" + temp +"|\n";
	}
	texte_ += "+" + string(combo.GetLargeur(), '-') + "+";
}
Boite::~Boite()
{
	
}
string Boite::Emboiter(string t)
{
	istringstream iss(t);
	t = "";
	for (string temp; getline(iss, temp);)
	{
		t += "|" + temp + string(largeur_ - temp.length(), ' ') + "|\n";
	}
	return t;
}

int Boite::Largeur(string t)
{
	istringstream iss(t);
	int largeur = 0;
	for (string temp; getline(iss, temp);)
	{
		if (temp.length() > largeur)
			largeur = temp.length();
	}
	return largeur;
}
string Boite::Couche(int largeur)
{
	return "+"+string(largeur, '-')+"+\n";
}

ostream &operator<<(ostream & os, const Boite & b)
{
	os << b.texte_;
	return os;
}
