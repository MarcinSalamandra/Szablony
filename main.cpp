#include "wektor.h"
#include <string>
#include <fstream>

using std::endl;
using std::cout;
using std::string;
using std::ifstream;
using std::cerr;

const string file_name = "test";

int main() {



    /****** TESTY DLA DOUBLE ******/


    // test czytania z pliku i przeciazenia operatora >> jak i operatora <<
    ifstream file;
    file.open(file_name);
    Vector<double, DIMENSION> V1;
    file >> V1;
    cout << "Pierwszy wektor wczytany z pliku: " << endl << V1 << endl;

    // test konstruktora parametrycznego
    double tab[DIMENSION] = {2, 2, 0, 4, 1};
    Vector<double, 5> V(tab);
    cout << "Drugi wektor zrobiony recznie: " << endl << V << endl;

    // test metod:

    // dlugosc wektora
    double dlugosc;
    dlugosc = V.length();
    cout << "Dlugosc drugiego wektora: " << endl << dlugosc << endl;

    // przeciazenia operatorow
    double result;
    result = V1 * V;
    cout << "Wynik mnozenia tych wektorow: " << endl << result << endl;

    Vector<double, DIMENSION> wynik;
    wynik = V1 * 5;
    cout << "Wynik mnozenia pierwszego wektora przez 5" << endl << wynik << endl;

    wynik = V1 / 2;
    cout << "Wynik dzielenia pierwszego wektora przez 2 " << endl << wynik << endl;

    wynik = V1 - V;
    cout << "Wynik odejmowania drugiego wektora od pierwszego " << endl << wynik << endl;

    wynik = V1 + V;
    cout << "Wynik dodawania tych wektorow " << endl << wynik << endl;

    // test indeksowania wektora
    double a;
    a = V1[2];
    cout << "Trzeci element pierwszego wektora to: " << endl << a << endl;

    double b = 3;
    V1[2] += b;
    cout << "Trzeci element pierwszego wektora powiekszony o 3 wynosi: " << endl << V1[2] << endl;


    /****** TESTY DLA COMPLEX ******/


    cout << endl;
    Vector<Complex, DIMENSION> V2;
    file >> V2;
    cout << "Wektor liczb zespolonych wczytany z pliku: " << endl << V2 << endl;
    Complex Cn1(2, 3);
    Complex Cn2(6, -3);
    Complex Cn3(-1, 3);
    Complex Cn4(-2, -3);
    Complex Cn5(2, -7);
    Complex tab1[DIMENSION] = {Cn1, Cn2, Cn3, Cn4, Cn5};
    Vector<Complex, DIMENSION> V3(tab1);
    cout << "Wektor stworzony recznie: " << endl << V3 << endl;

    dlugosc = V2.length();
    cout << "Dlugosc pierwszego wektora: " << endl << dlugosc << endl;

    // przeciazenia operatorow
    Complex cresult;
    cresult = V2 * V3;
    cout << "Wynik mnozenia tych wektorow: " << endl << cresult << endl;

    Vector<Complex, DIMENSION> cwynik;
    cwynik = V2 * 5;
    cout << "Wynik mnozenia pierwszego wektora przez 5" << endl << cwynik << endl;

    cwynik = V2 / 2;
    cout << "Wynik dzielenia pierwszego wektora przez 2 " << endl << cwynik << endl;

    cwynik = V2 - V3;
    cout << "Wynik odejmowania drugiego wektora od pierwszego " << endl << cwynik << endl;

    cwynik = V2 + V3;
    cout << "Wynik dodawania tych wektorow " << endl << cwynik << endl;

    // test indeksowania wektora
    Complex c;
    c = V2[2];
    cout << "Trzeci element pierwszego wektora to: " << endl << c << endl;

    Complex d(4, -13);
    V2[2] += d;
    cout << "Trzeci element pierwszego wektora powiekszony o (4, -13) wynosi: " << endl << V2[2] << endl;



    file.close();

    return 0;
}
