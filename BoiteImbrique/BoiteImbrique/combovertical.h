#ifndef COMBOVERTICAL_H_
#define COMBOVERTICAL_H_
#include "iboite.h"
#include <string>
using namespace std;

class ComboVertical : public Iboite
{
	int Largeur_;
	string texte_;
public:
	ComboVertical();
	string Emboiter();
};
#endif