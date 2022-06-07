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
	cout<<"\nIntroduceti optiunea: ";
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
    PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
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
            PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
			joc_nou->joc();
			nrMeciuri++;
			cout<<"Doriti sa salvati jocul?(Y/N):";
			cin>>alegere;
			PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
			if(toupper(alegere)=='Y')
                salvare_joc(numeFisier,joc_nou,nrMeciuri,adminJocuri);
            else if(toupper(alegere)=='N')
                nrMeciuri--;
            else {
                cout<<"Introduceti o valoare valida\n";
                PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
            }
			break;
		case '2':
			char dificultate;
			int dif;
			PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
			while(true){
                cin.ignore();
                cout<<"Alege nivelul de dificultate(0 - Usor / 1 - Dificil):";
                cin>>dificultate;
                if((dificultate=='0' || dificultate=='1') && isdigit(dificultate)){
                    PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
                    dif=dificultate-'0';
                    break;
                }
                else{
                    cout<<"Introduceti o valoare valida\n";
                    PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
                }
			}
			joc_nou->initializare_tabla();
			joc_nou->jocVsAI(dif);
            nrMeciuri++;
			cout<<"Doriti sa salvati jocul?(Y/N):";
			cin>>alegere;
			while(true)
            {
                if(toupper(alegere)=='Y'){
                    PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
                    salvare_joc(numeFisier,joc_nou,nrMeciuri,adminJocuri);
                    break;}
                else if(toupper(alegere)=='N'){
                    nrMeciuri--;
                    PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
                    break;
                }
                else{
                    PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
                    cout<<"Introduceti o valoare valida: ";
                    cin>>alegere;
                }
            }
			break;
        case '3':{
            cin.ignore();
            PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
            int IDCautat;
            cout<<"Introduceti ID-ul jocului:"; cin>>IDCautat;
            string istoric_joc=adminJocuri->PreluareJoc(numeFisier,IDCautat);
            if(istoric_joc!="Jocul nu a fost gasit")
                joc_nou->Preluare_joc(istoric_joc);
            else {
                    PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
                    cout<<istoric_joc<<"\n";}}
            break;
        case '0':
            PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
            break;
        default:
            PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
            cout<<"Introduceti o valoare valida\n";
            break;
		}
		system("pause");
	} while (comanda != '0');
	exit(0);
}
