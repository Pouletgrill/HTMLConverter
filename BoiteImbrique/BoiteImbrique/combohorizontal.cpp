#include "combohorizontal.h"

ComboHorizontal::ComboHorizontal():
	texte_{},
	Largeur_{}
{

}

ComboHorizontal::ComboHorizontal(Boite a, Boite b):
	texte_{},
	a_(a),
	b_(b)
{
	Largeur_= a_.GetLargeur()+b_GetLargeur();	
}

string ComboHorizontal::Emboiter()
{
	istringstream issA(a_.GetTexte());
	istringstream issB(a_.GetTexte());

	for (string tempA,tempB; getline(issA, tempA) || getline(issB, tempB);)
	{
		texte_ += "|" + tempA + string(a_.GetLargeur() - tempA.length(), ' ') + "|"+tempB + string(b_GetLargeur() - tempB.length(), ' ') + "|\n";
	}

	return a_.Couche(Largeur_) + texte_ + a_.Couche(Largeur_);	

}

