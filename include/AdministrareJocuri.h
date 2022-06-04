#ifndef ADMINISTRAREJOCURI_H
#define ADMINISTRAREJOCURI_H


#include <bits/stdc++.h>
#include "tictactoe.h"
using namespace std;
class AdministrareJocuri
{
	private:
		string numeFisier;
	public:
		AdministrareJocuri();
		AdministrareJocuri(string numeFisier);
		void AdaugareJoc(string numeFisier,string linie,int ID);
		int GetJocuri(string numeFisier);
		string PreluareJoc(string numeFisier,int index);

};

#endif // ADMINISTRAREJOCURI_H
