#include "combohorizontal.h"

ComboHorizontal::ComboHorizontal():
	texteBrut_{},
	Largeur_{}
{

}

ComboHorizontal::ComboHorizontal(Boite a, Boite b):	
	a_(a),
	b_(b)
{
	Largeur_= a_.GetLargeur()+b_.GetLargeur();
	texteBrut_ = Emboiter();
	posmilieu_ = a_.GetLargeur();
}

string ComboHorizontal::Emboiter()
{
	
	string texte_ = "";
	bool FlagTempA = true;
	bool FlagTempB = true;
	istringstream issA(a_.GetTexteBrut());
	istringstream issB(b_.GetTexteBrut());

	string tempExtraLine = "";

	for (string tempA="", tempB=""; FlagTempA || FlagTempB;)
	{
		if (FlagTempA = (bool)getline(issA, tempA)){}

		if (FlagTempB = (bool)getline(issB, tempB)){}		

		if (FlagTempA || FlagTempB)
		{
			tempExtraLine = tempA + string(a_.GetLargeur() - tempA.length(), ' ');
			if (tempExtraLine == string(tempExtraLine.length(), ' ') && a_.GetPosMilieu() != 0)
			{
				tempExtraLine[a_.GetPosMilieu()] = '|';
				texte_ += tempExtraLine;
			}				
			else
				texte_ += tempExtraLine;
			texte_ += "|";			
			

			tempExtraLine = tempB + string(b_.GetLargeur() - tempB.length(), ' ');
			if (tempExtraLine == string(tempExtraLine.length(), ' ') && b_.GetPosMilieu()!=0)
			{
				
				tempExtraLine[b_.GetPosMilieu()] = '|';
				texte_ += tempExtraLine;
			}				
			else
				texte_ += tempExtraLine;
			texte_ += "\n";
		}		

		tempA = tempB = "";
	}
	Largeur_++;
	return texte_;
}

int ComboHorizontal::GetLargeur()
{
	return Largeur_;
}
int ComboHorizontal::GetPosMilieu()
{
	return posmilieu_;
}
string ComboHorizontal::GetTexteBrut()
{
	return texteBrut_;
}
