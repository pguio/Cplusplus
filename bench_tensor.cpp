
#if defined(HAVE_EIGEN)
#include <unsupported/Eigen/CXX11/Tensor>
//#include <bench/BenchTimer.h>
#include <BenchTimer.h>
#if defined(HAVE_BLITZ)
#include <blitz/array.h>
#endif
#endif

// from /usr/include/eigen3/Eigen/src/Core/util/Macros.h
#define EIGEN_DONT_INLINE __attribute__((noinline))

// from https://sourceforge.net/p/blitz/mailman/blitz-devel/ 
// Post by Gael Guennebaud <gael.guennebaud@gmail.com> on Blitz-devel 20/01/16
// https://sourceforge.net/p/blitz/mailman/blitz-devel/?viewmonth=201601&viewday=20
// from https://sourceforge.net/p/blitz/mailman/attachment/CACgDPxPS1FMA43cjmuH5QkGAGKH7ZC73arZ%2BptCuGXTqitKHZQ%40mail.gmail.com/2/

#if defined(HAVE_EIGEN)
typedef Eigen::Tensor<float, 1>::DimensionPair DimPair;
EIGEN_DONT_INLINE
double constraction_eigen()
{
  Eigen::Tensor<float, 4> t1(30, 50, 80, 31);
  Eigen::Tensor<float, 5> t2(80, 31, 16, 20, 10);
  Eigen::Tensor<float, 5> res(30, 50, 16, 20, 10);

  t1.setRandom();
  t2.setRandom();

  Eigen::array<DimPair, 2> dims({{DimPair(2, 0), DimPair(3, 1)}});

  Eigen::BenchTimer t;
  t.start();
  res = t1.contract(t2, dims);
  t.stop();
  return t.best();
}
#endif

#if defined(HAVE_BLITZ)
EIGEN_DONT_INLINE
double constraction_blitz()
{
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

  Eigen::BenchTimer t;
  t.start();
  res = sum(sum(t1(i0,i1,j0,j1) * t2(j0,j1,i2,i3,i4), j0), j1);
  t.stop();
  return t.best();
}
#endif


int main()
{
#if defined(HAVE_EIGEN)
  std::cout << "Eigen " << constraction_eigen() << " s\n";
#if defined(HAVE_BLITZ)
  std::cout << "Blitz " << constraction_blitz() << " s\n";
#endif
#endif

  return 0;
}
