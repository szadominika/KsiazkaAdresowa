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

void DodajZarejestrowanegoDoWektora (const int idUzytkownika, const string& nazwa, const string& haslo) {
    zarejestrowani.push_back({idUzytkownika, nazwa, haslo});
}

void Rejestracja (int IloscUzytkownikow) {
    string nazwa, haslo;
    int idUzytkownika;
    cout << ">>> REJESTRACJA NOWEGO UZYTKOWNIKA <<<" << endl << endl;
    cout << "Podaj nazwe uzytkownika:";
    cin >> nazwa;
    int i = 0;

    while (i < zarejestrowani.size()) {
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
    if (zarejestrowani.empty() == true) {
        idUzytkownika = 1;
    } else {
        idUzytkownika = zarejestrowani.back().idUzytkownika + 1;
    }

    DodajZarejestrowanegoDoWektora(idUzytkownika, nazwa, haslo);
    cout << "Konto zostalo poprawnie zalozone.";
    Sleep(1000);

    fstream plik;
    plik.open("DaneUzytkownikow.txt",ios::out | ios::app);

    if (plik.good() == true) {
        plik << idUzytkownika << "|" << nazwa << "|" << haslo;
        plik << endl;
        plik.close();
        cout << "Dane przyjaciela zostaly dodane do ksiazki adresowej";
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
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

int OkreslOstatniNrIdUzytkownika (string Linia) {
    int IdAdresata = 0;
    string ZnakPodzialu = "|";

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == false) {
        IdAdresata = 0;
    }

    while (getline(plik, Linia)) {
        Linia = Linia.substr(0, Linia.find(ZnakPodzialu));
        IdAdresata = atoi(Linia.c_str());
    }
    plik.close();
    return IdAdresata;
}


int Logowanie(vector <Uzytkownik>& zarejestrowani) {
    string nazwa, haslo;
    cout << ">>> LOGOWANIE <<<" << endl << endl;
    cout << "Podaj nazwe uzytkownika:";
    cin >> nazwa;

    int i = 0;
    while (i < zarejestrowani.size()) {
        if (zarejestrowani[i].nazwa == nazwa) {
            for (int proba = 0; proba < 3; proba++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proba << ":";
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
    cout << ">>> ZMIANA HASLA <<<" << endl << endl;
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

Przyjaciel WczytajZKsiazkiAdresowejWpis(string DaneAdresata, int IdZalogowanegoUzytkownika ) {
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

        if (pobrane.idUzytkownika == IdZalogowanegoUzytkownika ) {
            adresaci.push_back(pobrane);
        }
    }
    plik.close();
    return   pobrane;
}
void DopiszAdresataDoPliku (Przyjaciel przyjaciele) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if (plik.good() == true) {
        plik << przyjaciele.id << "|" << przyjaciele.idUzytkownika << "|" << przyjaciele.Imie << "|"
             << przyjaciele.Nazwisko << "|" << przyjaciele.NrTelefonu << "|" << przyjaciele.Email << "|"
             << przyjaciele.Adres << "|";
        plik << endl;
        plik.close();
        cout << "Dane przyjaciela zostaly dodane do ksiazki adresowej";
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

void DodajAdresata (vector <Przyjaciel>& adresaci, int IdZalogowanegoUzytkownika) {

    string Linia;
    string Imie, Nazwisko, NrTelefonu, Email, Adres, DaneAdresata;
    Przyjaciel przyjaciele;
    przyjaciele.idUzytkownika = IdZalogowanegoUzytkownika;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    przyjaciele.id = OkreslOstatniNrIdUzytkownika(Linia) + 1;
    int id = przyjaciele.id;

    cout << "Podaj imie: ";
    cin >> Imie;
    przyjaciele.Imie = Imie;
    cout << "Podaj nazwisko: ";
    cin >> Nazwisko;
    przyjaciele.Nazwisko  = Nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, NrTelefonu);
    przyjaciele.NrTelefonu = NrTelefonu;
    cout << "Podaj email: ";
    cin >> Email;
    przyjaciele.Email = Email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, Adres);
    przyjaciele.Adres = Adres;

    adresaci.push_back(przyjaciele);
    system("pause");

    DopiszAdresataDoPliku(przyjaciele);
}

void WypiszDanePrzyjaciela(vector < Przyjaciel > &adresaci, int indeks) {
    cout << "Id:               " << adresaci[indeks].id << endl;
    cout << "Imie:             " << adresaci[indeks].Imie << endl;
    cout << "Nazwisko:         " << adresaci[indeks].Nazwisko << endl;
    cout << "Numer telefonu:   " << adresaci[indeks].NrTelefonu << endl;
    cout << "Email:            " << adresaci[indeks].Email << endl;
    cout << "Adres:            " << adresaci[indeks].Adres << endl;
    cout << endl;
}

void wypiszWszystkichAdresatow(vector<Przyjaciel> &adresaci) {
    system("cls");
    cout << ">>> WSZYSCY ADRESACI <<<" << endl << endl;
    if (!adresaci.empty()) {
        for (vector<Przyjaciel>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
                cout << "Id:                 " << itr->id << endl;
                cout << "Imie:               " << itr->Imie << endl;
                cout << "Nazwisko:           " << itr->Nazwisko << endl;
                cout << "Numer telefonu:     " << itr->NrTelefonu << endl;
                cout << "Email:              " << itr->Email << endl;
                cout << "Adres:              " << itr->Adres << endl << endl;
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

int WyszukajNazwisko(vector < Przyjaciel > &adresaci) {
    string Nazwisko = "";
    cout << ">>> WYSZUKAJ: <<<" << endl << endl;
    cout << "Podaj nazwisko przyjaciela:";
    cin >> Nazwisko;

    while (!adresaci.empty()) {
        for (int i=0; i < adresaci.size(); i++) {
            if (adresaci[i].Nazwisko == Nazwisko) {
                WypiszDanePrzyjaciela(adresaci, i);
                system("pause");
            }
        }
        return 0;
    }
}

int WyszukajImie(vector < Przyjaciel > &adresaci) {
    string Imie = "";
    cout << ">>> WYSZUKAJ: <<<" << endl << endl;
    cout << "Podaj imie przyjaciela:";
    cin >> Imie;

    while (!adresaci.empty()) {
        for (int i=0; i < adresaci.size(); i++) {
            if (adresaci[i].Imie == Imie) {
                WypiszDanePrzyjaciela(adresaci, i);
                system("pause");
            }
        }
        return 0;
    }
}



void DodajDoPlikuTymczasowego (vector < Przyjaciel > &adresaci) {
    fstream plik;
    plik.open("KsiazkaAdresowaTymczasowa.txt",ios::out|ios::trunc);

    if (plik.good() == true) {
        for (int i = 0; i < adresaci.size(); i++) {
            plik << adresaci[i].id << "|" << adresaci[i].idUzytkownika << "|" << adresaci[i].Imie << "|" << adresaci[i].Nazwisko << "|"
                 << adresaci[i].NrTelefonu << "|" << adresaci[i].Email << "|" << adresaci[i].Adres << "|" << endl;
        }
        plik.close();
    }
}

void UsunAdresata (vector < Przyjaciel > &adresaci) {
    int id = 0;
    vector<Przyjaciel>::iterator it;
    it = adresaci.begin();
    cout << ">>> USUWANIE ADRESATA <<<" << endl << endl;
    cout << " Podaj ID przyjaciela: ";
    cin >> id;
    for ( int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == id) {
            char potwierdzenie;
            cout << "Czy jestes pewny, ze chcesz usunac wpis? Jesli tak nacisnij t na klawiaturze.";
            cin >> potwierdzenie;
            if (potwierdzenie == 't') {
                adresaci.erase(it+i);
            }
        }
    }
    DodajDoPlikuTymczasowego(adresaci);
}

void EdytujAdresata (vector < Przyjaciel > &adresaci) {
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
            if (itr->id == idPrzyjaciela) {
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
                    break;
                case '2':
                    cout << "Wpisz nowe nazwisko: ";
                    cin >> Zmiana;
                    itr->Nazwisko = Zmiana;
                    cout << "Nazwisko zostalo zmienione.";
                    break;
                case '3':
                    cout << "Wpisz nowy numer telefonu: ";
                    cin.sync();
                    getline(cin, Zmiana);
                    itr->NrTelefonu = Zmiana;
                    cout << "Numer telefonu zostal zmieniony.";
                    break;
                case '4':
                    cout << "Wpisz nowy adres e-mail: ";
                    cin >> Zmiana;
                    itr->Email = Zmiana;
                    cout << "Adres e-mail zostal zmieniony.";
                    break;
                case '5':
                    cout << "Wpisz nowy adres zamieszkania: ";
                    cin.sync();
                    getline(cin, Zmiana);
                    itr->Adres = Zmiana;
                    cout << "Adres zamieszkania zostal zmieniony.";
                    break;
                case '6':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
                DodajDoPlikuTymczasowego(adresaci);
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

    int IdZalogowanegoUzytkownika = 0;
    int IloscUzytkownikow = 0;
    char wybor;
    string DaneAdresata = "";
    string DaneUzytkownika = "";

    WczytajDaneDoLogowania(DaneUzytkownika);

    while(1) {
        if (IdZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;

            cin >> wybor;

            if (wybor == '1') {
                Rejestracja (IloscUzytkownikow);
            } else if (wybor == '2') {
                IdZalogowanegoUzytkownika = Logowanie(zarejestrowani);
                WczytajZKsiazkiAdresowejWpis(DaneAdresata, IdZalogowanegoUzytkownika);
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
                DodajAdresata (adresaci, IdZalogowanegoUzytkownika);
            } else if (wybor == '2') {
                WyszukajImie(adresaci);
            } else if (wybor == '3') {
                WyszukajNazwisko(adresaci);
            } else if (wybor == '4') {
                wypiszWszystkichAdresatow(adresaci);
            } else if (wybor == '5') {
                UsunAdresata(adresaci);
            } else if (wybor == '6') {
                EdytujAdresata (adresaci);
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
