#ifndef EQUATION_H
#define EQUATION_H

#include "matrix.h"

// szablon klasy rownania macierzowego
template <class TYPE, int SIZE>
class Equation {
    Matrix<TYPE, SIZE> M;
    Vector<TYPE, SIZE> V;

    public:
        Equation();
        Equation(Matrix<TYPE, SIZE> Ma, Vector<TYPE, SIZE> Ve);

        const Matrix<TYPE, SIZE> & get_M() const;
        const Vector<TYPE, SIZE> & get_V() const;
        void set_M(const Matrix<TYPE, SIZE> & Ma);
        void set_V(const Vector<TYPE, SIZE> & Ve);

        Vector<TYPE, SIZE> calculate() const;
        Vector<TYPE, SIZE> fault() const;
};

// przeciazenia operatorow strumieni wejscia / wyjscia dla rownania macierzowego

template <class TYPE, int SIZE>
istream & operator >> (istream & str, Equation<TYPE, SIZE> & E);

template <class TYPE, int SIZE>
ostream & operator << (ostream & str, const Equation<TYPE, SIZE> & E);


#endif
