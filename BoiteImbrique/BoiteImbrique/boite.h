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
public:
	Boite();
	Boite(string t);
	Boite(icombo &combo);
	Boite(const Boite&) = default;
	~Boite();

	string GetTexte() {return textBrut_;}
	int GetLargeur()  {return largeur_;}
	string Emboiter(string t);
	int Largeur(string t);
	string Couche(int largeur);
	friend ostream& operator<<(ostream& os,const Boite& b);
};
#endif