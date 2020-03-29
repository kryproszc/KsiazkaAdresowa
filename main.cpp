#include <iostream>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Adresy {
    string id;
    string imie,nazwisko,nr_tel,email,adres;
};
int  OdczytKsiazki(vector <Adresy> &adresaci) {
    int iloscOsobWplku=0;
    Adresy osoby;
    fstream plik;
    plik.open("osoby.txt",ios::in);
    do {
        getline(plik,osoby.id,'|');
        getline(plik,osoby.imie,'|');
        getline(plik,osoby.nazwisko,'|');
        getline(plik,osoby.nr_tel,'|');
        getline(plik,osoby.email,'|');
        getline(plik,osoby.adres,'|');
        iloscOsobWplku++;
        adresaci.push_back(osoby);
    } while(getline(plik,osoby.id));
    plik.close();
    return iloscOsobWplku-1;
}
int DodajOsoby( vector<Adresy> adresaci,int id) {
    string imie="",nazwisko="",nr_tel="",email="",adres="";
    cout<< "Podaj imie: ";
    cin.sync();
    getline(cin,imie);
    cout<< "Podaj nazwisko: ";
    getline(cin,nazwisko);
    cout<< "Podaj numer telefonu: ";
    getline(cin,nr_tel);
    cout<< "Podaj email: ";
    cin.sync();
    getline(cin,email);
    cout<< "Podaj adres: ";
    cin.sync();
    getline(cin,adres);
    fstream plik;
    plik.open("osoby.txt",ios::out|ios::app);
    if (plik.good() == false) {
        plik.open("osoby.txt",std::ios::out);
    }
    plik<<id<<"|"<<imie<<"|"<<nazwisko<<"|"<<nr_tel<<"|"<<email<<"|"<<adres<<"|"<<endl;
    plik.close();
    cout<< "Poprawnie dodano nowa osoby do ksiazki adresowej.";
}
void zapiszUzytkownikow(vector<Adresy> &adresaci) {
    fstream edycja;
    edycja.open("osoby.txt",ios::out|ios::trunc);
    for(int i=0; i<adresaci.size()-1; i++) {
        edycja<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].nr_tel<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
    }
    edycja.close();
}
void WyswietlWektor(vector<Adresy> &adresaci,int j) {
    cout<<adresaci[j].id<<endl;
    cout<<adresaci[j].imie<<endl;
    cout<< adresaci[j].nazwisko<<endl;
    cout<< adresaci[j].nr_tel<<endl;
    cout<< adresaci[j].email<<endl;
    cout<< adresaci[j].adres<<endl;
    cout<<endl;
}
void WczytajKsiazke( vector<Adresy> &adresaci) {
    int    iloscUzytkownikowWksiazce= adresaci.size()-1;
    for(int j=0; j<iloscUzytkownikowWksiazce; j++) {
        WyswietlWektor(adresaci,j);
    }
}
void WczytajWgNazwiska(vector<Adresy> &adresaci) {
    int   iloscUzytkownikowWksiazce= adresaci.size()-1;
    string nazwisko;
    cout<< "Podaj nazwisko: ";
    cin>>nazwisko;
    int q=0,i=0;
    while(q<iloscUzytkownikowWksiazce) {
        if(adresaci[q].nazwisko==nazwisko) {
            WyswietlWektor(adresaci,q);
            i++;
        }
        q++;
    }
    if(i==0) {
        cout<< "Uzytkownik o nazwisku: "<<nazwisko<< " nie istnieje w ksiazce adresowej."<<endl;
    }
}
void WczytajWgImienia(vector<Adresy> &adresaci) {
    int    iloscUzytkownikowWksiazce= adresaci.size()-1;
    string imie;
    cout<< "Podaj imie: ";
    cin>>imie;
    int q=0;
    int i=0;
    while(q<iloscUzytkownikowWksiazce) {
        if(adresaci[q].imie==imie) {
            WyswietlWektor(adresaci,q);
        }
        q++;
    }
    if(i==0) {
        cout<< "Uzytkownik o imieniu: "<<imie<< " nie istnieje w ksiazce adresowej."<<endl;
    }
}
int wyznaczaIDKolejnegoUzytkownika(vector<Adresy> adresaci) {
    int iloscOsobyWksiazce= adresaci.size()-2;
    int idKolejnegoUzytkownika;
    string IdOstatniegoUzytkownika;
    IdOstatniegoUzytkownika=adresaci[iloscOsobyWksiazce].id;
    int IdOstatniegoUzytkownika_int;
    IdOstatniegoUzytkownika_int=atoi(IdOstatniegoUzytkownika.c_str());
    return idKolejnegoUzytkownika=IdOstatniegoUzytkownika_int+1;
}
vector<Adresy> zmieniaImie(vector<Adresy> adresaci,string idUzytkownika) {
    string noweImie;
    for(int i=0; i<adresaci.size()-1; i++) {
        if(adresaci[i].id==idUzytkownika) {
            cout<< " Podaj nowe imie: ";
            cin>>noweImie;
            adresaci[i].imie=noweImie;
            zapiszUzytkownikow(adresaci);
        }
    }
    cout<< "Dane zostaly edytowane poprawnie";
    return adresaci;
}
vector<Adresy> zmieniaNazwisko(vector<Adresy> adresaci,string idUzytkownika) {
    string noweNazwisko;
    for(int i=0; i<adresaci.size()-1; i++) {
        if(adresaci[i].id==idUzytkownika) {
            cout<< " Podaj nowe nazwisko: ";
            cin>>noweNazwisko;
            adresaci[i].nazwisko=noweNazwisko;
            zapiszUzytkownikow(adresaci);
        }
    }
    cout<< "Dane zostaly edytowane poprawnie";
    return adresaci;
}
vector<Adresy> zmieniaNumerTel(vector<Adresy> adresaci,string idUzytkownika) {
    string noweNr_tel;
    for(int i=0; i<adresaci.size()-1; i++) {
        if(adresaci[i].id==idUzytkownika) {
            cout<< " Podaj nowe numer telefonu: ";
            cin>>noweNr_tel;
            adresaci[i].nr_tel=noweNr_tel;
            zapiszUzytkownikow(adresaci);
        }
    }
    cout<< "Dane zostaly edytowane poprawnie";
    return adresaci;
}
vector<Adresy> zmieniaemail(vector<Adresy> adresaci,string idUzytkownika) {
    string noweemail;
    for(int i=0; i<adresaci.size()-1; i++) {
        if(adresaci[i].id==idUzytkownika) {
            cout<< " Podaj nowe email: ";
            cin>>noweemail;
            adresaci[i].email=noweemail;
            zapiszUzytkownikow(adresaci);
        }
    }
    cout<< "Dane zostaly edytowane poprawnie";
    return adresaci;
}
vector<Adresy> zmieniaAdres(vector<Adresy> adresaci,string idUzytkownika) {
    string noweAdres;
    for(int i=0; i<adresaci.size()-1; i++) {
        if(adresaci[i].id==idUzytkownika) {
            cout<< " Podaj nowe adres: ";
            cin>>noweAdres;
            adresaci[i].adres=noweAdres;
            zapiszUzytkownikow(adresaci);
        }
    }
    cout<< "Dane zostaly edytowane poprawnie";
    return adresaci;
}
void usuwaUzytkownika(vector<Adresy> adresaci,string idUsuwanegoUzytkownika) {
    int u=0;
    for( vector<Adresy>::iterator i = adresaci.begin(); i < adresaci.end(); i++) {
        u++;
        if(i->id == idUsuwanegoUzytkownika) {
            break;
        }
    }
    adresaci.erase(adresaci.begin()+u);
    zapiszUzytkownikow(adresaci);
}
int main() {
    char wybor;
    while(true) {
        vector<Adresy> adresaci;
        OdczytKsiazki(adresaci);
        Sleep(3000);
        system("cls");
        cout<< "KSIAZKA ADRESOWA"<<endl;
        cout<< "1.Dodaj adresata "<<endl;
        cout<< "2.Wyswietl wszystkich adresatow"<<endl;
        cout<< "3.Wyszukaj po nazwisku "<<endl;
        cout<< "4.Wyszukaj po imieniu "<<endl;
        cout<< "5.Edytuj adresata "<<endl;
        cout<< "6.Usun adresata"<<endl;
        cout<< "9.Zakoncz program."<<endl;
        cin>>wybor;
        if(wybor=='1') {
            system("cls");
            int id=wyznaczaIDKolejnegoUzytkownika(adresaci);
            DodajOsoby(adresaci,id);
        } else if(wybor=='2')  {
            system("cls");
            WczytajKsiazke(adresaci);
            cout<< "Aby przejsc do Menu glownego nacisnij ENTER.";
            getchar();
            getchar();
        } else if(wybor=='3') {
            system("cls");
            WczytajWgNazwiska(adresaci);
            cout<< "Aby przejsc do Menu glownego nacisnij ENTER.";
            getchar();
            getchar();
        } else if(wybor=='4') {
            system("cls");
            WczytajWgImienia(adresaci);
            cout<< "Aby przejsc do Menu glownego nacisnij ENTER.";
            getchar();
            getchar();
        } else if(wybor=='5') {
            system("cls");
            string idUzytkownika;
            char danaDoZmiany;
            cout<< "Podaj id  uzytkownika ktorego chcesz edytowac: ";
            cin>>idUzytkownika;
            system("cls");
            cout<< "Chce zmienic: "<<endl;
            cout<< "1-Imie "<<endl;
            cout<< "2-Nazwisko "<<endl;
            cout<< "3-Numer telefony "<<endl;
            cout<< "4-Adres email"<<endl;
            cout<< "5-Adres"<<endl;
            cin>>danaDoZmiany;
            if(danaDoZmiany=='1') {
                zmieniaImie(adresaci,idUzytkownika);
            } else if(danaDoZmiany=='2') {
                zmieniaNazwisko(adresaci,idUzytkownika);
            } else if(danaDoZmiany=='3') {
                zmieniaNumerTel(adresaci,idUzytkownika);
            } else if(danaDoZmiany=='4') {
                zmieniaemail(adresaci,idUzytkownika);
            } else if(danaDoZmiany=='5') {
                zmieniaAdres(adresaci,idUzytkownika);
            }
        } else if(wybor=='6') {
            system("cls");
            cout<< "Id uzytkownika ktorego chcesz usunac: ";
            string id_usun;
            cin>>id_usun;
            cout<< "Czy napewno chcesz usunac uzutkownika o id: "<<id_usun<< " ?(t/n)";
            char decyzjaCzyusunacUzytkownika;
            cin>>decyzjaCzyusunacUzytkownika;
            if(decyzjaCzyusunacUzytkownika=='t') {
                usuwaUzytkownika(adresaci,id_usun);
            }
        } else if(wybor=='9') {
            exit(0);
        }
    }
    return 0;
}


