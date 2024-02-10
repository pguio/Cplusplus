#include <unsupported/Eigen/CXX11/Tensor>
//#include <bench/BenchTimer.h>
#include <BenchTimer.h>
#include <blitz/array.h>

using namespace Eigen;

typedef Tensor<float, 1>::DimensionPair DimPair;

EIGEN_DONT_INLINE
double constraction_eigen() {
  Tensor<float, 4> t1(30, 50, 80, 31);
  Tensor<float, 5> t2(80, 31, 16, 20, 10);
  Tensor<float, 5> res(30, 50, 16, 20, 10);

  t1.setRandom();
  t2.setRandom();

  Eigen::array<DimPair, 2> dims({{DimPair(2, 0), DimPair(3, 1)}});

  BenchTimer t;
  t.start();
  res = t1.contract(t2, dims);
  t.stop();
  return t.best();
}

EIGEN_DONT_INLINE
double constraction_blitz() {
  blitz::Array<float, 4> t1(30, 50, 80, 31);
  blitz::Array<float, 5> t2(80, 31, 16, 20, 10);
  blitz::Array<float, 5> res(30, 50, 16, 20, 10);

  blitz::firstIndex   i0;
  blitz::secondIndex  i1;
  blitz::thirdIndex   i2;
  blitz::fourthIndex  i3;
  blitz::fifthIndex   i4;
  blitz::sixthIndex   j0;
  blitz::seventhIndex j1;

  BenchTimer t;
  t.start();
  res = sum(sum(t1(i0,i1,j0,j1) * t2(j0,j1,i2,i3,i4), j0), j1);
  t.stop();
  return t.best();
}

int main() {
  std::cout << constraction_eigen() << "s\n";
  std::cout << constraction_blitz() << "s\n";
}
