#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct list{
    string vardas;
    string pavarde;
    int paz;
    list *next;
};

class pazymiuSarasas{
private:
    list *P;

public:
    pazymiuSarasas(){
        P = nullptr;
    }

    ~pazymiuSarasas(){
        list *temp;
        while (P != nullptr) {
            temp = P;
            P = P->next;
            delete temp;
        }
    }

    void iterpti(string vardas, string pavarde, int paz){
        list *naujas = new list;
        naujas->vardas = vardas;
        naujas->pavarde = pavarde;
        naujas->paz = paz;
        naujas->next = nullptr;

        if (P == nullptr) {
            P = naujas;
        } else {
            list *temp = P;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = naujas;
        }
    }

    void rikiuoti(int pasirinkimas){
        if (P == nullptr || P->next == nullptr) {
            return;
        }

        bool pakeista;
        do {
            pakeista = false;
            list *temp = P;
            list *tempp = nullptr;

            while (temp->next != nullptr) {

                bool reikiaSukeisti = false;

                if (pasirinkimas == 1 && temp->paz > temp->next->paz){
                    reikiaSukeisti = true;
                }
                else if(pasirinkimas == 2 && temp->paz < temp->next->paz) {
                    reikiaSukeisti = true;
                }

                if(reikiaSukeisti){
                    swap(temp->vardas, temp->next->vardas);
                    swap(temp->pavarde, temp->next->pavarde);
                    swap(temp->paz, temp->next->paz);
                    pakeista = true;
                }
                    temp = temp->next;
            }
        } while (pakeista);
        
    }

    void pasalinti(string pavarde){

        if(P == nullptr) {
            return;
        }

    if(P->pavarde == pavarde){
        list *temp = P;
        P = P->next;
        delete temp;
        cout << "Studentas pasalintas" << endl;
        return;
    }

    list *temp = P;

    while(temp->next != nullptr){
        if(temp->next->pavarde == pavarde){
            list *temp2 = temp->next;
            temp->next = temp2->next;
            delete temp2;
            cout << "Studentas pasalintas" << endl;
            return;
        }
        temp = temp->next;
    }
        cout << "Studentas nerastas" << endl;

    }

    void spausdinti() {
        list *temp = P;
        while (temp != nullptr) {
            cout << temp->vardas << " " << temp->pavarde << " " << temp->paz << endl;
            temp = temp->next;
        }
    }

    double spausdintiVidurki() {
        if (P == nullptr) {
            return 0.0;
        }

        int suma = 0;
        int kiekis = 0;
        list *temp = P;

        while (temp != nullptr) {
            suma += temp->paz;
            kiekis++;
            temp = temp->next;
        }

        return (double)suma / kiekis;
    }



};

int main() {
    
    pazymiuSarasas sarasas;

    ifstream fd("studentai.txt");

    if(!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo." << endl;
        return 1;
    }

    string v, p;
    int Pazymys;
    while (fd >> v >> p >> Pazymys) {
        sarasas.iterpti(v, p, Pazymys);
    }
    fd.close();

    //sarasas.spausdinti();

    int pasirinkimas;

    do{
        cout << "Studentu sarasas nuskaitytas is failo studentai.txt" << endl;
        sarasas.spausdinti();
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1 - Rikiuoti didziausiu" << endl;
        cout << "2 - Rikiuoti maziausiu" << endl;
        cout << "3 - Prideti studenta" << endl;
        cout << "4 - Pasalinti studenta" << endl;
        cout << "5 - Iseiti" << endl;
        cin >> pasirinkimas;

        if(pasirinkimas == 1){
        sarasas.rikiuoti(1);
        sarasas.spausdinti();
    } else if(pasirinkimas == 2){
        sarasas.rikiuoti(2);
        sarasas.spausdinti();
    } else if(pasirinkimas == 3){
        string vardas, pavarde;
        int paz;
        cout << "Iveskite varda: ";
        cin >> vardas;
        cout << "Iveskite pavarde: ";
        cin >> pavarde;
        cout << "Iveskite pazymi: ";
        cin >> paz;
        sarasas.iterpti(vardas, pavarde, paz);
    } else if(pasirinkimas == 4){
        string pavarde;
        cout << "Iveskite pavarde: ";
        cin >> pavarde;
        sarasas.pasalinti(pavarde);
    }

    } while (pasirinkimas != 5);

    

    return 0;
}
