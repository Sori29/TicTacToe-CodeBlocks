#include "AdministrareJocuri.h"
ofstream g;
AdministrareJocuri::AdministrareJocuri()
{
	numeFisier = { 0 };
}
AdministrareJocuri::AdministrareJocuri(string numeFisier)
{
	this->numeFisier = numeFisier;
}
void AdministrareJocuri::AdaugareJoc(string numeFisier, string linie, int ID)
{
	g.open(numeFisier,ofstream::app);
	if (g.is_open())
	{
        if(ID==1)
            g << linie;
        else
            g << "\n" <<linie;
		g.close();
	}
	else
	{
		cout << "Fisierul nu a putut fi deschis";
	}

}
int AdministrareJocuri::GetJocuri(string numeFisier)
{
    int nr_linii=0;
    string linie;
    ifstream fisier(numeFisier);
    while(std::getline(fisier,linie))
        ++nr_linii;
    return nr_linii;
}

string AdministrareJocuri::PreluareJoc(string numeFisier,int index)
{
    int nr_linii=0;
    string linie;
    ifstream fisier(numeFisier);
    while(std::getline(fisier,linie,','))
    {
        ++nr_linii;
        if(index+1==nr_linii){
            int lungime=sizeof(linie);
            for(int contor=0;contor<lungime;contor++)
            {
                if(linie[contor]=='\n'){
                    for(int j=contor;j<lungime;j++)
                        linie[j]='\0';
                    break;}
            }
            return linie;
        }
    }
    return "Jocul nu a fost gasit";
}
