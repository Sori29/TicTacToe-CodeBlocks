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
	printf("\t\t\t %c | %c | %c \n", tabla[0][0], tabla[0][1], tabla[0][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n", tabla[1][0], tabla[1][1], tabla[1][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n\n", tabla[2][0], tabla[2][1], tabla[2][2]);
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
		cout << "Player " << rand_jucator << " Unde vrei sa joci? Alege un numar intre 1-9: ";
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
				else{
					cout << "Miscare gresita. Pozitia este deja ocupata. Incercati din nou" << endl;
					PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
				}
			}
			else{
				cout << "Trebuie sa introduceti un numar intre 1-9. Incercati din nou. \n";
				PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
                }
		}
		else{
			cout << "Trebuie sa introduceti ceva!" << endl;
			PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
            }
	}
	cout << "Numar total miscari: " << nrMiscari << endl;
}

char tictactoe::schimbaJucator(char jucator) {

	jucator = jucator == 'X' ? 'O' : 'X';
	return (jucator);
}
char tictactoe::get_oponent(char jucator)
{
    if(jucator=='X')
        return 'O';
    else return 'X';
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
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"ID-ul meciului este: ";
    SetConsoleTextAttribute(h,9);
    cout<<IDMeci+1<<endl;
    SetConsoleTextAttribute(h,15);
	cout << "SCORUL (PLAYER 1 VS PLAYER 2): ";
	SetConsoleTextAttribute(h,2);
	cout <<nrVictoriJucator1;
	SetConsoleTextAttribute(h,15);
	cout << "-";
	SetConsoleTextAttribute(h,3);
	cout << nrVictoriJucator2 << endl;
	SetConsoleTextAttribute(h,15);
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
            SetConsoleTextAttribute(h,2);
            PlaySound(TEXT("sunet_victorie.wav"),NULL,SND_ASYNC);
			cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
				<< jucator << " A CASTIGAT!!" << endl;
            SetConsoleTextAttribute(h,15);
			gameOver = true;
		}
		else if (verificaRemiza()) {
            SetConsoleTextAttribute(h,14);
			cout << "ESTE O REMIZA! Jucati din nou!" << endl;
            SetConsoleTextAttribute(h,15);
			gameOver = true;
		}
		jucator = schimbaJucator(jucator);
	} while (gameOver != true);

	afisareTabla();
}
void tictactoe::miscareAI(char jucator,int dificultate) {
    if(dificultate==0)
    {
        size_t min,max;
        mt19937 rng;
        rng.seed(random_device()());
        uniform_int_distribution<mt19937::result_type>dist(min,max);
        while (true) {
            int numar_rand = (dist(rng)%9)+1;
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
    else if(dificultate==1){
        int numar_rand=GasireMiscareOptima(nrMiscari,jucator);
        cout<<"Calculatorul a ales pozitia: "<<numar_rand+1<<endl;
        tabla[numar_rand/3][numar_rand%3]=jucator;
        buffer[nrMiscari]=numar_rand;
        nrMiscari++;
        cout << "Numar total de miscari: " << nrMiscari << endl;
    }
}

void tictactoe::jocVsAI(int dificultate) {
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"ID-ul meciului este: ";
    SetConsoleTextAttribute(h,9);
    cout<<IDMeci+1<<endl;
    SetConsoleTextAttribute(h,15);
	cout << "SCORUL (PLAYER VS AI) ";
	SetConsoleTextAttribute(h,2);
	cout<< nrVictoriJucator_AI;
	SetConsoleTextAttribute(h,15);
	cout << "-";
	SetConsoleTextAttribute(h,3);
	cout<< nrVictoriAI<<endl;
	SetConsoleTextAttribute(h,15);
	string input;
	char jucator=0;
	do {
        cin.ignore();
		cout << "Introduceti cu ce doriti sa jucati (X/O):";
			getline(cin, input);
			if (toupper(input[0]) == 'X' or toupper(input[0]) == 'O') {
                PlaySound(TEXT("sunet_optiune.wav"),NULL,SND_ASYNC);
				jucator = toupper(input[0]);
				break;
			}
			if (toupper(input[0]) != 'X' or toupper(input[0]) != 'O'){
				cout << "Introduceti o valoare valida\n";
                PlaySound(TEXT("sunet_eroare.wav"),NULL,SND_ASYNC);
			}
	} while (jucator != 'X' or jucator != 'O');
	bool gameOver = false;
	if (jucator == 'X')
	{
		do {
				afisareTabla();
				miscareJucator(jucator);
				PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
				if (verificaVictorie(jucator)) {
					if (jucator == 'X'){
						nrVictoriJucator_AI++;
                        PlaySound(TEXT("sunet_victorie.wav"),NULL,SND_ASYNC);
					}
					else{
						nrVictoriAI++;
                        PlaySound(TEXT("sunet_infrangere.wav"),NULL,SND_ASYNC);
					}
                    SetConsoleTextAttribute(h,2);
					cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
						<< jucator << " A CASTIGAT!!" << endl;
                    SetConsoleTextAttribute(h,15);
					gameOver = true;
					break;
				}
				else if (verificaRemiza()) {
                    SetConsoleTextAttribute(h,14);
					cout << "ESTE O REMIZA! Jucati din nou!" << endl;
                    SetConsoleTextAttribute(h,15);
					gameOver = true;
					break;
				}
				jucator = schimbaJucator(jucator);
				miscareAI(jucator,dificultate); //comp jucator
				PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
				if (verificaVictorie(jucator)) {
                    SetConsoleTextAttribute(h,2);
					cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
						<< jucator << " A CASTIGAT!!" << endl;
                    SetConsoleTextAttribute(h,15);
					gameOver = true;
					break;
				}
				else if (verificaRemiza()) {
                    SetConsoleTextAttribute(h,14);
					cout << "ESTE O REMIZA! Jucati din nou!" << endl;
                    SetConsoleTextAttribute(h,15);
					gameOver = true;
					break;
				}
				jucator = schimbaJucator(jucator);

			} while (gameOver != true);
	}
	else {
		do {
			jucator = schimbaJucator(jucator);
			miscareAI(jucator,dificultate);
			afisareTabla();
			PlaySound(TEXT("sound1.wav"),NULL,SND_ALIAS);
			if (verificaVictorie(jucator)) {
				if (jucator == 'X'){
					nrVictoriAI++;
					PlaySound(TEXT("sunet_infrangere.wav"),NULL,SND_ASYNC);
				}
				else{
					nrVictoriJucator_AI++;
					PlaySound(TEXT("sunet_victorie.wav"),NULL,SND_ASYNC);
				}
                SetConsoleTextAttribute(h,2);
				cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
					<< jucator << " A CASTIGAT!!" << endl;
                SetConsoleTextAttribute(h,15);
				gameOver = true;
				break;
			}
			else if (verificaRemiza()) {
                SetConsoleTextAttribute(h,14);
				cout << "ESTE O REMIZA! Jucati din nou!" << endl;
                SetConsoleTextAttribute(h,15);
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
                SetConsoleTextAttribute(h,2);
				cout << "\n *********** AVEM UN CASTIGATOR!! ***********" << endl
					<< jucator << " A CASTIGAT!!" << endl;
                SetConsoleTextAttribute(h,15);
				gameOver = true;
				break;
			}
			else if (verificaRemiza()) {
                SetConsoleTextAttribute(h,14);
				cout << "ESTE O REMIZA! Jucati din nou!" << endl;
                SetConsoleTextAttribute(h,15);
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

int tictactoe::MiniMax(int depth,bool isAI,char jucator)
{
    int score=0;
    int bestScore=0;
    if(verificaVictorie(jucator))
    {
        if(isAI==true)
            return +1;
        else
            return -1;
    }
    else
    {
        if(depth<9)
        {
            if(isAI==true)
            {
                bestScore=-999;
                for(int row=0;row<BSIZE;row++)
                {
                    for(int col=0;col<BSIZE;col++)
                    {
                        if (tabla[row][col] == ' ')
						{
							tabla[row][col] = jucator;
							score = MiniMax(depth + 1, false,jucator);
							tabla[row][col] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
				for (int row = 0; row < BSIZE; row++)
				{
					for (int col = 0; col < BSIZE; col++)
					{
						if (tabla[row][col] == ' ')
						{
							tabla[row][col] = get_oponent(jucator);
							score = MiniMax(depth + 1, true,jucator);
							tabla[row][col] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
            }
        }
        else
            return 0;
    }
}
int tictactoe::GasireMiscareOptima(int movIndex,char jucator)
{
    int x=-1,y=-1;
    int score=0,bestScore=-999;
    for (int row = 0; row < BSIZE; row++)
	{
		for (int col = 0; col < BSIZE; col++)
		{
			if (tabla[row][col] == ' ')
			{
				tabla[row][col] = jucator;
				score = MiniMax(movIndex+1, true,jucator);
				tabla[row][col] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x=row;
					y=col;
				}
			}
		}
	}
	return x*3+y;
}
