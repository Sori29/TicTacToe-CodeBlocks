#include "tictactoe.h"
tictactoe::tictactoe() {
	initializare_tabla();
}

void tictactoe::initializare_tabla() {
	nrMiscari = 0;
	for (int row = 0; row < BSIZE; row++) {
		for (int col = 0; col < BSIZE; col++) {
			tabla[row][col] = ' ';
		}
	}
}
void tictactoe::afisareTabla()const {
	cout << " --------------\n";
	for (int row = 0; row < BSIZE; row++) {
		cout << " | ";
		for (int col = 0; col < BSIZE; col++) {
			cout << tabla[row][col] << "  |";
		}

		cout << "\n --------------\n";
	}
}
void tictactoe::miscareJucator(char jucator) {
	//declarare variabile
	string input; //salveaza caracterul introdus de utilizator
	char char_entered; //verifica caracterul
	int num_entered, row, col, index;
	int rand_jucator;
	if (jucator == 'X') {
		rand_jucator = 1;
	}
	else {
		rand_jucator = 2;
	}
	while (true) {
		cout << "Player " << rand_jucator << " Unde vrei sa joci? Alege un numar intre 1-9: " << endl;
		getline(cin,input);

		if (input != "") {
			//convertire string la cstring
			char_entered = input.c_str()[0];
			if (char_entered >= '1' && char_entered <= '9') {
				//Daca introducerea este intre intervalul dorit, convertim la tipul int
				num_entered = char_entered - '0';
				//folosim acest numar pentru a gasi pozitia pe tabla de joc si de a salva miscarea
				index = num_entered - 1;
				row = index / 3;
				col = index % 3;
				//verificam daca spatiul gasit este gol
				char b_pos = tabla[row][col];
				if (b_pos != 'X' && b_pos != 'O') {
					//daca miscarea este corecta, introduce
					tabla[row][col] = jucator;
					buffer[nrMiscari] = num_entered;
					nrMiscari++;
					break;
					//in caz contrar, afiseaza mesaj de eroare
				}
				else
					cout << "Miscare gresita. Pozitia este deja ocupata. Incercati din nou" << endl;
			}
			else
				cout << "Trebuie sa introduceti un numar intre 1-9. Incercati din nou. \n";
		}
		else
			cout << "Trebuie sa introduceti ceva!" << endl;
	}
	cout << "Numar total miscari: " << nrMiscari << endl;
}

char tictactoe::schimbaJucator(char jucator) {

	jucator = jucator == 'X' ? 'O' : 'X';
	return (jucator);
}

bool tictactoe::verificaVictorie(char jucator)const {
	//verifica victorie doar cand numarul total de miscari este mai mare sau egal decat numarul minim de miscari pentru o victorie
	if (nrMiscari >= nrMinMiscariVictorie) {
		//verifica randuri
		if (tabla[0][0] == jucator && tabla[0][1] == jucator && tabla[0][2] == jucator) {
			return true;
		}
		if (tabla[1][0] == jucator && tabla[1][1] == jucator && tabla[1][2] == jucator)
		{
			return true;
		}
		if (tabla[2][0] == jucator && tabla[2][1] == jucator && tabla[2][2] == jucator)
		{
			return true;
		}
		//verificare coloane
		if (tabla[0][0] == jucator && tabla[1][0] == jucator && tabla[2][0] == jucator)
		{
			return true;
		}
		if (tabla[0][1] == jucator && tabla[1][1] == jucator && tabla[2][1] == jucator)
		{
			return true;
		}
		if (tabla[0][2] == jucator && tabla[1][2] == jucator && tabla[2][2] == jucator)
		{
			return true;
		}
		//verificare diagonale
		if (tabla[0][0] == jucator && tabla[1][1] == jucator && tabla[2][2] == jucator)
		{
			return true;
		}
		if (tabla[0][2] == jucator && tabla[1][1] == jucator && tabla[2][0] == jucator)
		{
			return true;
		}

	}
	return false;

}

bool tictactoe::verificaRemiza()const {
	return nrMiscari == nrMaxMiscari;
}

void tictactoe::joc() {
    cout<<"ID-ul meciului este: "<<IDMeci+1<<endl;
	cout << "SCORUL (PLAYER 1 VS PLAYER 2): " <<nrVictoriJucator1 << "-" << nrVictoriJucator2 << endl;
	char jucator = 'X'; //initializare jucator
	bool gameOver = false;
	do {
		afisareTabla();
		miscareJucator(jucator);
		PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
		if (verificaVictorie(jucator)) {
			if (jucator == 'X')
				nrVictoriJucator1++;
			else
				nrVictoriJucator2++;
			cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
				<< jucator << " A CASTIGAT!!" << endl;
			gameOver = true;
		}
		else if (verificaRemiza()) {
			cout << "ESTE O REMIZA! Jucati din nou!" << endl;
			gameOver = true;
		}
		jucator = schimbaJucator(jucator);
	} while (gameOver != true);

	afisareTabla();
}
void tictactoe::miscareAI(char jucator) {
	srand(time_t(NULL)); //initializare generator de numar la intamplare .
	while (true) {

		int numar_rand = (rand() % 9) + 1;
		int row = (numar_rand - 1) / 3;
		int col = (numar_rand - 1) % 3;
		char bpos = tabla[row][col];
		//verificare daca pozitia este goala
		if (bpos == 'X' || bpos == 'O') { //daca da, atunci alege alt numar
			continue;
		}
		else { //daca nu, introduce simbolul pe pozitia aleasa
			cout << "Calculator a ales pozitia: " << numar_rand << endl;
			tabla[row][col] = jucator;
			buffer[nrMiscari] = numar_rand;
			nrMiscari++;
			break;
		}
	}
	cout << "Numar total de miscari: " << nrMiscari << endl;
}
void tictactoe::jocVsAI() {
    cout<<"ID-ul meciului este: "<<IDMeci+1<<endl;
	cout << "SCORUL (PLAYER VS AI) " << nrVictoriJucator_AI << "-" << nrVictoriAI<<endl;
	string input;
	char jucator=0;
	do {
		cout << "Introduceti cu ce doriti sa jucati (X/O)\n";
			getline(cin, input);
			if (toupper(input[0]) == 'X' or toupper(input[0]) == 'O') {
				jucator = toupper(input[0]);
				break;
			}
			if (toupper(input[0]) != 'X' or toupper(input[0]) != 'O')
				cout << "Introduceti o valoare valida\n";
	} while (jucator != 'X' or jucator != 'O');
	bool gameOver = false;
	if (jucator == 'X')
	{
		do {
				afisareTabla();
				miscareJucator(jucator);
				PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
				if (verificaVictorie(jucator)) {
					if (jucator == 'X')
						nrVictoriJucator_AI++;
					else
						nrVictoriAI++;
					cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
						<< jucator << " A CASTIGAT!!" << endl;
					gameOver = true;
					break;
				}
				else if (verificaRemiza()) {
					cout << "ESTE O REMIZA! Jucati din nou!" << endl;
					gameOver = true;
					break;
				}
				jucator = schimbaJucator(jucator);
				miscareAI(jucator); //comp jucator
				PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
				if (verificaVictorie(jucator)) {
					cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
						<< jucator << " A CASTIGAT!!" << endl;
					gameOver = true;
					break;
				}
				else if (verificaRemiza()) {
					cout << "ESTE O REMIZA! Jucati din nou!" << endl;
					gameOver = true;
					break;
				}
				jucator = schimbaJucator(jucator);

			} while (gameOver != true);
	}
	else {
		do {
			jucator = schimbaJucator(jucator);
			miscareAI(jucator);
			afisareTabla();
			PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
			if (verificaVictorie(jucator)) {
				if (jucator == 'X')
					nrVictoriAI++;
				else
					nrVictoriJucator_AI++;
				cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
					<< jucator << " A CASTIGAT!!" << endl;
				gameOver = true;
				break;
			}
			else if (verificaRemiza()) {
				cout << "ESTE O REMIZA! Jucati din nou!" << endl;
				gameOver = true;
				break;
			}
			jucator = schimbaJucator(jucator);
			miscareJucator(jucator);
			PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
			if (verificaVictorie(jucator)) {
				if (jucator == 'X')
					nrVictoriAI++;
				else
					nrVictoriJucator_AI++;
				cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
					<< jucator << " A CASTIGAT!!" << endl;
				gameOver = true;
				break;
			}
			else if (verificaRemiza()) {
				cout << "ESTE O REMIZA! Jucati din nou!" << endl;
				gameOver = true;
				break;
			}
		} while (gameOver != true);
	}
	afisareTabla();
}

string tictactoe::Conversie_La_Sir_Pentru_Fisier()
{
	string s = to_string(IDMeci);
	stringstream linie;
	linie << s << ",";
	for (int i = 0; i < nrMaxMiscari; i++)
		linie << buffer[i] << " ";
	string liniePentruFisier = linie.str();
	return liniePentruFisier;
}

void tictactoe::setID(int IDMeci)
{
	this->IDMeci = IDMeci;
}

int tictactoe::getID()
{
	return IDMeci;
}

void tictactoe::Preluare_joc(string istoric_joc)
{
    initializare_tabla();
    int contor_miscare=1;
    for(int contor_istoric=0;contor_istoric<sizeof(istoric_joc);contor_istoric=contor_istoric+2)
    {
        int pozitie=istoric_joc[contor_istoric]-'0';
        pozitie--;
        if(pozitie<0)
            break;
        int row = pozitie / 3;
        int col = pozitie % 3;
        if(contor_miscare%2==0)
            tabla[row][col]='O';
        else tabla[row][col]='X';
        afisareTabla();
        contor_miscare++;
    }
}
