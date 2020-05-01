#include "equation.h"
#include <string>

using std::endl;
using std::cout;
using std::string;
using std::cerr;
using std::cin;

int main(int argc, char *argv[])
{
    string option;        // opcja, czy rownanie macierzowe jest dla liczb rzeczywistych czy urojonych
    double length;      // dlugosc wektora bledu

    cout << endl;

    if(argc == 1) {     // sprawdzamy czy uzytkownik nie podal zbednych argumentow wywolania programu
        getline(cin, option);

        if(option.size() == 1) {        // sprawdzamy czy znak wariantu obliczen to rzeczywiscie znak czy ciag znakow
            switch(option[0]) {
                case 'r': {                                 // wybrano opcje z liczbami rzeczywistymi
                    Equation<double, DIMENSION> E;
                    Vector<double, DIMENSION> result;       // zmienne
                    Vector<double, DIMENSION> fault;

                    cin >> E;                               // sprawdzenie czy poprawnie zapisano macierz i wektor
                    if(!cin.good()) {
                            cerr << "Blad: Nie udalo sie wczytac ukladu rownan z pliku. Macierz lub wektor zostaly zle zapisane." << endl << endl;
                    exit(1);
                    }

                    result = E.calculate();                 // obliczenia w programie
                    fault = E.fault();
                    length = fault.length();

                    cout << "Rownanie macierzowe: " << endl;        // wyswietlenie wynikow na ekran
                    cout << endl << E << endl;
                    cout << "Rozwiazanie ukladu rownan liniowych opisuje wektor: ";
                    cout << endl << result << endl;
                    cout << endl << "Wektor bledu: " << endl;
                    cout << endl << fault << endl;
                    cout << endl << "Dlugosc wektora bledu: " << endl;
                    cout << endl << length << endl << endl;

                    break;
                }
                case 'z': {                                 // analogicznie dla liczb zespolonych
                    Equation<Complex, DIMENSION> E;
                    Vector<Complex, DIMENSION> result;
                    Vector<Complex, DIMENSION> fault;

                    cin >> E;
                    if(!cin.good()) {
                        cerr << "Blad: Nie udalo sie wczytac ukladu rownan z pliku. Macierz lub wektor zostaly zle zapisane." << endl << endl;
                        exit(1);
                    }

                    result = E.calculate();
                    fault = E.fault();
                    length = fault.length();

                    cout << "Rownanie macierzowe: " << endl;
                    cout << endl << E << endl;
                    cout << "Rozwiazanie ukladu rownan liniowych opisuje wektor: " << endl;
                    cout << endl << result << endl;
                    cout << endl <<"Wektor bledu: " << endl;
                    cout << endl << fault << endl;
                    cout << endl << "Dlugosc wektora bledu: " << endl;
                    cout << endl << length << endl << endl;

                    break;
                    }
                default : {
                    cerr << "Blad: Nie udalo sie wczytac ukladu rownan z pliku. Niedozwolony znak wyboru wariantu obliczen." << endl << endl;
                    exit(1);
                }
            }
        }
        else {
            cerr << "Blad: Nie udalo sie wczytac ukladu rownan z pliku. Niedozwolony znaku wyboru wariantu obliczen." << endl << endl;
            exit(1);
        }
    }
    else {     
        cerr << "Podano zbedne argumenty wywolania programu." << endl << endl;
    }
    return 0;
}
