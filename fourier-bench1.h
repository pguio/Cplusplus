
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <memory>
#include <bench.h>

using std::complex;
using std::cout;
using std::endl;
using std::setw;
using std::string;


namespace bench {

  template <class Test>
  double bench(Test & test, int & n, double weight, bool verbose)
  {
    double t = benchClassOp(test, 4.0);
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

  template <class T1>
  void init(T1 * & in, int ni)
  {
    in  = new T1[ni];
    for (int i=0; i<ni; ++i) in[i]   = T1(0.0);
  }

  template <class T1>
  void free(T1 *in)
  {
    delete[] in;
  }

  template <class T1, class T2>
  void init(T1 * & in, int ni, T2 * & out, int no)
  {
    in  = new T1[ni];
    out = new T2[no];
    for (int i=0; i<ni; ++i) in[i]   = T1(0.0);
    for (int i=0; i<no; ++i) out[i]  = T2(0.0);
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




