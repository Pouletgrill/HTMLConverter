#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;



bool FileExist(string filename)
{
	ifstream infile(filename);
	return infile.good();
}

template<class it, class T>
bool AnalyseParameter(it debut,it end, const T &pred)
{
	for (; debut != end; ++debut)
	{
		if (pred(*debut))
			return true;
	}
	return false;
}

template<class it, class T>
bool FindFichier(it param, const T &pred)
{
	if (pred(*param) && FileExist(*param))
		return true;
	else
		return false;
}

void convertirHtml(bool couleur,bool stat,ifstream& file, map<string, int> htmlMap)
{
	//build map
	for (string s; file >> s;)
		htmlMap[s]++;

	for (auto &p : htmlMap)
		cout << p.first << "/" << p.second << endl;
}


int main(int argc, char* argv[])
{
	vector<string> arguments(argv, argv + argc);
	/*string listHtml[] = {
		"<!DOCTYPE>","<a>",
		"<abbr>","<acronym>",
		"<address>","<applet>",
		"<area>","<article>",
		"<aside>","<audio>",
		"<b>","<base>",
		"<basefont>","<bdi>",
		"<bdo>","<big>",
		"<blockquote>",	"<body>",
		"<br>","<button>",
		"<canvas>","<caption>",
		"<center>","<cite>",
		"<code>","<col>",
		"<colgroup>	","<command>",
		"<datalist>	","<dd>",
		"<del>","<details>",
		"<dfn>","<dir>",
		"<div>","<dl>",
		"<dt>","<em>",
		"<embed>","<fieldset>",
		"<figcaption>",	"<figure>",
		"<font>","<footer>",
		"<form>","<frame>",
		"<frameset>","<h1>",
		"<h2>","<h3>",
		"<h4>","<h5>",
		"<h6>","<head>",
		"<header>","<hgroup>",
		"<hr>","<html>",
		"<i>","<iframe>",
		"<img>","<input>",
		"<ins>","<kbd>",
		"<keygen>","<label>",
		"<legend>","<li>",
		"<link>","<map>",
		"<mark>","<menu>",
		"<meta>","<meter>",
		"<nav>","<noframes>",
		"<noscript>","<object>",
		"<ol>","<optgroup>",
		"<option>","<output>",
		"<p>","<param>",
		"<pre>","<progress>",
		"<q>","<rp>",
		"<rt>","<ruby>",
		"<s>","<samp>",
		"<script>","<section>",
		"<select>","<small>",
		"<source>","<span>",
		"<strike>","<strong>",
		"<style>","<sub>",
		"<summary>","<sup>",
		"<table>","<tbody>",
		"<td>","<textarea>",
		"<tfoot>","<th>",
		"<thead>","<time>",
		"<title>","<tr>",
		"<track>","<tt>",
		"<u>","<ul>",
		"<var>","<video>",
		"<wbr>" };*/
	string listCPP[] = {
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
		,"xor_eq"
	};

	//Enlever premier argument qui est le nom de l'executable
	arguments.erase(arguments.begin());
	if (!arguments.empty())
	{	
		//Check les paramètres
		bool couleur = AnalyseParameter(begin(arguments), end(arguments), [](string param) {return param == "/couleur" || param == "-couleur"; });
		bool stat = AnalyseParameter(begin(arguments), end(arguments), [](string param) {return param == "/stat" || param == "-stat"; });
		
		//la map html
		map<string, int> htmlMap;

		//ce promène dans la liste d'argument pour trouver les fichiers qui existe et qui respectent le predicat
		vector<string>::iterator it = begin(arguments);
		for (string filename;it!=end(arguments);it++)
		{		   
			if (FindFichier(it, [](string param) {return param.substr(param.find_last_of(".") + 1) == "cpp"; }))
			{
				filename = *it;	
				ifstream in(filename);
				convertirHtml(couleur,stat,in,htmlMap);
			}			
		}	
	}
	else
	{
		cout << "Pas de parametre" << endl;
	}
	return 0;
}
	