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
	bool fini = false;
	for (string tempA, tempB; !fini;)
	{
		fini = true;
		if (getline(issA, tempA))
		{
			texte_ += tempA + string(a_.GetLargeur() - tempA.length(), ' ') + "|";
			fini = false;
		}	
		else
		{
			texte_ += string(a_.GetLargeur(), ' ')+"|";
		}

		if (getline(issB, tempB))
		{
			texte_ += tempB + string(b_.GetLargeur()+1 - tempB.length(), ' ') + "\n";
			fini = false;
		}
		else
		{
			texte_ += string(b_.GetLargeur(), ' ') + "|";
		}
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
