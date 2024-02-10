
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>

using std::cout;
using std::endl;

using std::complex;
using std::string;

#include <bench.h>

#define FFT_BENCH(fft,name,n,weight)                                \
{                                                                   \
using namespace bench;                                              \
using namespace timeutils;                                          \
double t;                                                           \
BENCH(fft,name,4.0,t)                                               \
if (verbose)                                                        \
cout << " (" << smartTime(t/n) << "/point)\n"                       \
<< "\"mflops\" = 5 (n log2 n) / (t in microseconds) = "             \
<< weight*5.0*n*log(static_cast<double>(n))/(log(2.0)*1e6*t)        \
<< '\n' << endl;                                                    \
else                                                                \
cout << std::setw(10)                                               \
<< weight*5.0*n*log(static_cast<double>(n))/(log(2.0)*1e6*t)        \
<< " mflops" << endl;                                               \
}                                                                   \

namespace bench {

  template <class Test>
  double bench(const Test & test, int & n, double weight)
  {
    double t = benchClassOp(test, 4.0);
    if (verbose) {
      cout << " (" << timeutils::smartTime(t/n) << "/point)\n"
           << "\"mflops\" = 5 (n log2 n) / (t in microseconds) = "
           << weight*5.0*n*log(static_cast<double>(n))/(log(2.0)*1e6*t)
           << '\n' << endl;
    }
    else {
      cout << std::setw(10)
           << weight*5.0*n*log(static_cast<double>(n))/(log(2.0)*1e6*t)
           << " mflops" << endl;
    }
    return t;
  }

  template <class T1, class T2>
  void init(T1 * & in, T2 * & out, int size)
  {
    in  = new T1[size];
    out = new T2[size];
    for (int i=0; i<size; ++i) {
      in[i] = T1(0.0);
      out[i] = T2(0.0);
    }
  }

  template <class T1, class T2>
  void free(T1 *in, T2 *out)
  {
    delete[] in;
    delete[] out;
  }

  void inline header(const string &source,
                     const string &type,
                     const string &inplace,
                     const string &direction,
                     int n)
  {
    if (verbose)
      cout << source << ": " << type << inplace << direction << n << endl;
    else
      cout << source << ": " << type << inplace << direction << n << ":";
  }
}


