#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Przyjaciel {
    int id;
    int idUzytkownika;
    string Imie;
    string Nazwisko;
    string NrTelefonu;
    string Email;
    string Adres;
};

struct Uzytkownik {
    int idUzytkownika;
    string nazwa, haslo;
};

vector <Przyjaciel> adresaci;
vector <Uzytkownik> zarejestrowani;

void DodajAdresataDoWektora (const int id, const int idUzytkownika, const string& Imie, const string& Nazwisko,
                             const string& NrTelefonu, const string& Email, const string& Adres) {
    adresaci.push_back({id, idUzytkownika, Imie, Nazwisko, NrTelefonu, Email, Adres});
}
void DodajZarejestrowanegoDoWektora (const int idUzytkownika, const string& nazwa, const string& haslo) {
    zarejestrowani.push_back({idUzytkownika, nazwa, haslo});
}

Uzytkownik WczytajDaneDoLogowania(string DaneUzytkownika) {
    Uzytkownik pobrane;
    string ZnakPodzialu = "|";
    string Linia;

    fstream plik;
    plik.open("DaneUzytkownikow.txt", ios::in);

    if (plik.good()==false) {
        cout<<"Nie mozna otworzyc pliku!";
    }

    while (getline(plik, DaneUzytkownika)) {
        Linia = DaneUzytkownika.substr(0, DaneUzytkownika.find(ZnakPodzialu));
        pobrane.idUzytkownika = atoi(Linia.c_str());
        DaneUzytkownika.erase(0, DaneUzytkownika.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.nazwa = DaneUzytkownika.substr(0, DaneUzytkownika.find(ZnakPodzialu));
        DaneUzytkownika.erase(0, DaneUzytkownika.find(ZnakPodzialu) + ZnakPodzialu.length());

        pobrane.haslo = DaneUzytkownika.substr(0, DaneUzytkownika.find(ZnakPodzialu));
        DaneUzytkownika.erase(0, DaneUzytkownika.find(ZnakPodzialu) + ZnakPodzialu.length());

        zarejestrowani.push_back(pobrane);
    }
    plik.close();
    return   pobrane;
}

int Rejestracja (int IloscUzytkownikow) {
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika:";
    cin >> nazwa;
    int i = 0;

    while (i < IloscUzytkownikow) {
        if (zarejestrowani[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje, wpisz inna nazwe: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }

    cout << "Podaj haslo:";
    cin >> haslo;
    int idUzytkownika = IloscUzytkownikow + 1;
    DodajZarejestrowanegoDoWektora(idUzytkownika, nazwa, haslo);
    cout << "Konto zostalo poprawnie zalozone.";
    Sleep(1000);

    vector<Przyjaciel>::iterator it;
    it = adresaci.begin();
    fstream plik;
    plik.open("DaneUzytkownikow.txt",ios::out | ios::app);

    if (plik.good() == true) {
        plik << idUzytkownika << "|" << nazwa << "|" << haslo;
        plik  << endl;
        it++;
        plik.close();
        cout << "Dane przyjaciela zostaly dodane do ksiazki adresowej";
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }

    return IloscUzytkownikow + 1;
}

int Logowanie(vector <Uzytkownik>& zarejestrowani, int IloscUzytkownikow) {
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika:";
    cin >> nazwa;

    int i = 0;
    while (i < IloscUzytkownikow) {
        if (zarejestrowani[i].nazwa == nazwa) {
            for (int k = 0; k < 3; k++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - k << ":";
                cin >> haslo;

                if (zarejestrowani[i].haslo == haslo) {
                    cout << "Jestes poprawnie zalogowany.";
                    Sleep(1000);
                    return zarejestrowani[i].idUzytkownika;
                }
            }
            cout << "Podale 3 razy bledne haslo. Poczekaj 5 sekund przed klejna proba." << endl;
            Sleep(5000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika o takiej nazwie." << endl;
    Sleep(3000);
    return 0;
}

void ZmianaHasla(vector <Uzytkownik>& zarejestrowani, int IloscUzytkownikow, int IdZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for ( int i=0; i < IloscUzytkownikow; i++) {
        if ( zarejestrowani[i].idUzytkownika == IdZalogowanegoUzytkownika) {
            zarejestrowani[i].haslo = haslo;
            cout << "Haslo zostalo zmienione." <<  endl;
            Sleep(1000);
        }
    }
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

        Linia = DaneAdresata.substr(0, DaneAdresata.find(ZnakPodzialu));
        pobrane.idUzytkownika = atoi(Linia.c_str());
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

int DodajAdresata (int IloscPrzyjaciol, int IdZalogowanegoUzytkownika) {
    string Imie, Nazwisko, NrTelefonu, Email, Adres, DaneAdresata;
    int id, idUzytkownika;
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
    idUzytkownika = IdZalogowanegoUzytkownika;

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

    DodajAdresataDoWektora(id, idUzytkownika, Imie, Nazwisko, NrTelefonu, Email, Adres);

    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if (plik.good() == true) {
        plik << idPrzyjaciela << "|" << idUzytkownika << "|" << Imie << "|" << Nazwisko << "|" << NrTelefonu << "|" << Email << "|" << Adres << "|";
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
    cout << adresaci[indeks].id << " | " << adresaci[indeks].idUzytkownika << " | " << adresaci[indeks].Imie << " | "
         << adresaci[indeks].Nazwisko << " | " << adresaci[indeks].NrTelefonu << " | "
         << adresaci[indeks].Email << " | " << adresaci[indeks].Adres << endl;
    cout << endl;
}

int WyswietlKsiazkeAdresowa ( vector < Przyjaciel > &adresaci, int IdZalogowanegoUzytkownika) {
    int i=0;
    while (!adresaci.empty()) {
        if (adresaci[i].idUzytkownika == IdZalogowanegoUzytkownika) {
            WypiszDanePrzyjaciela(adresaci, i);
            i++;
            system("pause");
        } else {
            return 0;
        }
    }
}

int WyszukajNazwisko(vector < Przyjaciel > &adresaci, int IdZalogowanegoUzytkownika) {
    string Nazwisko;
    cout << "Podaj nazwisko przyjaciela:";
    cin >> Nazwisko;

    int i = 0;
    while (!adresaci.empty()) {
        if (adresaci[i].idUzytkownika == IdZalogowanegoUzytkownika && adresaci[i].Nazwisko == Nazwisko) {
            WypiszDanePrzyjaciela(adresaci, i);
            i++;
            system("pause");
        } else if (adresaci[i].idUzytkownika == IdZalogowanegoUzytkownika || adresaci[i].Nazwisko != Nazwisko) {
            i++;
        } else {
            return 0;
        }
    }
}

int WyszukajImie(vector < Przyjaciel > &adresaci, int IdZalogowanegoUzytkownika) {
    string Imie;
    cout << "Podaj imie przyjaciela:";
    cin >> Imie;

    int i = 0;
    while (!adresaci.empty()) {
        if (adresaci[i].idUzytkownika == IdZalogowanegoUzytkownika && adresaci[i].Imie == Imie) {
            WypiszDanePrzyjaciela(adresaci, i);
            i++;
            system("pause");
        } else if (adresaci[i].idUzytkownika == IdZalogowanegoUzytkownika || adresaci[i].Imie != Imie) {
            i++;
        } else {
            return 0;
        }
    }
}

void NadpiszPlik (vector < Przyjaciel > &adresaci) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::trunc | ios::out);

    if (plik.good() == true) {
        for (int i = 0; i < adresaci.size(); i++) {
            plik << adresaci[i].id << "|" << adresaci[i].idUzytkownika << "|" << adresaci[i].Imie << "|" << adresaci[i].Nazwisko << "|"
                 << adresaci[i].NrTelefonu << "|" << adresaci[i].Email << "|" << adresaci[i].Adres << "|" << endl;
        }
        plik.close();
    }
}

void UsunAdresata (vector < Przyjaciel > &adresaci, int IdZalogowanegoUzytkownika) {
    int id = 0;

    vector<Przyjaciel>::iterator it;
    it = adresaci.begin();

    cout << " Podaj ID przyjaciela: ";
    cin >> id;
    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == id && adresaci[i].idUzytkownika == IdZalogowanegoUzytkownika) {
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

void EdytujAdresata (vector < Przyjaciel > &adresaci, int IdZalogowanegoUzytkownika) {
    int idPrzyjaciela = 0;
    char wybor;
    bool czyIstniejeAdresat = false;
    string Zmiana = "";

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> EDYCJA ADRESATA <<<" << endl << endl;
        cout << "Podaj numer ID adresata u ktorego chcesz zmienic dane: ";
        cin >> idPrzyjaciela;

        for (vector<Przyjaciel>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->id == idPrzyjaciela && itr->idUzytkownika == IdZalogowanegoUzytkownika) {
                czyIstniejeAdresat = true;

                cout << endl << "Ktore dane zaktualizowac: " << endl;
                cout << "1 - Imie" << endl;
                cout << "2 - Nazwisko" << endl;
                cout << "3 - Numer telefonu" << endl;
                cout << "4 - Email" << endl;
                cout << "5 - Adres" << endl;
                cout << "6 - Powrot " << endl;
                cout << endl << "Wybierz 1-6: ";
                cin >> wybor;

                switch (wybor) {
                case '1':
                    cout << "Wpisz nowe imie: ";
                    cin >> Zmiana;
                    itr->Imie = Zmiana;
                    cout << "Imie zostalo zmienione.";
                    NadpiszPlik(adresaci);
                    break;
                case '2':
                    cout << "Wpisz nowe nazwisko: ";
                    cin >> Zmiana;
                    itr->Nazwisko = Zmiana;
                    cout << "Nazwisko zostalo zmienione.";
                    NadpiszPlik(adresaci);
                case '3':
                    cout << "Wpisz nowy numer telefonu: ";
                    cin.sync();
                    getline(cin, Zmiana);
                    itr->NrTelefonu = Zmiana;
                    cout << "Numer telefonu zostal zmieniony.";
                    NadpiszPlik(adresaci);
                    break;
                case '4':
                    cout << "Wpisz nowy adres e-mail: ";
                    cin >> Zmiana;
                    itr->Email = Zmiana;
                    cout << "Adres e-mail zostal zmieniony.";
                    NadpiszPlik(adresaci);
                    break;
                case '5':
                    cout << "Wpisz nowy adres zamieszkania: ";
                    cin.sync();
                    getline(cin, Zmiana);
                    itr->Adres = Zmiana;
                    cout << "Adres zamieszkania zostal zmieniony.";
                    NadpiszPlik(adresaci);
                    break;
                case '6':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

int main() {
    setlocale(LC_ALL, "Polish");

    int IloscPrzyjaciol = 0;
    int IdPrzyjaciela = 0;
    int IdZalogowanegoUzytkownika = 0;
    int IloscUzytkownikow = 0;
    char wybor;
    string DaneAdresata = "";
    string DaneUzytkownika = "";

    WczytajZKsiazkiAdresowejWpis(DaneAdresata);
    WczytajDaneDoLogowania(DaneUzytkownika);
    IloscPrzyjaciol = adresaci.size();
    IloscUzytkownikow = zarejestrowani.size();

    while(1) {
        if (IdZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;

            cin >> wybor;

            if (wybor == '1') {
                // cout << IloscUzytkownikow;
                IloscUzytkownikow = Rejestracja (IloscUzytkownikow);
            } else if (wybor == '2') {
                IdZalogowanegoUzytkownika = Logowanie(zarejestrowani, IloscUzytkownikow);
            } else if (wybor == '9') {
                exit(0);
            }
        } else {
            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatów" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor:";

            cin >> wybor;
            if (wybor == '1') {
                IloscPrzyjaciol = DodajAdresata (IloscPrzyjaciol, IdZalogowanegoUzytkownika);
            } else if (wybor == '2') {
                WyszukajImie(adresaci, IdZalogowanegoUzytkownika);
            } else if (wybor == '3') {
                WyszukajNazwisko(adresaci, IdZalogowanegoUzytkownika);
            } else if (wybor == '4') {
                WyswietlKsiazkeAdresowa(adresaci,IdZalogowanegoUzytkownika);
            } else if (wybor == '5') {
                UsunAdresata(adresaci, IdZalogowanegoUzytkownika);
            } else if (wybor == '6') {
                EdytujAdresata (adresaci, IdZalogowanegoUzytkownika);
            } else if (wybor == '7') {
                ZmianaHasla(zarejestrowani, IloscUzytkownikow, IdZalogowanegoUzytkownika);
            } else if (wybor == '8') {
                IdZalogowanegoUzytkownika = 0;
            } else if (wybor == '9') {
                exit(0);
            }
        }
    }
    return 0;
}
