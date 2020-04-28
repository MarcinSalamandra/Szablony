#include "matrix.h"
#include <math.h>
#include <string>
#include <iomanip>
#include <sstream>

using std::cerr;
using std::endl;
using std::string;
using std::setw;
using std::ostringstream;

/********************************************
* Konstruktor bezargumentowy dla macierzy   *
********************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE>::Matrix() {
}

/********************************************************************************************
* Konstruktor z argumentami dla macierzy, macierz to tablica wektorów czyli tablica tablic  *
********************************************************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE>::Matrix(Vector<TYPE, SIZE> elem[]) {
    for(int i = 0; i < SIZE; i++) {
        field[i] = elem[i];
    }
}

/********************************************************************************************************
* Przeciazenie operatora indeksowania dla macierzy, takiego by dostac wektor, do dzialan typu V = M[i]  *
********************************************************************************************************/

template <class TYPE, int SIZE>
const Vector<TYPE, SIZE> & Matrix<TYPE, SIZE>::operator [] (int index) const {
    if(index < 0 || index >= SIZE) {
        cerr << "Blad: Zly indeks macierzy" << endl;
        exit(1);
    }
    return field[index];
}

/********************************************************************************************************
* Przeciazenie operatora indeksowania dla macierzy, takiego by dostac wektor, do dzialan typu M[i] = V  *
********************************************************************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> & Matrix<TYPE, SIZE>::operator [] (int index) {
    if(index < 0 || index >= SIZE) {
        cerr << "Blad: Zly indeks macierzy" << endl;
        exit(1);
    }
    return field[index];
}

/************************************************************
* Metoda make_unit zamienia macierz na macierz jednostkowa  *
************************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::make_unit() {
   for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            this->field[i][j] = 0;
        }
    this->field[i][i] = 1;
    }

    return *this;
}

/**********************************************************
* Metoda swap_rows zamienia miejscami wiersze macierzy    *
**********************************************************/

template <class TYPE, int SIZE>
void Matrix<TYPE, SIZE>::swap_rows(int index1, int index2) {
    Vector<TYPE, SIZE> helper;

    helper = this->field[index1];
    this->field[index1] = this->field[index2];
    this->field[index2] = helper;
}

/********************************
* Metoda invert odwraca macierz *
********************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::invert() const {
    Matrix diagnal = *this;      // tworzymy macierz, ktora przeksztalcamy do macierzy diagonalnej, nastepnie dzielimy wiersze i powstaje macierz jednostkowa
    TYPE multipler;       // mnoznik, potrzebny do zerowania kolejnych pozycji w macierzy
    Matrix unit;
    unit.make_unit();

    // najpierw zerujemy pozycje pod glowna przekatna macierzy diagnal
    for(int i = 0; i < SIZE - 1; i++) {        // petla odpowiedzialna za przesuniecie zerowanego miejsca w prawo lub lewo
        for(int j = i + 1; j < SIZE; j++) {        // petla odpowiedzialna za przesuniecie zerowanego miejsca w dol lub w gore
            if(abs(diagnal[i][i]) < eps) {      // sprawdzamy czy na przekatnej nie ma zera, jesli jest to w dalszej czesci programu pojawi sie dzielenie przez 0, wiec wyswietlamy blad
                int found = 0;
                for(int k = i + 1; k < SIZE && found == 0; k++) {
                    diagnal.swap_rows(i, k);
                    unit.swap_rows(i, k);
                    if(abs(diagnal[i][i]) >= eps) {
                        found = 1;
                    }
                }
                if(abs(diagnal[i][i]) < eps) {
                    cerr << "Blad: Dzielenie przez 0!" << endl;
                    exit(1);
                }
            }
            multipler = -diagnal[j][i] / diagnal[i][i];     // liczymy mnoznik
            diagnal[j] = diagnal[j] + diagnal[i] * multipler;       // redukujemy wiersze, zerujac pola pod przekatna
            unit[j] = unit[j] + unit[i] * multipler;        // te sama redukcje wykonujemy dla jednostowej, dzieki temu zamieni sie ona na macierz odwrotna do poczatkowej macierzy diagnal
        }
    }
    // teraz zerujemy pozycje nad glowna przekatna macierzy, otrzymujemy macierz diagonalna
    for(int i = SIZE - 1; i > 0; i--) {       // petla odpowiedzialna za przesuniecie zerowanego miejsca w prawo lub lewo
        for(int j = i - 1; j >= 0; j--) {       // petla odpowiedzialna za przesuniecie zerowanego miejsca w dol lub w gore
            if(abs(diagnal[i][i]) < eps) {                                     // reszta analogicznie jak wyzej
                cerr << "Blad: Dzielenie przez 0!" << endl;
                exit(1);
            }
            multipler = -diagnal[j][i] / diagnal[i][i];
            diagnal[j] = diagnal[j] + diagnal[i] * multipler;
            unit[j] = unit[j] + unit[i] * multipler;
        }
    }
    for(int i = 0; i < SIZE; i++) {        // diagnal jest macierza diagonalna, zeby otrzymac jednostkowa, trzeba podzielic wiersze przez elementy na przekatnej, to samo dzielenie robimy dla macierzy unit
        unit[i] = unit[i] / diagnal[i][i];
    }
    return unit;
}

/****************************************************************************************
* Metoda take_column bierze kolumne z macierzy, co przydaje sie w jej transponowaniu    *
****************************************************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Matrix<TYPE, SIZE>::take_column(int index) const {
    if(index < 0 || index >= SIZE) {
        cerr << "Blad: Zly indeks macierzy" << endl;
        exit(1);
    }
    Vector<TYPE, SIZE> V;

    for(int i = 0; i < SIZE; i++) {
        V[i] = this->field[i][index];       // zamieniamy wiersz na kolumne
    }
    return V;
}

/********************************************************************************
* Metoda determinant liczy wyznacznik z macierzy za pomoca eliminacji Gaussa    *
********************************************************************************/

template <class TYPE, int SIZE>
TYPE Matrix<TYPE, SIZE>::determinant() const {
    TYPE det;
    det = 1;
    Matrix M = *this;
    TYPE multipler;       // mnoznik, potrzebny do zerowania kolejnych pozycji w macierzy

    // zerujemy pozycje pod glowna przekatna macierzy
    for(int i = 0; i < SIZE - 1; i++) {        // petla odpowiedzialna za przesuniecie zerowanego miejsca w prawo lub lewo
        for(int j = i + 1; j < SIZE; j++) {        // petla odpowiedzialna za przesuniecie zerowanego miejsca w dol lub w gore
            if(abs(M[i][i]) < eps) {      // sprawdzamy czy na przekatnej nie ma zera, jesli jest to w dalszej czesci programu pojawi sie dzielenie przez 0, wiec wyswietlamy blad
                int found = 0;
                for(int k = i + 1; k < SIZE && found == 0; k++) {
                    M.swap_rows(i, k);
                    det *= (-1);
                    if(abs(M[i][i]) >= eps) {
                        found = 1;
                    }
                }
                if(abs(M[i][i]) < eps) {
                    det = 0;
                    return det;
                }
            }
            multipler = -M[j][i] / M[i][i];       // wyliczamy mnoznik
            M[j] = M[j] + M[i] * multipler;      // redukujemy wiersze zerujac tym samym pola pod przekatna
        }
    }
    for(int i = 0; i < SIZE; i++) {
        det *= M[i][i];       // mnozymy pola na przekatnej
    }
    return det;
}

/********************************************************
* Metoda transposition tworzy macierz transponowana     *
********************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::transposition() const {
    Matrix result;

    for(int i = 0; i < SIZE; i++) {
        result[i] = this->take_column(i);       // zamieniamy wiersze na kolumny
    }
    return result;
}

/****************************************************
* Przeciazenie operatora dodawania dwoch macierzy   *
****************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator + (const Matrix<TYPE, SIZE> & M2) const {
    Matrix result;      // zwracany wynik to macierz

    for(int i = 0; i < SIZE; i++) {
        result[i] = this->field[i] + M2[i];
    }
    return result;
}

/******************************************************
* Przeciazenie operatora odejmowania dwoch macierzy   *
******************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator - (const Matrix<TYPE, SIZE> & M2) const {
    Matrix result;      // zwracany wynik to macierz

    for(int i = 0; i < DIMENSION; i++) {
        result[i] = this->field[i] - M2[i];
    }
    return result;
}

/********************************************************
* Przeciazenie operatora mnozenia macierzy przez skalar *
********************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator * (const TYPE & multipler) const {
    Matrix result;

    for(int i = 0; i < SIZE; i++) {
        result[i] = this->field[i] * multipler;
    }
    return result;
}

/********************************************************
* Przeciazenie operatora mnozenia macierzy przez wektor *
********************************************************/

template <class TYPE, int SIZE>
Vector<TYPE, SIZE> Matrix<TYPE, SIZE>::operator * (const Vector<TYPE, SIZE> & V) const {
    Vector<TYPE, SIZE> result;

    for(int i = 0; i < DIMENSION; i++) {
        result[i] = this->field[i] * V;
    }
    return result;
}

/****************************************************
* Przeciazenie operatora mnozenia dwoch macierzy    *
****************************************************/

template <class TYPE, int SIZE>
Matrix<TYPE, SIZE> Matrix<TYPE, SIZE>::operator * (const Matrix<TYPE, SIZE> & M2) const {
    Matrix result;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            result[i][j] = this->field[i] * M2.take_column(j);
        }
    }
    return result;
}

/************************************************************
* Przeciazenie operatora do wczytania macierzy z wejscia    *
************************************************************/

template <class TYPE, int SIZE>
istream & operator >> (istream & str, Matrix<TYPE, SIZE> & M) {
    for(int i = 0; i < SIZE; i++) {
        str >> M[i];        // wczytujemy M[i] w petli czyli tak na prawde wczytujemy po kolei wektory, z ktorych sklada sie dana macierz
    }
    return str;
}

/****************************************************************
* Przeciazenie operatora do wyswietlenia macierzy na wyjscie    *
****************************************************************/

template <class TYPE, int SIZE>
ostream & operator << (ostream & str, const Matrix<TYPE, SIZE> & M) {
    string vec;     // przechowujemy w nim elementy wektorow, z ktorych sklada sie macierz
    int str_len[SIZE];     // tablica przechowujaca informacje o "szerokosci" kazdej liczby w wierszu macierzy
    int max_len[SIZE] = {0, 0, 0};     // tablica przechowujaca informacje o maksymalnej "szerokosci" kazdej kolumny w macierzy
    ostringstream ss;       // objekt do operowania stringami

    for(int i = 0; i < SIZE; i++) {
        for(int k = 0; k < SIZE; k++) {
            ss << M[i][k];      // dodajemy liczbe double do zawartosci strumienia
            vec = ss.str();     // do naszego stringa przypisujemy zwracanego stringa z aktualna zawartoscia strumienia, uzywajac funkcji to_string gdy pobieralem double, np double x=6;,
                                // do stringa zapisywala sie liczba 6.000000 przez co "dlugosc" liczby byla nieprawidlowa, znalazlem w internecie rozwiazanie z klasa ostringstream i biblioteka sstream
            ss.str("");         // resetujemy zawartosc strumienia
            ss.clear();
            str_len[k] = vec.size();        // pobieramy dlugosc kazdej liczby w macierzy
            if(str_len[k] > max_len[k]) {
                max_len[k] = str_len[k];        // znajdujemy "najszersza" kolumne w macierzy, wzgledem tej szerokosci bedziemy wstawiac spacje, gdy wyswietlamy macierz
            }
        }
    }
    for(int i = 0; i < SIZE; i++) {        // wyswietlamy macierz z odpowiednimi odstepami, liczba pod liczba
        str << "|";
        for(int j = 0; j < SIZE; j++) {
            str << ' ' << setw(max_len[j]) << M[i][j] << ' ';
        }
        str << "|" << endl;
    }
    return str;
}

/****************************************************************
* Przeciazenie operatora do wyswietlenia macierzy na wyjscie    *
****************************************************************/

template <>
ostream & operator << (ostream & str, const Matrix<Complex, DIMENSION> & M) {
    string vec;     // przechowujemy w nim elementy wektorow, z ktorych sklada sie macierz
    int str_len[DIMENSION];     // tablica przechowujaca informacje o "szerokosci" kazdej liczby w wierszu macierzy
    int max_len[DIMENSION] = {0, 0, 0};     // tablica przechowujaca informacje o maksymalnej "szerokosci" kazdej kolumny w macierzy
    ostringstream ss;       // objekt do operowania stringami

    for(int i = 0; i < DIMENSION; i++) {
        for(int k = 0; k < DIMENSION; k++) {
            ss << M[i][k];      // dodajemy liczbe double do zawartosci strumienia
            vec = ss.str();     // do naszego stringa przypisujemy zwracanego stringa z aktualna zawartoscia strumienia, uzywajac funkcji to_string gdy pobieralem double, np double x=6;,
                                // do stringa zapisywala sie liczba 6.000000 przez co "dlugosc" liczby byla nieprawidlowa, znalazlem w internecie rozwiazanie z klasa ostringstream i biblioteka sstream
            ss.str("");         // resetujemy zawartosc strumienia
            ss.clear();
            str_len[k] = vec.size();        // pobieramy dlugosc kazdej liczby w macierzy
            if(str_len[k] > max_len[k]) {
                max_len[k] = str_len[k];        // znajdujemy "najszersza" kolumne w macierzy, wzgledem tej szerokosci bedziemy wstawiac spacje, gdy wyswietlamy macierz
            }
        }
    }
    for(int i = 0; i < DIMENSION; i++) {        // wyswietlamy macierz z odpowiednimi odstepami, liczba pod liczba
        str << "|";
        for(int j = 0; j < DIMENSION; j++) {
            ss << M[i][j];
            vec = ss.str();
            ss.str("");
            ss.clear();
            str_len[j] = vec.size();

            str << ' ' << setw(max_len[j] - str_len[j] + 1) << M[i][j] << ' ';
        }
        str << "|" << endl;
    }
    return str;
}















