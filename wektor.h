#ifndef WEKTOR_H
#define WEKTOR_H

#define DIMENSION 5

#include "Lzespolona.h"

// szablon klasy wektora
template <class TYPE, int SIZE>
class Vector {
    TYPE data[SIZE];

    public:
        Vector(TYPE elem[]);
        Vector();

        double length() const;

        TYPE operator * (const Vector & V2) const;
        Vector operator * (const double & multipler) const;
        Vector operator / (const double & divider) const;
        Vector operator + (const Vector & V2) const;
        Vector operator - (const Vector & V2) const;

        TYPE & operator [] (int index);
        const TYPE & operator [] (int index) const;
};

// przeciazenia operatorow strumieni wejscia / wyjscia dla wektora

template <class TYPE, int SIZE>
ostream & operator << (ostream & str, const Vector<TYPE, SIZE> & V);

template <class TYPE, int SIZE>
istream & operator >> (istream & str, Vector<TYPE, SIZE> & V);

#endif
