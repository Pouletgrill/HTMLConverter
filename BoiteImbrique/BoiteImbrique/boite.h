#ifndef BOITE_H_
#define BOITE_H_
#include "iboite.h"
#include <string>
#include <sstream>
using namespace std;

class Boite
{
	string texte_;
	int largeur_;
public:
	Boite();
	Boite(string t);
/**/	Boite(Iboite combo); //*/
	~Boite();

	string Emboiter(string t);
	int Largeur(string t);
	string Couche(int largeur);
	friend ostream& operator<<(ostream& os,const Boite& b);
	Boite operator=(const Boite& b);
};
#endif