
#include "fourier-bench1.h"

#ifdef HAVE_MLIB_FFT

namespace mlib {

#include <veclib.h>

  double *work;
  int iopt;
  int ier;

  namespace r2r {
    double *in;

    struct itest : bench::Test {
      itest(int n)
      {
        bench::init(in, n);
        work = new double[2*n];
        iopt = -3;
        drc1ft(in, &n, work, &iopt, &ier);
        bench::header("MLIB", "r2r", "i", "f", n);
        iopt = 1;
      }
      ~itest()
      {
        delete[] work;
        bench::free(in);
      }
      void op()
      {
        drc1ft(in,&n,work,&iopt,&ier);
      };
      string opName() const
      {
        return "drc1ft()";
      }
    };
  }

  namespace c2c {
    complex<double> *in;

    struct itest : bench::Test {
      itest(int n)
      {
        bench::init(in, n);
        work = new double[(5*n)/2];
        iopt = -3;
        z1dfft(reinterpret_cast<complex16_t*>(in), &n, work, &iopt, &ier);
        bench::header("MLIB", "c2c", "i", "f", n);
        iopt = 1;
      }
      ~itest()
      {
        delete[] work;
        bench::free(in);
      }
      void op()
      {
        z1dfft(reinterpret_cast<complex16_t*>(in), &n, work, &iopt, &ier);
      };
      string opName() const
      {
        return "z1dfft()";
      }
    };
  }

  void run(int n, int verbose)
  {
    // bench namespace verbose locally scoped
    //bench::verbose = true;

    {
      r2r::itest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      c2c::itest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    cout << endl;
  }
}

#else

namespace mlib {
  void run(int n, bool verbose)
  {
    cout << "MLIB port not available." << endl << endl;
  }
}

#endif


