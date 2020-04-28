#include "equation.cpp"

template class Equation<double, DIMENSION>;

template ostream & operator << (ostream & str, const Equation<double, DIMENSION> & E);

template istream & operator >> (istream & str, Equation<double, DIMENSION> & E);

template class Equation<Complex, DIMENSION>;

template ostream & operator << (ostream & str, const Equation<Complex, DIMENSION> & E);

template istream & operator >> (istream & str, Equation<Complex, DIMENSION> & E);
