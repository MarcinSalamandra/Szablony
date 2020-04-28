#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

// szablon klasy macierzy
template <class TYPE, int SIZE>
class Matrix {
    Vector<TYPE, SIZE> field[SIZE];

    public:
        Matrix();
        Matrix(Vector<TYPE, SIZE> elem[]);

        const Vector<TYPE, SIZE> & operator [] (int index) const;
        Vector<TYPE, SIZE> & operator [] (int index);

        Matrix invert() const;
        Matrix make_unit();
        void swap_rows(int index1, int index2);
        TYPE determinant() const;

        Matrix transposition() const;
        Vector<TYPE, SIZE> take_column(int index) const;

        Matrix operator + (const Matrix & M2) const;
        Matrix operator - (const Matrix & M2) const;
        Matrix operator * (const Matrix & M2) const;
        Matrix operator * (const TYPE & multipler) const;
        Vector<TYPE, SIZE> operator * (const Vector<TYPE, SIZE> & V) const;
};

// przeciazenia operatorow strumieni wejscia / wyjscia dla macierzy

template <class TYPE, int SIZE>
ostream & operator << (ostream & str, const Matrix<TYPE, SIZE> & M);

template <class TYPE, int SIZE>
istream & operator >> (istream & str, Matrix<TYPE, SIZE> & M);


#endif
