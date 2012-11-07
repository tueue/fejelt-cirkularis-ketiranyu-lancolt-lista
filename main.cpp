/* 
 * 
 * File         : main.cpp
 * Author       : tueue
 * Description  : Pannon ADAL hazifeladat: fejelet-korkorosen-ketszeresen lancolt lista.
 * Date         : 2012-11-02
 *  
 */

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class KLLista {
private:
    struct listaElem {
        string szoveg;
        int szam;
        listaElem* kov;
        listaElem* elo;
    };
    listaElem* fej;
public:
    KLLista() {
        fej = new listaElem;
        fej->elo = fej; // nem korokorosnel = NULL
        fej->kov = fej; // nem korokorosnel = NULL
    }
    ~KLLista() {
        listaElem* akt;
        for (akt = fej->kov; akt != fej; akt = akt->kov) // vegigmegyek a listan
            delete akt;
        //fej->elo, fej->kov = fej;
    }
    void beszur(const string&, const int);
    void torol(const string&);
    bool keres(const string&);
    friend ostream& operator<<(ostream&, const KLLista&);
    void listaz(const int);
};

void KLLista::beszur(const string& adat, const int szam) {
    listaElem* ujElem = new listaElem;
    ujElem->szoveg = adat;
    ujElem->szam = szam;
    if (fej->kov == fej && fej->elo == fej) { // meg ures a lista
        fej->kov = ujElem; // fej mutat elso elemre
        fej->elo = ujElem; // fej mutat utolso elemre
        ujElem->elo = fej;
        ujElem->kov = fej;
    } else { // mar nem ures a lista
        listaElem* akt;
        string hova;
        cout << " Hova, elejére vagy végére? (e/v): ";
        cin >> hova;
        if ( hova == "e" ) { // beszuras a lista elejere
                ujElem->elo = fej;
                ujElem->kov = fej->kov;
                (fej->kov)->elo = ujElem;
                fej->kov = ujElem;                
        } else if ( hova == "v" ) { // beszuras a vegere
                ujElem->kov = fej;
                ujElem->elo = fej->elo;
                (fej->elo)->kov = ujElem;
                fej->elo = ujElem;
        } else
            cout << " Hibas bemenet! " << endl;    
    }

}

void KLLista::torol(const string& adat) {
    listaElem* akt;
    if( KLLista::keres(adat) ) {
        for (akt = fej->kov; akt != fej; akt = akt->kov) { // vegigmegyek a listan
            if (akt->szoveg == adat) {
                if (akt == fej->kov) { // elso elem?
                    (akt->kov)->elo = fej;
                    fej->kov = akt->kov;
                } else if (akt->kov == fej) { // utolso elem?
                    (akt->elo)->kov = akt->kov;
                    fej->elo = (akt->elo)->elo;
                } else { // kozbenso elem?
                    (akt->elo)->kov = akt->kov;
                    (akt->kov)->elo = akt->elo;
                }
            }
        }
    } else 
        cout << " Nincs benne a listában! " << endl;
}

void KLLista::listaz(const int merre) {
    KLLista::listaElem* akt;
    if(merre == 1) { // irany: elore
        for (akt = KLLista::fej->kov; akt != KLLista::fej; akt = akt->kov) {
            cout << "{ " << akt->szoveg << " :: " << akt->szam << " }";
            if (akt->kov != KLLista::fej)
                cout << "<->";
        }
    } else if( merre == 2) { // irany: hatra
        for (akt = KLLista::fej->elo; akt != KLLista::fej; akt = akt->elo) {
            cout << "{ " << akt->szoveg << " :: " << akt->szam << " }";
            if (akt->elo != KLLista::fej)
                cout << "<->";
        }
    } else { // nem 1 vagy 2 a bemenet
        cout << " Hiba a listázáskor! " << endl;
        return;
    }
    cout << endl;
}

bool KLLista::keres(const string& adat) {
    bool letezik = false;
    listaElem* akt;
    if( KLLista::fej->elo == KLLista::fej && KLLista::fej->kov == KLLista::fej ) {
        cout << " A lista üres! ";
        return letezik;
    }
    for (akt = fej->kov; akt != fej; akt = akt->kov) { // vegigmegyek a listan
        if( akt->szoveg == adat )
            letezik = true;
    }    
    return letezik;
}

ostream& operator<<(ostream& ostr, const KLLista& kll) {
    // elore kilistazza a teljes listát
    if ((kll.KLLista::fej)->kov == kll.KLLista::fej) 
        ostr << " A lista üres! " << endl;
    else {
        KLLista::listaElem* akt;
        for (akt = (kll.KLLista::fej->kov); akt != kll.KLLista::fej; akt = akt->kov) {
            ostr << " { " << akt->szoveg << " | " << akt->szam << " } ";
            if (akt->kov != kll.KLLista::fej)
                ostr << " <-> ";
        }
        ostr << endl;
        return ostr;
    }
}

void clear_screen() {
    #ifdef WINDOWS
        system("CLS");
    #else
        // Assume POSIX
        system("clear");
    #endif
}

int main() {
    KLLista lista;    
    int mch, num;
    string temp, merrol;
    clear_screen();
    while (1) {        
        cout << endl;
        cout << " Fejelt-Körkörös-Duplán-Láncolt Lista" << endl;
        cout << " ------------------------------------" << endl;
        cout << "  1. Beszúrás " << endl;
        cout << "  2. Törlés " << endl;
        cout << "  3. Listázás " << endl;
        cout << "  4. Keres" << endl;
        cout << "  5. Kilépés " << endl;
        cout << " ------------------------------------" << endl;
        cout << " Választás : ";
        cin >> mch;
        switch (mch) {
            case 1: clear_screen();
                cout << " Add meg, hogy mit adjak a listához:" << endl;
                cout << " Szoveg: ";
                cin.ignore();
                getline(cin, temp);
                cout << " Szam: ";
                cin >> num;
                lista.beszur(temp, num);
                break;
            case 2: clear_screen();
                cout << " Add meg, h mit töröljek a listából (szoveg) : ";
                cin.ignore();
                getline(cin, temp);
                lista.torol(temp);
                break;
            case 3: clear_screen();
                cout << " Előre vagy visszafele listázzam? (e/v): ";
                cin >> merrol;
                cout << " A lista tartalma : ";
                if ( merrol == "e" )                    
                    cout << lista;
                else 
                    if ( merrol == "v")
                        lista.listaz(2);
                    else
                        cout << " Hibas bemenet! "  << endl;
                break;
            case 4: clear_screen();
                cout << " Add meg, h mit keressek a listában (szoveg) : ";
                cin.ignore();
                getline(cin, temp);
                if( lista.keres(temp) )
                    cout << " Benne van a listában! " << endl;
                else
                    cout << " Nincs benne a listában! " << endl;                    
                break;
            case 5: exit;
                return 0;
                break;
            default: clear_screen();
                cout << " EEeee, ilyen nincs! ";
                break;
        }
    }    
    return 0;
}