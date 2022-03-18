#include <iostream>
#include <bitset>

using namespace std;

const short BITU = 24;
bitset<BITU> nula(0);

int dvaNa(short kolikatou) {
    int vysledek = 1;
    for (int i = 0; i < kolikatou; i++) {
        vysledek *= 2;
    }
    return vysledek;
}

bitset<BITU> maska(short bit) {
    bitset<BITU> maska_bitset(dvaNa(bit));
    return maska_bitset;
}

int ztrojeni(int vstup) {
    int vysledek = 0b0;
    bitset<BITU> binarni(vstup);
    bitset<BITU> vysledek(0);
    cout << binarni << endl << endl;

    short j = 0;

    for (short i = 0; i < BITU; i++) {
        cout << maska(i) << endl;
        bitset<BITU> tady_je = maska(i) & binarni;
        if (tady_je != nula) {
            for(int k = 0; k < 3; k++) {
                vysledek += maska(dvaNa(k))
            }
        }
    }

    return 1;
}

int main()
{
    int vstup, ztrojeno;
    cin >> vstup;

    ztrojeno = ztrojeni(vstup);
}
