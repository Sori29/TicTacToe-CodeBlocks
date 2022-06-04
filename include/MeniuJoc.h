#ifndef MENIUJOC_H
#define MENIUJOC_H


#include <bits/stdc++.h>
#include "tictactoe.h"
#include "AdministrareJocuri.h"
using namespace std;

void comanda();
char meniu();
void salvare_joc(string numeFisier,tictactoe *joc_nou,int nrMeciuri,AdministrareJocuri *adminJocuri);


#endif // MENIUJOC_H
