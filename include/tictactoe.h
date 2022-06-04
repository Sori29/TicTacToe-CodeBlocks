#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <bits/stdc++.h>
#include "AdministrareJocuri.h"
using namespace std;

class tictactoe {
public:
	tictactoe(); // constructor implicit
	void afisareTabla()const; // functie de afisare tabla de joc
	void miscareJucator(char jucator); //preluare si verificare pozitie introdusa de utilizator, daca este valida o introduce in matrice
	void miscareAI(char jucator); //simulare miscare robot
	void joc();//functie principala pentru joc cu 2 jucatori
	void jocVsAI(); //functie principala pentru joc 1 jucator vs calculatorul
	void setID(int IDMeci);
	int getID();
	friend char meniu(); // meniu principal
	friend void comanda(); // preluare comanda pentru meniu
	string Conversie_La_Sir_Pentru_Fisier();
	void Preluare_joc(string istoric_joc);

private:
	int IDMeci=0;
	static const int BSIZE = 3; //marimea tablei
	static const int nrMaxMiscari = 9; //numarul maxim de miscari
	static const int nrMinMiscariVictorie = 5; //numarul minim de miscari pentru o victorie
	char tabla[BSIZE][BSIZE]; //declarare tabla de joc
	int buffer[10]={0};
	int nrMiscari=0; //contor de miscari
	int nrVictoriJucator_AI=0; // contor pentru numarul de victorii al jucatorului vs AI
	int nrVictoriAI=0; // contor pentru numarul de victorii al AI
	int nrVictoriJucator1=0;
	int nrVictoriJucator2=0;
	bool verificaVictorie(char jucator)const; //verifica tabla de joc (linie, coloana, diagonala) pentru o victorie
	bool verificaRemiza()const; // verifica daca numarul maxim de miscari a fost atins
	void initializare_tabla(); // initializare tabla de joc cu spatii goale
	char schimbaJucator(char jucator); //schimba semnul la sfarsit de tura (X/0)
};

#endif // TICTACTOE_H
