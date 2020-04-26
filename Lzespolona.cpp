#include <math.h>
#include "Lzespolona.h"

using std::endl;
using std::cerr;

/********************************
* Konstruktor bezparametryczny  *
********************************/

Complex::Complex() {
}

/****************************
* Konstruktor parametryczny *
****************************/

Complex::Complex(double reality, double imaginary) {
    re = reality;
    im = imaginary;
}

/************************************************
* Zmieniamy czesc rzeczywista liczby zespolonej *
************************************************/

void Complex::set_re(const double & reality) {
    this->re = reality;
}

/********************************************
* Zmieniamy czesc urojona liczby zespolonej *
********************************************/

void Complex::set_im(const double & imaginary) {
    this->im = imaginary;
}

/************************************************
* Pobieramy czesc rzeczywista liczby zespolonej *
************************************************/

const double & Complex::get_re() const {
    return this->re;
}

/********************************************
* Pobieramy czesc urojona liczby zespolonej *
********************************************/

const double & Complex::get_im() const {
    return this->im;
}

/************************************
* Przeciazenie operatora dodawania  *
************************************/

Complex Complex::operator + (const Complex & Cn2) const {
    Complex result;     // zwracany wynik dodawania

    // dodajemy do siebie czesci: rzeczywista i urojona
    result.re = this->re + Cn2.re;
    result.im = this->im + Cn2.im;

    return result;
}

/***************************************************
* Przeciazenie operatora dodawania z przypisaniem  *
***************************************************/

void Complex::operator += (const Complex & Cn2) {
    // dodajemy do siebie czesci: rzeczywista i urojona
    this->re += Cn2.re;
    this->im += Cn2.im;
}

/****************************************
* Przeciazenie operatora odejmowania    *
****************************************/

Complex Complex::operator - (const Complex & Cn2) const {
    Complex result;     // zwracany wynik odejmowania

    // odejmujemy od siebie czesci: rzeczywista i urojona
    result.re = this->re - Cn2.re;
    result.im = this->im - Cn2.im;

    return result;
}

/***************************************************************
* Przeciazenie operatora mnozenia zespolonej przez zespolona   *
***************************************************************/

Complex Complex::operator * (const Complex & Cn2) const {
    Complex result;     // zwracany wynik mnozenia

    // mnozymy odpowiednio
    result.re = this->re * Cn2.re - this->im * Cn2.im;
    result.im = this->re * Cn2.im + this->im * Cn2.re;

    return result;
}

/***********************************************************
* Przeciazenie operatora mnozenia zespolonej przez double  *
***********************************************************/

Complex Complex::operator * (const double & multipler) const {
    Complex result;

    result.re = this->re * multipler;
    result.im = this->im * multipler;

    return result;
}

/************************************************************
* Przeciazenie operatora dzielenia dwoch liczb zespolonychy *
************************************************************/

Complex Complex::operator / (const Complex & Cn2) const {
    Complex top;           // licznik w dzieleniu liczb zespolonych
    double bottom;         // mianownik w dzieleniu liczb zespolonych
    Complex result;        // zwracany wynik dzielenia
    top = *this;

    // obliczany jest licznik oraz mianownik
    top = top * Cn2.coupling();
    bottom = Cn2.module() * Cn2.module();

    result = top / bottom;

    return result;
}

/************************************************************************************
* Przeciazenie operatora dzielenia liczy zespolonej przez liczbe zmiennoprzecinkowa *
************************************************************************************/

Complex Complex::operator / (const double & bottom) const {
    Complex result;

    // sprawdzamy czy mianownik nie jest rowny zeru
    if(fabs(bottom) < eps) {
        cerr << "Blad: Dzielenie przez 0." << endl;
        exit(1);
    }
    result.re = this->re / bottom;
    result.im = this->im / bottom;

    return result;
}

/************************************************
* Funkcja liczaca sprzezenie liczby zespolonej  *
************************************************/

Complex Complex::coupling() const {
    Complex result;     // zwracany wynik sprzezenia

    // zmieniamy tylko czesc urojona
    result.re=this->re;
    result.im=-this->im;

    return result;
}

/********************************************
* Funkcja liczaca modul z liczby zespolonej *
********************************************/

double Complex::module() const {
    double result = sqrt(this->re * this->re + this->im * this->im);      // zwracany wynik nalozenia modulu na liczbe zespolona to liczba zmiennoprzecinkowa

    return result;
}

/************************************
* Przeciazenie operatora porownania *
************************************/

bool Complex::operator == (const Complex & Cn2) const {
    // sprawdzamy czy czesci urojone i rzeczywiste sa sobie rowne i zwracamy odpowiedni wynik - 0 lub 1
    if(fabs(this->re - Cn2.re) < eps && fabs(this->im - Cn2.im) < eps) {
        return true;
    }
    else {
        return false;
    }
}

/****************************************
* Przeciazenie operatora nierownosci    *
****************************************/

bool Complex::operator != (const Complex & Cn2) const {
    return !(*this == Cn2);
}

/********************************************
* Przeciazenie operatora strumienia wejscia *
********************************************/

istream & operator >> (istream & str, Complex & in) {
    char character;     // znak dzialania
    double reality, imaginary;

    str >> character;         // pobieramy znak i sprawdzamy czy to otworzenie nawiasu
    if(character != '(') {
        str.setstate(std::ios::failbit);
    }
    str >> reality;             // pobieramy czesc rzeczywista i urojona liczby zespolonej
    str >> imaginary;
    str >> character;         // pobieramy znak i sprawdzamy czy to litera 'i'
    if(character != 'i') {
        str.setstate(std::ios::failbit);
    }
    str >> character;         // pobieramy znak i sprawdzamy czy to domkniecie nawiasu
    if(character != ')') {
        str.setstate(std::ios::failbit);
    }
    in.set_im(imaginary);
    in.set_re(reality);

    return str;
}

/********************************************************************
* Przeciazenie operatora strumienia wyjscia dla liczby zespolonej   *
********************************************************************/

ostream & operator << (ostream & str, Complex out) {
    str << '(';
    if(fabs(out.get_re()) >= eps) {
        str << out.get_re();
    }
    if(fabs(out.get_im()) >= eps) {
        if(fabs(out.get_re()) >= eps) {
            if(out.get_im() == 1) {
                str << "+i";
            }
            else if(out.get_im() == -1) {
                str << "-i";
            }
            else {
                str << std::showpos << out.get_im() << std::noshowpos << 'i';
            }
        }
        else {
            if(out.get_im() == 1) {
                str << 'i';
            }
            else if(out.get_im() == -1) {
                str << "-i";
            }
            else {
                str << out.get_im() << 'i';
            }
        }
    }
    if(fabs(out.get_re()) < eps && fabs(out.get_im()) < eps) {
        str << 0;
    }
    str << ')';

    return str;
}






