#ifndef LZESPOLONA_H
#define LZESPOLONA_H

#include <iostream>

using std::ostream;
using std::istream;

const double eps = 0.000001;       // stala, wzgledem ktorej okreslamy, czy liczba to 0

// klasa liczby zespolonej
class Complex {
    double im, re;

    public:
        Complex();
        Complex(double reality, double imaginary);

        void set_re(const double & reality);
        void set_im(const double & imaginary);
        const double & get_re() const;
        const double & get_im() const;

        Complex operator + (const Complex & Cn2) const;
        void operator += (const Complex & Cn2);
        Complex operator - (const Complex & Cn2) const;
        Complex operator * (const Complex & Cn2) const;
        Complex operator * (const double & multipler) const;
        Complex operator / (const Complex & Cn2) const;
        Complex operator / (const double & bottom) const;

        bool operator == (const Complex & Cn2) const;
        bool operator != (const Complex & Cn2) const;

        Complex coupling() const;
        double module() const;
};

// przeciazenia operatorow strumieni wejscia / wyjscia dla liczby zespolonej
istream & operator >> (istream & str, Complex & in);
ostream & operator << (ostream & str, Complex out);

#endif

