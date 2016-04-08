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
	Largeur_= a_.GetLargeur()+b_.GetLargeur();	
}

string ComboHorizontal::Emboiter()
{
	istringstream issA(a_.GetTexteBrut());
	istringstream issB(b_.GetTexteBrut());

	for (string tempA, tempB; getline(issA, tempA) && getline(issB, tempB);)
	{

			texte_ += tempA + string(a_.GetLargeur() - tempA.length(), ' ') + "|";

			texte_ += tempB + string(b_.GetLargeur() - tempB.length(), ' ') + "\n";
			tempA = tempB = " ";
	}
	Largeur_++;
	return texte_;

}

int ComboHorizontal::GetLargeur()
{
	return Largeur_;
}


string ComboHorizontal::GetTexteBrut()
{
	return texte_;
}
