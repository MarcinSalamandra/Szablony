#include "equation.h"
#include <string>
#include <fstream>

using std::endl;
using std::cout;
using std::string;
using std::ifstream;
using std::cerr;

int main(int argc, char *argv[])
{
    if(argc == 2) {
        string option;
        option = argv[1];
        if(option.size() == 1) {
            switch(*argv[1]) {
                case 'r': {
                    string file_name = "Test1";
                    Equation<double, DIMENSION> E;
                    Vector<double, DIMENSION> result;
                    Vector<double, DIMENSION> fault;

                    ifstream file;
                    double length;

                    file.open(file_name);
                    if(!file.good()) {
                        cerr << "Blad: Nie udalo sie otworzyc pliku." << endl;
                        exit(1);
                    }

                    file >> E;
                    if(!file.good()) {
                        cerr << "Blad: Nie udalo sie wczytac ukladu rownan z pliku." << endl;
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

                    file.close();
                    break;
                }
                case 'z': {
                    string file_name = "Test2";
                    Equation<Complex, DIMENSION> E;
                    Vector<Complex, DIMENSION> result;
                    Vector<Complex, DIMENSION> fault;

                    ifstream file;
                    double length;

                    file.open(file_name);
                    if(!file.good()) {
                        cerr << "Blad: Nie udalo sie otworzyc pliku." << endl;
                        exit(1);
                    }

                    file >> E;
                    if(!file.good()) {
                        cerr << "Blad: Nie udalo sie wczytac ukladu rownan z pliku." << endl;
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

                    file.close();
                    break;
                }
                default : {
                    cerr << "Blad: Podano zly argument wywolania programu. Dopuszczalne argumenty to: 'r' lub 'z'." << endl;
                    exit(1);
                }
            }
        }
        else {
            cerr << "Blad: Podano zly argument wywolania programu. Dopuszczalne argumenty to: 'r' lub 'z'." << endl;
            exit(1);
        }
    }
    else {
        cerr << "Blad: Podano nieprawidlowa liczbe argumentow wywolania programu." << endl;
        exit(1);
    }
    return 0;
}
