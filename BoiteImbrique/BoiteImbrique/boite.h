#ifndef BOITE_H_
#define BOITE_H_

#include "icombo.h"
#include <string>
#include <sstream>
using namespace std;

class Boite
{
protected:
	string texte_;
	string textBrut_;
	int largeur_;
	int posmilieu_;
public:
	Boite();
	Boite(string t);
	Boite(icombo &combo);
	Boite(const Boite& boite) {//= default;
		texte_    = boite.texte_;
		textBrut_ = boite.textBrut_;
		largeur_  = boite.largeur_;
		posmilieu_ = boite.posmilieu_;
	}
	~Boite();

	string GetTexteBrut() { return textBrut_; }
	int GetLargeur() { return largeur_; }
	int GetPosMilieu() { return posmilieu_; }
	string Emboiter(string t);
	int Largeur(string t);
	string Couche(int largeur);
	friend ostream& operator<<(ostream& os, const Boite& b);
};
#endif