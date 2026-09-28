#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct list{
    string vardas;
    string pavarde;
    int paz;
    list *next;
} List;

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

    void iterpti(int paz){
        list *naujas = new list;
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
                if ((pasirinkimas == 1 && temp->paz > temp->next->paz) ||
                    (pasirinkimas == 2 && temp->paz < temp->next->paz)) {
                    
                    list *tempp = temp->next;
                    temp->next = tempp->next;
                    tempp->next = temp;

                    if (tempp == nullptr) {
                        P = tempp; 
                    } else {
                        tempp->next = tempp;
                    }

                    pakeista = true;
                }
                tempp = temp;
                temp = temp->next;
            }
        } while (pakeista);
    }

    void spausdinti() {
        list *temp = P;
        while (temp != nullptr) {
            cout << temp->paz << " ";
            temp = temp->next;
        }
        cout << endl;
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

    ifstream fd("duomenys.txt");

    if(!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo." << endl;
        return 1;
    }

    int Pazymys;

    while (fd >> Pazymys) {
        sarasas.iterpti(Pazymys);
    }
    fd.close();

    sarasas.spausdinti();
    cout << "Vidurkis: " << sarasas.spausdintiVidurki() << endl;

    return 0;
}
