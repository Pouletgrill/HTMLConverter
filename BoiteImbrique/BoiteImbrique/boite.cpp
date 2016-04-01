#include "boite.h";

Boite::Boite()
{
	texte_ = "++\n++";
}

Boite::Boite(string t)
{
	largeur_ = Largeur(t);
	texte_ = Emboiter(t);
}

Boite::Boite(Iboite combo)
{
	texte_ = "comboVertical";
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
	return Couche(largeur_)+t+Couche(largeur_);
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
Boite Boite::operator=(const Boite & b)
{
	return Boite(b.texte_);
}
ostream &operator<<(ostream & os, const Boite & b)
{
	os << b.texte_;
	return os;
}
