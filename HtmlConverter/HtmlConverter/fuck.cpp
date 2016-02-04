void convertirHtml(bool couleur, bool stat, map<string, int> htmlMap, string filename)
{
	ifstream file(filename);

	//Creation du fichier Stats
	if (stat)
	{
		ofstream myfile;
		myfile.open("Stats.txt");
		//build map
		for (string s; file >> s;)
			htmlMap[s]++;

		for (auto &p : htmlMap)
			myfile << p.first << " / " << p.second << endl;
		myfile.close();
	}qw
22222222222231231231243535
5145
134
543
5145134
5145
3
	ofstream myHtmlFile;
	myHtmlFile.open(filename + ".html");//Création du fichier
										//Header
	myHtmlFile << "<html><head>" << endl <<
		"<head>" << endl <<
		"<title>" << filename << "</title>" << endl <<
		"<meta charset = 'UTF-8'>" << endl <<
		"<link rel = 'stylesheet' type = 'text/css' href = 'Style.css'>" << endl <<
		"</head>" << endl <<
		"<body>" << endl;

	//Contenue
	if (couleur)
	{
		myHtmlFile << filename << " + couleur" << "<br>";
		ifstream in(filename);
		
		vector<string> FileTemp;
		for (string s; getline(in, s);)
			FileTemp.push_back(s);
	

		vector<string> listCPP = {
			"alignas"
			,"alignof"
			,"and"
			,"and_eq"
			,"asm"
			,"auto"
			,"bitand"
			,"bitor"
			,"bool"
			,"break"
			,"case"
			,"catch"
			,"char"
			,"class"
			,"compl"
			,"const"
			,"constexpr"
			,"const_cast"
			,"continue"
			,"decltype"
			,"default"
			,"delete"
			,"do"
			,"double"
			,"dynamic_cast"
			,"else"
			,"enum"
			,"explicit"
			,"export"
			,"extern"
			,"false"
			,"float"
			,"for"
			,"friend"
			,"goto"
			,"if"
			,"inline"
			,"int"
			,"long"
			,"mutable"
			,"namespace"
			,"new"
			,"noexcept"
			,"not"
			,"not_eq"
			,"nullptr"
			,"operator"
			,"or"
			,"or_eq"
			,"private"
			,"protected"
			,"public"
			,"register"
			,"reinterpret_cast"
			,"return"
			,"short"
			,"signed"
			,"sizeof"
			,"static"
			,"static_assert"
			,"static_cast"
			,"struct"
			,"switch"
			,"template"
			,"this"
			,"thread_local"
			,"throw"
			,"true"
			,"try"
			,"typedef"
			,"typeid"
			,"typename"
			,"union"
			,"unsigned"
			,"using"
			,"virtual"
			,"void"
			,"volatile"
			,"wchar_t"
			,"while"
			,"xor"
			,"xor_eq" };

		regex expression1;
	

		for (vector<string>::iterator begin = FileTemp.begin(); begin != FileTemp.end(); ++begin)
		{
			
			for (vector<string>::iterator keywordPos = listCPP.begin(); keywordPos != listCPP.end(); ++keywordPos)
			{
				 expression1 = "\\b" + *keywordPos + "\\b";
				
				*begin = regex_replace(*begin, expression1, "<span style='color:blue'>" + *keywordPos + "</span>");
				
			}
			myHtmlFile << *begin << "<br>" << flush;
		}
	}
	else
	{
		myHtmlFile << filename << endl;
		ifstream doc(filename);
		if(doc.is_open())
			for (string line=""; getline(doc, line);)
			{
				myHtmlFile << line << "<br/>"<<endl;
			}
		else
		{
			cout << " problemo " << endl;
		}
		doc.close();
	}	


	//footer
	myHtmlFile << "</body></html>" << endl;
	myHtmlFile.close();
}




int main(int argc, char* argv[])
{
	vector<string> arguments(argv, argv + argc);
	arguments.push_back("-couleur");	
	arguments.push_back("fuck.cpp");

	

	//Enlever premier argument qui est le nom de l'executable
	arguments.erase(arguments.begin());
	if (!arguments.empty())
	{
		double bitch;
		//Check les paramètres
		bool couleur = AnalyseParameter(begin(arguments), end(arguments), [](string param) {return param == "/couleur" || param == "-couleur"; });
		bool stat = AnalyseParameter(begin(arguments), end(arguments), [](string param) {return param == "/stat" || param == "-stat"; });

		//la map html
		map<string, int> htmlMap;

		//ce promène dans la liste d'argument pour trouver les fichiers qui existe et qui respectent le predicat
		vector<string>::iterator it = begin(arguments);
		for (string filename; it != end(arguments); it++)
		{
			if (FindFichier(it, [](string param) {string str = param.substr(param.find_last_of(".") + 1);
			for (auto & c : str) c = toupper(c); return  str == "CPP"; }))
			{
				filename = *it;
				
				convertirHtml(couleur, stat, htmlMap, filename);
				
			}
		}
	}
	else
	{
		cout << "Pas de parametre" << endl;
	}
	return 0;
}
