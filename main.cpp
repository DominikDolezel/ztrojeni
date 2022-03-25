#include <iostream>
#include <bitset>
#include <time.h>

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
    bitset <BITU * 3> na_poz_bitset;
    naplnPoleNulami(zmenene_cislice, pocet_spatnych_cislic);

    for (int i = 0; i < pocet_spatnych_cislic; i++) {
        do {
            pozice_cislice = generujNahodneCislo(0, (BITU * 3) - 1);
        } while (jeVPoli(zmenene_cislice, pozice_cislice, pocet_spatnych_cislic));
        zmenene_cislice[i] = pozice_cislice;

        maska = vytvorMasku(BITU * 3 - pozice_cislice - 1);

        na_poz_bitset = maska & ztrojeno;

        if(na_poz_bitset == nula) {
            na_pozici = 0;
        } else {
            na_pozici = 1;
        }

        if (na_pozici) {
            maska = ~maska;
            ztrojeno = ztrojeno & maska;
        } else {
            ztrojeno = ztrojeno | maska;
        }
    }
    cout << "zmeneno: " << ztrojeno << endl;
    cout << "zmenene cislice: ";
    for (int i = 0; i < pocet_spatnych_cislic; i++) {
        cout << zmenene_cislice[i] + 1 << ". ";
    }
    cout << endl;
    return ztrojeno;
}

bitset <BITU * 3> trojitaMaska(short prvni_bit) {
    bitset <BITU * 3> trojita_maska;
    trojita_maska = nula;
    for (int i = prvni_bit; i < prvni_bit + 3; i++) {
        trojita_maska = trojita_maska | vytvorMasku(i);
    }
    return trojita_maska;
}

bitset <BITU * 3> oprava(bitset <BITU * 3> zmeneno) {
    bitset <BITU * 3> maska;
    bitset <BITU * 3> je_tu;
    bitset <BITU * 3> opraveno;
    opraveno = nula;
    short pocet_jednicek;
    for (int i = BITU - 1; i >= 0; i--) {
        pocet_jednicek = 0;
        //maska = trojitaMaska(i * 3);
        for (int j = 0; j < 3; j++) {
            maska = vytvorMasku(i * 3 + j);
            je_tu = maska & zmeneno;
            if (je_tu != nula) {
                pocet_jednicek++;
            }
        }

        if (pocet_jednicek == 3) {
            cout << "jaja ";
            opraveno = opraveno | trojitaMaska(i * 3);
        } else if (pocet_jednicek == 2) {
            cout << "falsch ";
            opraveno = opraveno | trojitaMaska(i * 3);
        } else if (pocet_jednicek == 1) {
            cout << "falsch ";
            opraveno = opraveno & ~trojitaMaska(i * 3);
        } else {
            cout << "jaja ";
            opraveno = opraveno & ~trojitaMaska(i * 3);
        }
        cout << endl;
    }
    return opraveno;
}

int main()
{
    int vstup;
    bitset <BITU * 3> ztrojeno, zmeneno, opraveno;

    cin >> vstup;

    ztrojeno = ztrojeni(vstup);

    zmeneno = nahodnaZmena(ztrojeno);

    opraveno = oprava(zmeneno);

    cout << "opraveno: " << opraveno;
}
