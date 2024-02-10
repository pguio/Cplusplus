

#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;

using std::fixed;
using std::setw;

double log2(double x)
{
  return log(x)/log(2.0);
}

// global verbose locally scoped
static bool verbose;

template <class FFT>
double benchFft(FFT & fft, int & n, double weight)
{
  double t = benchClassOp(fft, 4.0);

  cout << fft << " : " << fft.opName() << " : ";
  if (verbose) {
    cout << " (" << timeutils::smartTime(t/n) << "/point)\n"
         << "\"mflops\" = 5 (n log2 n) / (t in microseconds) = "
         << setw(10) << weight*5.0*n*log2(static_cast<double>(n))/(1e6*t)
         << '\n' << endl;
  }
  else {
    cout << setw(10) << weight*5.0*n*log2(static_cast<double>(n))/(1e6*t)
         << " mflops" << endl;
  }
  return t;
}

template <typename inType, typename outType>
struct otest : bench::Test, fourier::ODFT1D<inType,outType> {
  otest<inType, outType>(int n, int sign) : bench::Test(),
    fourier::ODFT1D<inType,outType>(n, sign),
    in(n), out(n)
  {
    in  = 0.0;
    out = 0.0;
  };
  ~otest() {}
  void op()
  {
    fourier::ODFT1D<inType,outType>::direct(in, out);
  }
  std::string opName() const
  {
    return "direct()";
  }
  typedef typename fourier::ODFT1D<inType,outType>::Array1di inArray;
  typedef typename fourier::ODFT1D<inType,outType>::Array1do outArray;
  inArray in;
  outArray out;
};

template <typename inType, typename outType>
struct itest : bench::Test, fourier::IDFT1D<inType,outType> {
  itest<inType, outType>(int n, int sign) : bench::Test(),
    fourier::IDFT1D<inType,outType>(n, sign), in(n)
  {
    in  = 0.0;
  };
  ~itest() {}
  void op()
  {
    fourier::IDFT1D<inType,outType>::direct(in);
  }
  std::string opName() const
  {
    return "direct()";
  }
  typedef typename fourier::IDFT1D<inType,outType>::Array1di inArray;
  inArray in;
};


void run(int n, bool mainVerbose)
{
  // global verbose locally scoped
  verbose = mainVerbose;

  // bench namespace verbose locally scoped
  //bench::verbose = true;

  {
    otest<double,double> test(n,-1);
    benchFft(test, n, 0.5);
  }
  {
    otest<double,double> test(n,1);
    benchFft(test, n, 0.5);
  }

  {
    itest<double,double> test(n,-1);
    benchFft(test, n, 0.5);
  }
  {
    itest<double,double> test(n,1);
    benchFft(test, n, 0.5);
  }

  {
    otest<fourier::complex,fourier::complex> test(n,-1);
    benchFft(test, n, 1);
  }
  {
    otest<fourier::complex,fourier::complex> test(n,1);
    benchFft(test, n, 1);
  }

  {
    itest<fourier::complex,fourier::complex> test(n,-1);
    benchFft(test, n, 1);
  }
  {
    itest<fourier::complex,fourier::complex> test(n,1);
    benchFft(test, n, 1);
  }

#if defined(HAVE_FFTW3_FFT)

  {
    otest<double,fourier::complex> test(n,-1);
    benchFft(test, n, 0.5);
  }
  {
    otest<double,fourier::complex> test(n,1);
    benchFft(test, n, 0.5);
  }

  {
    itest<double,fourier::complex> test(n,-1);
    benchFft(test, n, 0.5);
  }
  {
    itest<double,fourier::complex> test(n,1);
    benchFft(test, n, 0.5);
  }

#endif

  std::cout << std::endl;
}


