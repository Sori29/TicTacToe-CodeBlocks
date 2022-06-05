#include "MeniuJoc.h"
using namespace std;
string numeFisier="date.txt";
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
char meniu() {
	system("cls");
	char optiune;
	PlaySound(TEXT("intro_sound.wav"),NULL,SND_ASYNC);
	SetConsoleTextAttribute(h,10);
	cout<<"  +================================================================================================================+"<<endl;
	cout<<"  |-----------------------------------------Joc X si O realizat de Lungu Sorin-------------------------------------|"<<endl;
	cout<<"  +================================================================================================================+"<<endl;
	SetConsoleTextAttribute(h,9);
	cout << "Apasati 1 pentru a juca impotriva altui jucator." << endl;
	SetConsoleTextAttribute(h,11);
	cout << "Apasati 2 pentru a juca impotriva unui robot" << endl;
	SetConsoleTextAttribute(h,13);
	cout << "Apasati 3 pentru a afisa un joc la alegere"<<endl;
	SetConsoleTextAttribute(h,12);
	cout << "Apasati 0 pentru a iesi din joc" << endl;
	SetConsoleTextAttribute(h,15);
	cin >> optiune;
	PlaySound(NULL, 0, 0);
	return optiune;
}
void salvare_joc(string numeFisier,tictactoe *joc_nou,int nrMeciuri,AdministrareJocuri *adminJocuri){
char alegere;
if(!numeFisier.empty()){
    cout<<"Numele fisierului curent este ";
    SetConsoleTextAttribute(h,14);
    cout<<numeFisier;
    SetConsoleTextAttribute(h,15);
    cout<<" doriti sa schimbati numele fisierului(Y/N):";
    cin>>alegere;
    if(toupper(alegere)=='Y')
        cin>>numeFisier;
}
else{
    cout<<"Introduceti numele fisierului in formatul <name.txt>:";
    cin>>numeFisier;
}
joc_nou->setID(nrMeciuri);
string linie = joc_nou->Conversie_La_Sir_Pentru_Fisier();
int ID=joc_nou->getID();
adminJocuri->AdaugareJoc(numeFisier,linie,ID);
cout << "Fisierul a fost salvat cu sucess\n";
}

void comanda() {
	char comanda;
	char alegere;
	string numeFisier="date.txt";
	tictactoe* joc_nou;
	joc_nou = new tictactoe;
	AdministrareJocuri* adminJocuri;
    adminJocuri = new AdministrareJocuri;
    int nrMeciuri=adminJocuri->GetJocuri(numeFisier);
	do {
        joc_nou->setID(nrMeciuri);
		comanda = meniu();
		switch (comanda) {
		case '1':
			cin.ignore(); //ignorare caractere in plus introduse in buffer pe care functia getline le preia
			joc_nou->initializare_tabla();
			joc_nou->joc();
			nrMeciuri++;
			cout<<"Doriti sa salvati jocul?(Y/N):";
			cin>>alegere;
			if(toupper(alegere)=='Y')
                salvare_joc(numeFisier,joc_nou,nrMeciuri,adminJocuri);
            else nrMeciuri--;
			break;
		case '2':
			cin.ignore();
			joc_nou->initializare_tabla();
			joc_nou->jocVsAI();
            nrMeciuri++;
			cout<<"Doriti sa salvati jocul?(Y/N):";
			cin>>alegere;
			if(toupper(alegere)=='Y')
                salvare_joc(numeFisier,joc_nou,nrMeciuri,adminJocuri);
            else nrMeciuri--;
			break;
        case '3':
            cin.ignore();
            int IDCautat;
            cout<<"Introduceti ID-ul jocului:"; cin>>IDCautat;
            string istoric_joc=adminJocuri->PreluareJoc(numeFisier,IDCautat);
            if(istoric_joc!="Jocul nu a fost gasit")
                joc_nou->Preluare_joc(istoric_joc);
            else cout<<istoric_joc<<"\n";
		}
		system("pause");
	} while (comanda != '0');
	exit(0);
}
