#include"pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
bool func(const string s, const char *ch)
{
	string str = string(ch);
	return ((s.compare(0, str.size(), str)) == 0) ? true : false;
}

vector<string>::iterator prvni(vector<string> *vec, const char *ch)
{
	for (auto it = vec->begin(); it != vec->end(); it++)
	{
		if (func(*it, ch)) 
			return it;
	}
	return vec->end();
}
vector<string>::iterator dalsi(vector<string> *vec, vector<string>::iterator posledni, const char *fil)
{
	for (auto it = posledni + 1; it != vec->end(); it++)
	{
		if (func(*it, fil))
			return it;
	}
	return vec->end();
}

int main()
{
	const char *Jmena[] =
	{ "Marie","Jan","Jana","Petr","Josef","Pavel","Jaroslav","Martin","Miroslav","Eva",
	  "Anna","Hana","Karel","Lenka","Milan","Michal","Alena","Petra","Lucie","Jaroslava",
	  "Ludmila","Helena","David","Ladislav","Marie","Jan","Jana","Petr","Jitka","Martina","Jakub","Veronika","Jarmila","Stanislav",
	  "Michaela","Ivana","Roman","Jarmila","Monika","Tereza","Zuzana","Radek","Vlasta","Marcela","Marek",
	  "Dagmar","Dana","Daniel","Marta","Irena","Monika","Miroslava","Barbora","Ilona","Pavla","Miloslav","Olga",
	  "Andrea","Iveta","Hana","Filip","Ilona","Blanka","Milada","Ivan","Zdenka","Libor","Renata","Rudolf",
	  "Vlastimil","Nikola","Gabriela","Lenka","Adam","Lenka","Milan","Radka","Simona","Milena","Miloslava","Iva","Daniela",
	  "Patrik","Bohumil","Denisa","Robert","Diana","Romana","Aneta","Ilona","Dominik","Jakub","Stanislava","Emilie",
	  "Radim","Richard","Kamila","Ivo","Monika","Rostislav","Vladislav","Bohuslav","Alois","Vit","Kamil",
	  "Jozef","Vendula","Bohumila","Viktor","Emil","Michael","Ladislava","Diana","Magdalena","Eduard","Dominika",
	  "Marcel","Adam","Sabina","Julie","David","Johana","Antonie","Josef","Alice","Peter","Dalibor","Kristina","Otakar","Karla",
	  "Hedvika","Alexandra","Silvie","Erika","Nela","Irena","Vratislav","Nikol","Leona","Jolana","Margita",
	  "Bohuslava","Radovan","Jan","Jana","Josefa","Terezie","Marian","Linda","Igor","Jarmila","Magda","Lada","Bohumir",
	  "Alexandr","Radim","Adriana","Dita","Hana","Vladislava","Otto","Sandra","Radmila","Svatava","Darina","Sylva",
	  "Viktorie","Ivona","David","Monika","Jarmila","Lenka","Bronislava","Elena","Svatopluk","Ivanka","Denis","Adolf","Hynek","Erik",
	  "Bronislav","Jakub","Drahoslava","Petr","Alexander","Robin","Maria","Diana","Lidmila","Vlastislav","Michala","Jindra",
	  "Juraj","Vlastimila","Karin","Zdena","Jan","Josef","Jana","Karolina","Mykola","Pavol","Vanda","Radoslav","Zdenek",
	  "Alenka","Ema","Andrej","Tibor","Anton","Ingrid","Nina","Irena","Viera","Linda","Valerie","Samuel",
	  "Zlata","Lydie","Tamara","Johana","Jan","Jana","Patricie","Julius","Boris","Leopold","Ota","Ester",
	  "Gertruda","Sylvie","Aloisie","Oto","Barbara","Gustav","Marika","Yvona","Jitka","Oksana","Bohdan" };
	vector<string> v;
	for (auto *jmeno : Jmena)
	{
		v.push_back(string (jmeno));
	}
	string s = "Ja";
	cout << *prvni(&v, s.c_str()) << endl;
	vector<string>::iterator i = dalsi(&v, prvni(&v, s.c_str()), s.c_str());
	while (i != v.end())
	{
		cout << *i << endl;
		i = dalsi(&v, i, s.c_str());
	}

}


