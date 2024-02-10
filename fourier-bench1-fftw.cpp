
#include "fourier-bench1.h"

#ifdef HAVE_FFTW_FFT

namespace fftw {

#include <fftw.h>
#include <rfftw.h>

  namespace r2r {
    rfftw_plan p;
    double *in, *out;

    struct otest : bench::Test {
      otest(int n)
      {
        bench::init(in, n, out, n);
        p = rfftw_create_plan(n, FFTW_FORWARD, FFTW_MEASURE | FFTW_OUT_OF_PLACE);
        bench::header("FFTW2", "r2r", "o", "f", n);
      }
      ~otest()
      {
        rfftw_destroy_plan(p);
        bench::free(in, out);
      }
      void op()
      {
        rfftw_one(p, reinterpret_cast<fftw_real*>(in), reinterpret_cast<fftw_real*>(out));
      };
      string opName() const
      {
        return "rfftw_one()";
      }
    };

    struct itest : bench::Test {
      itest(int n)
      {
        bench::init(in, n);
        p = rfftw_create_plan(n, FFTW_FORWARD, FFTW_MEASURE | FFTW_IN_PLACE);
        bench::header("FFTW2", "r2r", "i", "f", n);
      }
      ~itest()
      {
        rfftw_destroy_plan(p);
        bench::free(in);
      }
      void op()
      {
        rfftw_one(p, reinterpret_cast<fftw_real*>(in), 0);
      };
      string opName() const
      {
        return "rfftw_one()";
      }
    };
  }

  namespace c2c {
    fftw_plan p;
    complex<double> *in, *out;

    struct otest : bench::Test {
      otest(int n)
      {
        bench::init(in, n, out, n);
        p = fftw_create_plan(n, FFTW_FORWARD, FFTW_MEASURE | FFTW_OUT_OF_PLACE);
        bench::header("FFTW2", "c2c", "o", "f", n);
      }
      ~otest()
      {
        fftw_destroy_plan(p);
        bench::free(in, out);
      }
      void op()
      {
        fftw_one(p, reinterpret_cast<fftw_complex*>(in), reinterpret_cast<fftw_complex*>(out));
      };
      string opName() const
      {
        return "fftw_one()";
      }
    };

    struct itest : bench::Test {
      itest(int n)
      {
        bench::init(in, n);
        p = fftw_create_plan(n, FFTW_FORWARD, FFTW_MEASURE | FFTW_IN_PLACE);
        bench::header("FFTW2", "c2c", "i", "f",n);
      }
      ~itest()
      {
        fftw_destroy_plan(p);
        bench::free(in);
      }
      void op()
      {
        fftw_one(p, reinterpret_cast<fftw_complex*>(in), 0);
      };
      string opName() const
      {
        return "fftw_one()";
      }
    };
  }

  void run(int n, bool verbose)
  {

    // bench namespace verbose locally scoped
    //bench::verbose = true;

    {
      r2r::otest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      r2r::itest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      c2c::otest test(n);
      bench::bench(test, n, 1.0, verbose);
    }
    {
      c2c::itest test(n);
      bench::bench(test, n, 1.0, verbose);
    }
    cout << endl;
  }
}

#else

namespace fftw {
  void run(int n, bool verbose)
  {
    cout << "FFTW2 port not available." << endl << endl;
  }
}

#endif // HAVE_FFTW_FFT

