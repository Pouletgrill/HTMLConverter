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
	return find_if(debut, fin, pred) != fin;
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
	myHtmlFile << "<html><head>" << "\n" <<
		"<head>" << "\n" <<
		"<title>" << filename << "</title>\n" <<
		"<meta charset = 'UTF-8'>\n" <<
		"<link rel = 'stylesheet' type = 'text/css' href = 'Style.css'>\n" <<
		"</head>\n" <<
		"<body>\n" <<
		"<pre>\n";



	//Creation du fichier Stats
	if (stat)
	{
		file.open(filename);
		ofstream myfile;
		myfile.open(filename + "Stats.txt");
		//build map
		for (string s; file >> s;)
			htmlMap[s]++;

		regex ExpressKeyWord{ "\\w+" };
		regex ExpressNumeric{ "\\d+\\.*\\d*\\w*" };

		for (auto &p : htmlMap)
		{
			if (regex_match(p.first, ExpressKeyWord) || regex_match(p.first, ExpressNumeric))
			{
				myfile << p.first << " / " << p.second << "\n";
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
	myHtmlFile << "</pre></body></html>\n";
	myHtmlFile.close();
}




int main(int argc, char* argv[])
{
	const int nbCoeur = thread::hardware_concurrency();
	ofstream statfile("statfichier.txt", ios::app);
	const int NbFichier = 30;
	for (int k = 1; k <= NbFichier; ++k)
	{

		vector<string> arguments(argv + 1, argv + argc);
		//Forcer des arguments ICI
		//-------------------------
		arguments.push_back("-stat");
		arguments.push_back("-couleur");
		for (int i = 0; i < k; i++)
		{
			arguments.push_back("document1.cpp");
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
			vector<string>::iterator it = begin(arguments);
			
			//Sequenciel
			//ce prom�ne dans la liste d'argument pour trouver les fichiers qui existe et qui respectent le predicat
			
			/**/high_resolution_clock::time_point tempSequenceDebut = high_resolution_clock::now();
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
			duration<double> time_span_Seq = duration_cast<duration<double>>(tempSequenceFin - tempSequenceDebut);/**/

			//Thread Pool
			vector<thread> lesThreads;
			for (int i = 0; i < nbCoeur; ++i)
			{
				lesThreads.push_back(thread());
			}
			it = begin(arguments);

			high_resolution_clock::time_point tempTPDebut = high_resolution_clock::now();
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
				}
				++i;
			}
			for (int i = 0; i < nbCoeur; ++i)
			{
				if (lesThreads[i].joinable())
					lesThreads[i].join();
			}
			high_resolution_clock::time_point tempTPFin = high_resolution_clock::now();
			duration<double> time_span_TP = duration_cast<duration<double>>(tempTPFin - tempTPDebut);

			//Parallele
			vector<thread> lesThreads2;
			for (int i = 0; i < arguments.size(); ++i)
			{
				lesThreads2.push_back(thread());
			}
			it = begin(arguments);

			high_resolution_clock::time_point tempParaDebut = high_resolution_clock::now();
			int i2 = 0;
			for (string filename; it != end(arguments); it++)
			{
				if (FindFichier(it, [](string param) {string str = param.substr(param.find_last_of(".") + 1); for (auto & c : str)
					c = toupper(c); return  str == "CPP"; }))
				{
					filename = *it;
					lesThreads2[i2] = thread(convertirHtml, couleur, stat, htmlMap, filename);
				}
				++i2;
			}
			for (int i2 = 0; i2 < arguments.size(); ++i2)
			{
				if (lesThreads2[i2].joinable())
					lesThreads2[i2].join();
			}
			high_resolution_clock::time_point tempParaFin = high_resolution_clock::now();
			duration<double> time_span_Para = duration_cast<duration<double>>(tempParaFin - tempParaDebut);

			
			statfile << time_span_Seq.count() << "\t" << time_span_TP.count() << "\t" << time_span_Para.count() << "\n";

		}
		else
		{
			cout << "vous avez entre aucun parametre" << endl;
		}
	}
}
