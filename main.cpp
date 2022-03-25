#include <iostream>
#include <bitset>

using namespace std;

const short BITU = 8;
bitset <BITU * 3> nula(0);

int dvaNa(short kolikatou) {
    int vysledek = 1;
    for (int i = 0; i < kolikatou; i++) {
        vysledek *= 2;
    }
    return vysledek;
}

bitset <BITU * 3> vytvorMasku(short bit) {
    bitset<BITU * 3> maska_bitset(dvaNa(bit));
    return maska_bitset;
}

bitset <BITU * 3> ztrojeni(int vstup) {
    bitset<BITU * 3> binarni(vstup);
    bitset<BITU * 3> vysledek(0);
    //cout << binarni << endl << endl;

    short j = 0;

    for (short i = 0; i < BITU; i++) {
        //cout << maska(i) << endl;
        bitset<BITU * 3> tady_je = vytvorMasku(i) & binarni;
        if (tady_je != nula) {
            //cout << true << endl;
            for(int k = j; k < j+3; k++) {
                vysledek = vysledek | vytvorMasku(k);
            }
            j += 3;
        } else {
            //cout << false << endl;
            j += 3;
        }
    }
    cout << "vysledek ztrojeni: " << vysledek << endl;

    return vysledek;
}

int generujNahodneCislo(short od, short do_vc) {
    srand (time(NULL));

    return rand() % (do_vc - od + 1) + od;
}

void naplnPoleNulami(int *pole, short pocet_prvku) {
    for (int i = 0; i < pocet_prvku; i++) {
        pole[i] = 0;
    }
}

bool jeVPoli(int *pole, int prvek, short pocet_prvku) {
    for (int i = 0; i < pocet_prvku; i++) {
        if (pole[i] == prvek) {
            return true;
        }
    }
    return false;
}

bitset <BITU * 3> nahodnaZmena(bitset <BITU * 3> ztrojeno) {
    int pocet_spatnych_cislic = generujNahodneCislo(1, 2);
    int zmenene_cislice[pocet_spatnych_cislic], pozice_cislice;
    short na_pozici;
    bitset <BITU * 3> maska;
    naplnPoleNulami(zmenene_cislice, pocet_spatnych_cislic);

    for (int i = 0; i < pocet_spatnych_cislic; i++) {
        do {
            pozice_cislice = generujNahodneCislo(0, (BITU * 3) - 1);
        } while (jeVPoli(zmenene_cislice, pozice_cislice, pocet_spatnych_cislic));
        zmenene_cislice[i] = pozice_cislice;

        maska = vytvorMasku(BITU * 3 - pozice_cislice - 1);
        na_pozici = maska & ztrojeno;

        if (na_pozici) {
            maska = ~maska;
            ztrojeno = ztrojeno & maska;
        } else {
            ztrojeno = ztrojeno | maska;
        }
        cout << ztrojeno;
    }
}

int main()
{
    int vstup;
    bitset <BITU * 3> ztrojeno, zmeneno;

    cin >> vstup;

    ztrojeno = ztrojeni(vstup);

    zmeneno = nahodnaZmena(ztrojeno);
}
