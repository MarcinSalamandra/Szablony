#include "vector.cpp"

template class Vector<double, DIMENSION>;

template ostream & operator << (ostream & str, const Vector<double, DIMENSION> & V);

template istream & operator >> (istream & str, Vector<double, DIMENSION> & V);

template class Vector<Complex, DIMENSION>;

template ostream & operator << (ostream & str, const Vector<Complex, DIMENSION> & V);

template istream & operator >> (istream & str, Vector<Complex, DIMENSION> & V);
