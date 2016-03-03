/*
Xavier Brosseau
Charlie Laplante
*/
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <regex>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;



bool FileExist(string &filename) 
{
	return ifstream{ filename }.good();
}

template<class it, class T>
bool AnalyseParameter(it debut, it fin, const T &pred)
{
	return find_if(debut,fin,pred)!=fin;
}

template<class it, class T>
bool FindFichier(it param, const T &pred)
{
	return pred(*param) && FileExist(*param);
}

void convertirHtml(bool couleur, bool stat, map<string, int> htmlMap, string filename)
{
	ifstream file(filename);
	vector<string> FileTemp;
	for (string s; getline(file, s);)
		FileTemp.push_back(s);
	

	ofstream myHtmlFile;
	myHtmlFile.open(filename + ".html");//Cr�ation du fichier
										//Header
	myHtmlFile << "<html><head>" << endl <<
		"<head>" << endl <<
		"<title>" << filename << "</title>" << endl <<
		"<meta charset = 'UTF-8'>" << endl <<
		"<link rel = 'stylesheet' type = 'text/css' href = 'Style.css'>" << endl <<
		"</head>" << endl <<
		"<body>" << endl <<
		"<pre>" << endl;



	//Creation du fichier Stats
	if (stat)
	{
		file.open(filename);
		ofstream myfile;
		myfile.open(filename+"Stats.txt");
		//build map
		for (string s; file >> s;)
			htmlMap[s]++;

		regex ExpressKeyWord{ "\\w+" };
		regex ExpressNumeric{ "\\d+\\.*\\d*\\w*" };

		for (auto &p : htmlMap)
		{
			if (regex_match(p.first, ExpressKeyWord) || regex_match(p.first, ExpressNumeric))
			{
				myfile << p.first << " / " << p.second << endl;
			}
		}
		myfile.close();
		file.close();
	}


	//Contenue
	if (couleur)
	{
		file.open(filename);


		vector<string>listCPP = {
			"alignas","alignof","and","and_eq","asm"
			,"auto","bitand","bitor","bool"
			,"break","case","catch","char"
			,"class","compl","const","constexpr"
			,"const_cast","continue","decltype","default"
			,"delete","do","double","dynamic_cast"
			,"else","enum","explicit","export"
			,"extern","false","float","for"
			,"friend","goto","if","inline"
			,"int","include","long","mutable"
			,"namespace","new","noexcept","not"
			,"not_eq","nullptr","operator","or"
			,"or_eq","private","protected","public"
			,"register","reinterpret_cast","return","short"
			,"signed","sizeof","static","static_assert"
			,"static_cast","struct","switch","template"
			,"this","thread_local","throw","true"
			,"try","typedef","typeid","typename"
			,"union","unsigned","using","virtual"
			,"void","volatile","wchar_t","while"
			,"xor","xor_eq" };


		regex Express;
		for (auto & begin : FileTemp)
		{
			begin = regex_replace(begin, regex{ "&" }, "&amp;");
			begin = regex_replace(begin, regex{ "<" }, "&lt;");
			begin = regex_replace(begin, regex{ ">" }, "&gt;");

			for (vector<string>::iterator keywordPos = listCPP.begin(); keywordPos != listCPP.end(); ++keywordPos)
			{
				Express = "\\b" + *keywordPos + "\\b";

				begin = regex_replace(begin, Express, "<span style='color:blue'>" + *keywordPos + "</span>");
			}
			myHtmlFile << begin << "<br>" << flush;
		}
		file.close();
	}
	else
	{
		file.open(filename);

		for (vector<string>::iterator begin = FileTemp.begin(); begin != FileTemp.end(); ++begin)
		{
			*begin = regex_replace(*begin, regex{ "&" }, "&amp;");
			*begin = regex_replace(*begin, regex{ "<" }, "&lt;");
			*begin = regex_replace(*begin, regex{ ">" }, "&gt;");
			myHtmlFile << *begin << "<br>" << flush;
		}
		file.close();
	}
	//footer
	myHtmlFile << "</pre></body></html>" << endl;
	myHtmlFile.close();
}




int main(int argc, char* argv[])
{
	const int nbCoeur = thread::hardware_concurrency();
		

	vector<string> arguments(argv + 1, argv + argc);
	//Forcer des arguments ICI
	//-------------------------
	arguments.push_back("-stat");
	arguments.push_back("-couleur");
	arguments.push_back("fuck.cpp");
	arguments.push_back("fuck - Copie.cpp");
	for (int i = 2; i < 64; i++)
	{
		arguments.push_back("fuck - Copie ("+to_string(i)+").cpp");
	}

	if (!arguments.empty())
	{
		//Check les param�tres
		bool couleur = AnalyseParameter(begin(arguments),
			end(arguments),
			[](string param) {return param == "/couleur" || param == "-couleur"; });
		bool stat = AnalyseParameter(begin(arguments),
			end(arguments),
			[](string param) {return param == "/stat" || param == "-stat"; });
	
		//la map html
		map<string, int> htmlMap;
		
	
		//Sequenciel
		//ce prom�ne dans la liste d'argument pour trouver les fichiers qui existe et qui respectent le predicat
		vector<string>::iterator it = begin(arguments);
		high_resolution_clock::time_point tempSequenceDebut = high_resolution_clock::now();
		for (string filename; it != end(arguments); it++)
		{
			if (FindFichier(it, [](string param) {string str = param.substr(param.find_last_of(".") + 1);
			for (auto & c : str) c = toupper(c); return  str == "CPP"; }))
			{
					filename = *it;	
					convertirHtml(couleur, stat, htmlMap, filename);
			}
		}
		high_resolution_clock::time_point tempSequenceFin = high_resolution_clock::now();
		duration<double> time_span_Seq = duration_cast<duration<double>>(tempSequenceFin - tempSequenceDebut);

		//Parrallele
		vector<thread> lesThreads;
		for (int i = 0; i < nbCoeur; ++i)
		{
			lesThreads.push_back(thread());
		}
	    it = begin(arguments);

		high_resolution_clock::time_point tempParaDebut = high_resolution_clock::now();
		int i = 0;
		for (string filename; it != end(arguments); it++)
		{
			if (FindFichier(it, [](string param) {string str = param.substr(param.find_last_of(".") + 1); for (auto & c : str)
				c = toupper(c); return  str == "CPP"; }))
			{
				filename = *it;
				int tempo = i%nbCoeur;
				if (lesThreads[tempo].joinable())
					lesThreads[tempo].join();
				lesThreads[tempo] = thread(convertirHtml, couleur, stat, htmlMap, filename);
				//lesThreads.push_back(t1);
			}
			++i;
		}
		for (int i = 0; i < nbCoeur; ++i)
		{
			if (lesThreads[i].joinable())
				lesThreads[i].join();
		}
		high_resolution_clock::time_point tempParaFin = high_resolution_clock::now();
		duration<double> time_span_Para = duration_cast<duration<double>>(tempParaFin - tempParaDebut);

		ofstream statfile("statfichier.txt",ios::app);
		statfile << "Nombre de coeur" << nbCoeur << endl;
		statfile << "Pour " << arguments.size()-2 << " fichier"<<endl;
		statfile << "Sequenciel : " << time_span_Seq.count()<<endl;
		statfile << "Parralelle : " << time_span_Para.count() << endl;
		statfile << "--------------------------------------------------------------------" << endl;
		
	
	}
	else
	{
		cout << "vous avez entre aucun parametre" << endl;
	}
}
