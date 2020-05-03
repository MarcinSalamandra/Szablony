#include "matrix.cpp"

template class Matrix<double, DIMENSION>;

template ostream & operator << (ostream & str, const Matrix<double, DIMENSION> & M);

template istream & operator >> (istream & str, Matrix<double, DIMENSION> & M);

template class Matrix<Complex, DIMENSION>;

template ostream & operator << (ostream & str, const Matrix<Complex, DIMENSION> & M);

template istream & operator >> (istream & str, Matrix<Complex, DIMENSION> & M);
