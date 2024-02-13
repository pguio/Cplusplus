
#include <iostream>
#include <cmath>
#include <bench.h>

using std::string;

const double PI = 3.14159265358979323846;

// Calculate sin(x) using j terms
double sine(double x, int j)
{
  double val = 1.0;
  for (int k = j-1; k>= 0; --k)
    val= 1 -x*x/(2*k+2)/(2*k+3)*val;

  return x*val;
}

// Compute J terms in the series expansion.K is the loop variable.
template<int N, int I, int J, int K>
class SineSeries {
public:
  enum { go = (K+1 != J) };
  static double accumulate()
  {
    return 1.0 - (I*2*PI/N)*(I*2*PI/N)/(2*K+2)/(2*K+3)*
           SineSeries<N*go, I*go, J*go, (K+1)*go>::accumulate();
  }
};

// Specialisation to terminate loop
template <>
class SineSeries<0, 0, 0, 0> {
public:
  static double accumulate()
  {
    return 1.0;
  }
};

template<int N, int I>
class Sine {
public:
  static double sin()
  {
    return (I*2*PI/N)*SineSeries<N,I,10,0>::accumulate();
  }
};

typedef Sine<32,5> et;

struct test1 : bench::Test {
  void op()
  {
    et::sin();
  }
  string opName() const
  {
    return "Sine<32,5>::sin()       ";
  }
};

struct test2 : bench::Test {
  void op()
  {
    sine(2.0*PI*5.0/32.0,10);
  }
  string opName() const
  {
    return "sine(2.0*PI*5.0/32.0,10)";
  }
};

struct test3 : bench::Test {
  void op()
  {
    sin(2.0*PI*5.0/32.0);
  }
  string opName() const
  {
    return "sin(2.0*PI*5.0/32.0)    ";
  }
};


int main()
{
  std::cout << std::setprecision(10)
            << "Sine<32,5>::sin()        = " << et::sin() << std::endl
            << "sine(2.0*PI*5.0/32.0,10) = " << sine(2.0*PI*5.0/32.0,10) << std::endl
            << "sin(2.0*PI*5.0/32.0)     = " << sin(2.0*PI*5.0/32.0) << std::endl;

  test1 t1;
  bench::benchClassOp(t1, 1e-3, 100);
  test2 t2;
  bench::benchClassOp(t2, 1e-3, 100);
  test3 t3;
  bench::benchClassOp(t3, 1e-3, 100);

  return 0;
}
