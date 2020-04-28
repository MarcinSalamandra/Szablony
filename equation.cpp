#include "equation.h"
#include <math.h>
#include <string>
#include <iomanip>
#include <sstream>

using std::setw;
using std::ostringstream;
using std::endl;
using std::string;

/************************************************************
* Konstruktor bezargumentowy dla ukladu rownan liniowych    *
************************************************************/

template <class TYPE, int SIZE>
Equation<TYPE, SIZE>::Equation() {
}

/********************************************************
* Konstruktor z argumentam dla ukladu rownan liniowych  *
********************************************************/

template <class TYPE, int SIZE>
Equation<TYPE, SIZE>::Equation(Matrix<TYPE, SIZE> Ma, Vector<TYPE, SIZE> Ve) {
    M = Ma;
    V = Ve;
}

/************************************
* Pobieramy macierz z ukladu rownan *
************************************/

template <class TYPE, int SIZE>
const Matrix<TYPE, SIZE> & Equation<TYPE, SIZE>::get_M() const {
    return this->M;
}

/************************************
* Pobieramy wektor z ukladu rownan  *
************************************/

template <class TYPE, int SIZE>
const Vector<TYPE, SIZE> & Equation<TYPE, SIZE>::get_V() const {
    return this->V;
}

/******************************************************************
* Przypisujemy polu macierzy z ukladu rownan odpowiednie wartosci *
******************************************************************/

template <class TYPE, int SIZE>
void Equation<TYPE, SIZE>::set_M(const Matrix<TYPE, SIZE> & Ma) {
    this->M = Ma;
}

/******************************************************************
* Przypisujemy polu wektora z ukladu rownan odpowiednie wartosci  *
******************************************************************/

template <class TYPE, int SIZE>
void Equation<TYPE, SIZE>::set_V(const Vector<TYPE, SIZE> & Ve) {
    this->V = Ve;
}

/****************************************************************
* Metoda calculate wyznacza rozwiazania ukladu rownan liniowych *
****************************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Equation<TYPE, SIZE>::calculate() const {
    Vector<TYPE, SIZE> result;

    result = this->M.invert() * this->V;        // odwracamy macierz przedstawiajaca rownania i mnozymy ja razy wektor przedstawiajacy wyniki tych rownan, powstaje wektor skladajacy sie z rozwiazan ukladu

    return result;
}

/********************************************************************************
* Przeciazenie operatora do wczytania ukladu rownan ze strumienia wejsciowego   *
********************************************************************************/

template <class TYPE, int SIZE>
istream & operator >> (istream & str, Equation<TYPE, SIZE> & E) {
    Matrix<TYPE, SIZE> Ma;      // pomocnicza macierz i wektor
    Vector<TYPE, SIZE> Ve;

    str >> Ma;      // pobieramy macierz
    E.set_M(Ma.transposition());

    str >> Ve;      // nastepnie wektor
    E.set_V(Ve);

    return str;
}

/********************************************************************************
* Przeciazenie operatora do wyswietlenia ukladu rownan na strumien wyjsciowy    *
********************************************************************************/

template <class TYPE, int SIZE>
ostream & operator << (ostream & str, const Equation<TYPE, SIZE> & E) {
    Matrix<TYPE, SIZE> Ma;      // pomocnicza macierz i wektor wynikowy
    Vector<TYPE, SIZE> Ve;
    ostringstream ss;       // objekt do operowania stringami
    int v_len;              // szerokosc kolumny wynikowej
    int m_len[SIZE];   // szerokosc kolumn w macierzy
    int max_v_len = 0;      // maksymalna szerokosc kolumny wynikowej
    int max_m_len[SIZE];   // maksymalna szerokosc kolumn w macierzy
    string vec;     // pomocniczy string

    for(int i = 0; i < DIMENSION; i++) {
        max_m_len[i] = 0;
    }

    Ma = E.get_M();     // pobieramy macierz i wektor z klasy
    Ve = E.get_V();

    for(int j = 0; j < SIZE; j++) {
        ss << Ve[j];        // do zawartosci strumienia dodajemy wartosc z kolumny wynikowej
        vec = ss.str();     // przepisujemy to do stringa
        ss.str("");         // resetujemy zawartosc strumienia
        ss.clear();

        v_len = vec.size();        // pobieramy dlugosc kazdej liczby w kolumnie
        if(v_len > max_v_len) {
            max_v_len = v_len;        // znajdujemy "najszersze" miejsce w kolumnie, wzgledem tej szerokosci bedziemy wstawiac spacje, gdy wyswietlamy kolumne wynikowa
        }
    }
    for(int i = 0; i < SIZE; i++) {
        for(int k = 0; k < SIZE; k++) {
            ss << Ma[i][k];      // dodajemy liczbe double do zawartosci strumienia
            vec = ss.str();     // do naszego stringa przypisujemy zwracanego stringa z aktualna zawartoscia strumienia, uzywajac funkcji to_string gdy pobieralem double, np double x=6;,
                                // do stringa zapisywala sie liczba 6.000000 przez co "dlugosc" liczby byla nieprawidlowa, znalazlem w internecie rozwiazanie z klasa ostringstream i biblioteka sstream
            ss.str("");         // resetujemy zawartosc strumienia
            ss.clear();
            m_len[k] = vec.size();        // pobieramy dlugosc kazdej liczby w macierzy
            if(m_len[k] > max_m_len[k]) {
                max_m_len[k] = m_len[k];        // znajdujemy "najszersza" kolumne w macierzy, wzgledem tej szerokosci bedziemy wstawiac spacje, gdy wyswietlamy macierz
            }
        }
    }
    for(int i = 0; i < SIZE; i++) {        // petla odpowiedzialna za wyswietlenie ukladu rownan w odpowiednim formacie
        str << "|";
        for(int j = 0; j < SIZE; j++) {
            str << ' ' << setw(max_m_len[j]) << Ma[i][j] << ' ';
        }
        str << "|";

        if(i == SIZE / 2) {
            str << "   X  " << " | " << "x_" << i + 1 << " |" << "   =   " << "| " << setw(max_v_len) << Ve[i] << " |" << endl;
        }
        else {
            str << "       | " << "x_" << i + 1 << " |" << "       " << "| " << setw(max_v_len) << Ve[i] << " |" << endl;
        }
    }
    return str;
}

/********************************************************************************
* Specjalizacja dla przeciazenia operatora do wyswietlania ukladu na wyjsciu    *
********************************************************************************/

template <>
ostream & operator << (ostream & str, const Equation<Complex, DIMENSION> & E) {
    Matrix<Complex, DIMENSION> Ma;      // pomocnicza macierz i wektor wynikowy
    Vector<Complex, DIMENSION> Ve;
    ostringstream ss;       // objekt do operowania stringami
    int v_len[DIMENSION];              // szerokosc kolumny wynikowej
    int m_len[DIMENSION][DIMENSION];   // szerokosc kolumn w macierzy
    int max_v_len = 0;      // maksymalna szerokosc kolumny wynikowej
    int max_m_len[DIMENSION];   // maksymalna szerokosc kolumn w macierzy
    string vec;     // pomocniczy string

    for(int i = 0; i < DIMENSION; i++) {
        max_m_len[i] = 0;
    }

    Ma = E.get_M();     // pobieramy macierz i wektor z klasy
    Ve = E.get_V();

    for(int j = 0; j < DIMENSION; j++) {
        ss << Ve[j];        // do zawartosci strumienia dodajemy wartosc z kolumny wynikowej
        vec = ss.str();     // przepisujemy to do stringa
        ss.str("");         // resetujemy zawartosc strumienia
        ss.clear();

        v_len[j] = vec.size();        // pobieramy dlugosc kazdej liczby w kolumnie
        if(v_len[j] > max_v_len) {
            max_v_len = v_len[j];        // znajdujemy "najszersze" miejsce w kolumnie, wzgledem tej szerokosci bedziemy wstawiac spacje, gdy wyswietlamy kolumne wynikowa
        }
    }
    for(int i = 0; i < DIMENSION; i++) {
        for(int k = 0; k < DIMENSION; k++) {
            ss << Ma[i][k];      // dodajemy liczbe double do zawartosci strumienia
            vec = ss.str();     // do naszego stringa przypisujemy zwracanego stringa z aktualna zawartoscia strumienia, uzywajac funkcji to_string gdy pobieralem double, np double x=6;,
                                // do stringa zapisywala sie liczba 6.000000 przez co "dlugosc" liczby byla nieprawidlowa, znalazlem w internecie rozwiazanie z klasa ostringstream i biblioteka sstream
            ss.str("");         // resetujemy zawartosc strumienia
            ss.clear();
            m_len[i][k] = vec.size();        // pobieramy dlugosc kazdej liczby w macierzy
            if(m_len[i][k] > max_m_len[k]) {
                max_m_len[k] = m_len[i][k];        // znajdujemy "najszersza" kolumne w macierzy, wzgledem tej szerokosci bedziemy wstawiac spacje, gdy wyswietlamy macierz
            }
        }
    }
    for(int i = 0; i < DIMENSION; i++) {        // petla odpowiedzialna za wyswietlenie ukladu rownan w odpowiednim formacie
        str << "|";
        for(int j = 0; j < DIMENSION; j++) {
            str << ' ' << setw(max_m_len[j] - m_len[i][j] + 1) << Ma[i][j] << ' ';
        }
        str << "|";

        if(i == DIMENSION / 2) {
            str << "   X  " << " | " << "x_" << i + 1 << " |" << "   =   " << "| " << setw(max_v_len - v_len[i] + 1) << Ve[i] <<" |" << endl;
        }
        else {
            str << "       | " << "x_" << i + 1 << " |" << "       " << "| " << setw(max_v_len - v_len[i] + 1) << Ve[i] << " |" << endl;
        }
    }
    return str;
}

/************************************
* Metoda fault oblicza wektor bledu *
************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Equation<TYPE, SIZE>::fault() const {
    Vector<TYPE, SIZE> result;

    result = this->M * this->calculate() - this->V;

    return result;
}







