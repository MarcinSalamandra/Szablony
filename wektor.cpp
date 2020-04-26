#include "wektor.h"
#include <math.h>

using std::cerr;
using std::endl;

/****************************************
* Konstruktor wektora bez argumentow    *
****************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE>::Vector() {
}

/*************************************
* Konstruktor wektora z argumentami  *
*************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE>::Vector(TYPE elem[]) {
    for(int i = 0; i < SIZE; i++) {
        data[i] = elem[i];
    }
}

/****************************************
* Metoda, ktora liczy dlugosc wektora   *
****************************************/

template <class TYPE, int SIZE>
double Vector<TYPE, SIZE>::length() const {
    double length = 0;      // zwracamy dlugosc jako double

    for(int i = 0; i < SIZE; i++) {        // liczymy kwadraty kolejnych pol i dodajemy
        length += pow(this->data[i], 2);
    }
    return sqrt(length);        // zwracamy pierwiastek z sumy kwadratow pol wektora
}

/****************************************************************************
* Specjalizacja dla metody liczacej dlugosc wektora dla liczby zespolonej   *
****************************************************************************/

template <>
double Vector<Complex, DIMENSION>::length() const {
    double length = 0;
    Complex helper;

    for(int i = 0; i < DIMENSION; i++) {
        helper = this->data[i] * (this->data[i]).coupling();
        length += helper.get_re();
    }
    return sqrt(length);
}

/************************************************
* Przeciazenie operatora mnozenia skalarnego    *
************************************************/

template <class TYPE, int SIZE>
TYPE Vector<TYPE, SIZE>::operator * (const Vector<TYPE, SIZE> & V2) const {
    TYPE result = 0;

    for(int i = 0; i < SIZE; i++) {        // mnozymy kolejne pola i dodajemy
        result += this->data[i] * V2[i];
    }
    return result;
}

/************************************************************************************
* Specjalizacja do przeciazenia operatora mnozenia wektorow z liczbami zespolonymi  *
************************************************************************************/

template <>
Complex Vector<Complex, DIMENSION>::operator * (const Vector<Complex, DIMENSION> & V2) const {
    Complex result(0, 0);

    for(int i = 0; i < DIMENSION; i++) {        // mnozymy kolejne pola i dodajemy
        result += this->data[i] * V2[i];
    }
    return result;
}

/********************************************************
* Przeciazenie operatora mnozenia wektora przez liczbe  *
********************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator * (const double & multipler) const {
    Vector result;      // zwracamy wynik jako wektor

    for(int i = 0; i < SIZE; i++) {    // mnozymy kolejne pola przez mnoznik
        result[i] = this->data[i] * multipler;
    }
    return result;
}

/********************************************************
* Przeciazenie operatora dzielenia wektora przez liczbe *
********************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator / (const double & divider) const {
    Vector result;      // zwracamy wynik jako wektor

    if(fabs(divider) < eps) {
        cerr << "Blad: Dzielenie przez 0!" << endl;
        exit(1);
    }
    for(int i = 0; i < SIZE; i++) {        // dzielimy kolejne pola przez dzielnik
        result[i] = this->data[i] / divider;
    }
    return result;
}

/********************************************************
* Przeciazenie operatora dodawania dla dwoch wektorow   *
********************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator + (const Vector<TYPE, SIZE> & V2) const {
    Vector result;      // zwracamy wynik jako wektor

    for(int i = 0; i < SIZE; i++) {        // dodajemy kolejne pola
        result[i] = this->data[i] + V2[i];
    }
    return result;
}

/********************************************************
* Przeciazenie operatora odejmowania dla dwoch wektorow *
********************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Vector<TYPE, SIZE>::operator - (const Vector<TYPE, SIZE> & V2) const {
    Vector result;      // zwracamy wynik jako wektor

    for(int i = 0; i < SIZE; i++) {        // odejmujemy kolejne pola
        result[i] = this->data[i] - V2[i];
    }
    return result;
}

/**************************************************************************************************
* Przeciazenie operatora indeksu dla dzialan typu: V[i] = x, czyli do edytowania pol prywatnych   *
**************************************************************************************************/

template <class TYPE, int SIZE>
TYPE & Vector<TYPE, SIZE>::operator [] (int index) {
    if(index < 0 || index >= SIZE) {
        cerr << "Blad: Zly indeks wektora" << endl;
        exit(1);
    }
    return data[index];
}

/****************************************************************************************************
* Przeciazenie operatora indeksu dla dzialan typu: x = V[i], czyli jedynie odczytu pol prywatnych   *
****************************************************************************************************/

template <class TYPE, int SIZE>
const TYPE & Vector<TYPE, SIZE>::operator [] (int index) const {
    if(index < 0 || index >= SIZE) {
        cerr << "Blad: Zly indeks wektora" << endl;
        exit(1);
    }
    return data[index];
}

/********************************************************************************************
* Przeciazenie operatora dla wyswietlenia wektora na wyjscie w formacie: | x y z ... n |    *
********************************************************************************************/

template <class TYPE, int SIZE>
ostream & operator << (ostream & str, const Vector<TYPE, SIZE> & V) {
    str << '|';     // zaipujemy kreske pionowa

    for(int i = 0; i < SIZE; i++) {        // nastepnie wszystkie pola wektora po spacji
        str << ' ' << V[i] << ' ';
    }
    str << '|';

    return str;
}

/****************************************************************************************
* Przeciazenie operatora dla wczytania wektora z wejscia w formacie: | x y z ... n |    *
****************************************************************************************/

template <class TYPE, int SIZE>
istream & operator >> (istream & str, Vector<TYPE, SIZE> & V) {
    char c;     // znak na kreske pionowa

    str >> c;       // wczytujemy otworzenie nawiasu

    if(c != '|') {
        str.setstate(std::ios::failbit);
    }
    for(int i = 0; i < SIZE; i++) {
        str >> V[i];       // wczytujemy pole wektora
    }
    str >> c;       // wczytujemy zamkniecie nawiasu

    if(c != '|') {
        str.setstate(std::ios::failbit);
    }
    return str;
}


















