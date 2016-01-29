#include <iostream>
#include <map>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
	if (argc > 1)
	{		
		map<string, int> mots;

		for (int i = 1; i < argc; ++i)
		{
			if (AnalyseFile(argv[i]))
			{
				//ouvre le premier fichier trouver dans les parametres
				ifstream in(argv[i]);

			}
		}
			
	}
	else
	{
		cout << "Pas de parametre" << endl;
	}
	return 0;
}

bool AnalyseParameter(int argc,char* argv[], string param)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == "/"+param || argv[i] == "-"+param)
		{
			return true;
		}	
	}
	return false;
}

bool AnalyseFile(char* filename)
{	
	string exp = filename;
	if (exp.substr(exp.find_first_of(".") + 1) == "cpp")
	{
		return true;
	}
	return false;
}


	