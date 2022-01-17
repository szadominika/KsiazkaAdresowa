#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Przyjaciel {
    int id;
    string Imie;
    string Nazwisko;
    string NrTelefonu;
    string Email;
    string Adres;
};

vector <Przyjaciel> adresaci;

void DodajAdresataDoWektora (const int id, const string& Imie, const string& Nazwisko,
                   const string& NrTelefonu, const string& Email, const string& Adres)
{
    adresaci.push_back({id, Imie, Nazwisko, NrTelefonu, Email, Adres});
}

Przyjaciel WczytajZKsiazkiAdresowejWpis(string DaneAdresata) {
    Przyjaciel pobrane;
    string ZnakPodzialu = "|";
    string Linia;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()==false) {
        cout<<"Nie mozna otworzyc pliku!";
    }

    while (getline(plik, DaneAdresata)) {
        Linia = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        pobrane.id = atoi(Linia.c_str());
        DaneAdresata.erase(0, DaneAdresata.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.Imie = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        DaneAdresata.erase(0, DaneAdresata.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.Nazwisko = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        DaneAdresata.erase(0, DaneAdresata.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.NrTelefonu = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        DaneAdresata.erase(0, DaneAdresata.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.Adres = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        DaneAdresata.erase(0, DaneAdresata.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.Email = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        DaneAdresata.erase(0, DaneAdresata.find(ZnakPodzialu) + ZnakPodzialu.length());

        adresaci.push_back(pobrane);
    }
    plik.close();
    return   pobrane;
}

int DodajAdresata (int IloscPrzyjaciol) {
    string Imie, Nazwisko, NrTelefonu, Email, Adres, DaneAdresata;
    int id;
    int idPrzyjaciela;
    fstream plik;

    vector<Przyjaciel>::iterator it;
    it = adresaci.begin();

    if ( adresaci.size() != 0) {
        idPrzyjaciela = adresaci[IloscPrzyjaciol - 1].id + 1;
    } else {
        idPrzyjaciela = IloscPrzyjaciol+1;
    }
    id = idPrzyjaciela;
    cout << "Podaj imie przyjaciela:";
    cin >> Imie;
    cout << "Podaj nazwisko przyjaciela:";
    cin >> Nazwisko;
    cout << "Podaj nr telefonu przyjaciela:";
    cin.sync();
    getline(cin, NrTelefonu);
    cout << "Podaj e-mail przyjaciela:";
    cin >> Email;
    cout << "Podaj adres przyjaciela:";
    cin.sync();
    getline(cin, Adres);

    DodajAdresataDoWektora(id, Imie, Nazwisko, NrTelefonu, Email, Adres);

    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if (plik.good() == true) {
        plik << idPrzyjaciela << "|" << Imie << "|" << Nazwisko << "|" << NrTelefonu << "|" << Email << "|" << Adres << "|";
        plik  << endl;
        it++;
        plik.close();
        cout << "Dane przyjaciela zostaly dodane do ksiazki adresowej";
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    return IloscPrzyjaciol + 1;
}

void WypiszDanePrzyjaciela(vector < Przyjaciel > &adresaci, int indeks) {
    cout << adresaci[indeks].id << " | " << adresaci[indeks].Imie << " | "
         << adresaci[indeks].Nazwisko << " | " << adresaci[indeks].NrTelefonu << " | "
         << adresaci[indeks].Email << " | " << adresaci[indeks].Adres << endl;
    cout << endl;
}

void WyswietlKsiazkeAdresowa ( vector < Przyjaciel > &adresaci) {
    for (int liczba = 0; liczba < adresaci.size(); liczba++) {
        WypiszDanePrzyjaciela(adresaci, liczba);
        system("pause");
    }
}

void WyszukajNazwisko(vector < Przyjaciel > &adresaci) {
    string Nazwisko;
    cout << "Podaj nazwisko przyjaciela:";
    cin >> Nazwisko;

    int indeks = 0;
    while (indeks < adresaci.size()) {
        if (adresaci[indeks].Nazwisko == Nazwisko) {
            WypiszDanePrzyjaciela(adresaci, indeks);
        }
        indeks++;
    }
    system("pause");
}

void WyszukajImie(vector < Przyjaciel > &adresaci) {
    string Imie;
    cout << "Podaj imie przyjaciela:";
    cin >> Imie;

    int indeks = 0;
    while (indeks < adresaci.size()) {
        if (adresaci[indeks].Imie == Imie) {
            WypiszDanePrzyjaciela(adresaci, indeks);
        }
        indeks++;
    }
    system("pause");
}

void NadpiszPlik (vector < Przyjaciel > &adresaci) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::trunc | ios::out);

    if (plik.good() == true) {
        for (int i = 0; i < adresaci.size(); i++) {
            plik << adresaci[i].id << "|" << adresaci[i].Imie << "|" << adresaci[i].Nazwisko << "|"
                 << adresaci[i].NrTelefonu << "|" << adresaci[i].Email << "|" << adresaci[i].Adres << "|" << endl;
        }
        plik.close();
    }
}

void UsunAdresata (vector < Przyjaciel > &adresaci) {
    int id = 0;

    vector<Przyjaciel>::iterator it;
    it = adresaci.begin();

    cout << " Podaj ID przyjaciela: ";
    cin >> id;
    for ( int i = 0; i < adresaci.size(); i++) {
        if (id == adresaci[i].id) {
            char potwierdzenie;
            cout << "Czy jestes pewny, ze chcesz usunac wpis? Jesli tak nacisnij t na klawiaturze.";
            cin >> potwierdzenie;
            if (potwierdzenie == 't') {
                adresaci.erase(it+i);
            }
        }
    }
    NadpiszPlik(adresaci);
}

void ZmienImie (vector < Przyjaciel > &adresaci, int IdPrzyjaciela) {
    string Zmiana;

    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id ==  IdPrzyjaciela) {
            cout << "Wpisz nowe imie: ";
            cin >> Zmiana;
            adresaci[i].Imie = Zmiana;
            cout << "Nastapila zmiana.";
        }
    }
    NadpiszPlik(adresaci);
}

void ZmienNazwisko (vector < Przyjaciel > &adresaci, int IdPrzyjaciela) {
    string Zmiana;

    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id ==  IdPrzyjaciela) {
            cout << "Wpisz nowe nazwisko: ";
            cin >> Zmiana;
            adresaci[i].Nazwisko = Zmiana;
            cout << "Nastapila zmiana.";
        }
    }
    NadpiszPlik(adresaci);
}

void ZmienNrTelefonu (vector < Przyjaciel > &adresaci, int IdPrzyjaciela) {
    string Zmiana;

    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id ==  IdPrzyjaciela) {
            cout << "Wpisz nowy nr telefonu: ";
            cin.sync();
            getline(cin, Zmiana);
            adresaci[i].NrTelefonu = Zmiana;
            cout << "Nastapila zmiana.";
        }
    }
    NadpiszPlik(adresaci);
}

void ZmienEmail (vector < Przyjaciel > &adresaci, int IdPrzyjaciela) {
    string Zmiana;

    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id ==  IdPrzyjaciela) {
            cout << "Wpisz nowy adres e-mail: ";
            cin >> Zmiana;
            adresaci[i].Email = Zmiana;
            cout << "Nastapila zmiana.";
        }
    }
    NadpiszPlik(adresaci);
}

void ZmienAdres (vector < Przyjaciel > &adresaci, int IdPrzyjaciela) {
    string Zmiana;

    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id ==  IdPrzyjaciela) {
            cout << "Wpisz nowy adres: ";
            cin.sync();
            getline(cin, Zmiana);
            adresaci[i].Adres = Zmiana;
            cout << "Nastapila zmiana.";
        }
    }
    NadpiszPlik(adresaci);
}

int main() {
    setlocale(LC_ALL, "Polish");

    int IloscPrzyjaciol = 0;
    int IdPrzyjaciela = 0;
    char wybor;
    string DaneAdresata;

    WczytajZKsiazkiAdresowejWpis(DaneAdresata);
    IloscPrzyjaciol = adresaci.size();

    while(1) {
        if (IdPrzyjaciela == 0) {
            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatów" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor:";

            cin >> wybor;
            if (wybor == '1') {
                IloscPrzyjaciol = DodajAdresata (IloscPrzyjaciol);
            } else if (wybor == '2') {
                WyszukajImie(adresaci);
            } else if (wybor == '3') {
                WyszukajNazwisko(adresaci);
            } else if (wybor == '4') {
                WyswietlKsiazkeAdresowa(adresaci);
            } else if (wybor == '5') {
                UsunAdresata(adresaci);
            } else if (wybor == '6') {
                cout << "Wpisz ID przyjaciela, ktorego dane chcesz zmienic: ";
                cin >> IdPrzyjaciela;

            } else if (wybor == '9') {
                exit(0);
            }
        } else {
            system("cls");
            cout << "1. Zmien imie " << endl;
            cout << "2. Zmien nazwisko " << endl;
            cout << "3. Zmien nr telefonu " << endl;
            cout << "4. Zmien e-mail " << endl;
            cout << "5. Zmien adres " << endl;
            cout << "6. Wroc do menu glownego." << endl;

            cin >> wybor;
            if (wybor == '1') {
                ZmienImie(adresaci, IdPrzyjaciela);
            } if (wybor == '2') {
                ZmienNazwisko(adresaci, IdPrzyjaciela);
            } if (wybor == '3') {
                ZmienNrTelefonu(adresaci, IdPrzyjaciela);
            } if (wybor == '4') {
                ZmienEmail(adresaci, IdPrzyjaciela);
            } if (wybor == '5') {
                ZmienAdres(adresaci, IdPrzyjaciela);
            } else if (wybor == '6') {
                IdPrzyjaciela = 0;
            }
        }
    }
    return 0;
}
