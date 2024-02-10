
#include "fourier-bench1.h"

#ifdef HAVE_FFTW3_FFT

namespace fftw3 {

#include <fftw3.h>

  fftw_plan p;

  namespace r2c {

    double *in;
    complex<double> *out;

    struct otest : bench::Test {
      explicit otest(int n)
      {
        bench::init(in, n, out, n/2+1);
        p = fftw_plan_dft_r2c_1d(n, reinterpret_cast<double*>(in),
                                 reinterpret_cast<fftw_complex*>(out), FFTW_MEASURE);
        bench::header("FFTW3", "r2c", "o", "f", n);
      }
      ~otest()
      {
        fftw_destroy_plan(p);
        bench::free(in, out);
      }
      void op()
      {
        fftw_execute(p);
      };
      string opName() const
      {
        return "fftw_execute()";
      }
    };

    struct itest : bench::Test {
      explicit itest(int n)
      {
        bench::init(in, 2*(n/2+1));
        p = fftw_plan_dft_r2c_1d(n, reinterpret_cast<double*>(in),
                                 reinterpret_cast<fftw_complex*>(in), FFTW_MEASURE);
        bench::header("FFTW3", "r2c", "i", "f", n);
      }
      ~itest()
      {
        fftw_destroy_plan(p);
        bench::free(in);
      }
      void op()
      {
        fftw_execute(p);
      };
      string opName() const
      {
        return "fftw_execute()";
      }
    };
  }

  namespace r2r {
    double *in, *out;
    struct otest : bench::Test {
      explicit otest(int n)
      {
        bench::init(in, n, out, n);
        p = fftw_plan_r2r_1d(n, reinterpret_cast<double*>(in),
                             reinterpret_cast<double*>(out), FFTW_R2HC, FFTW_MEASURE);
        bench::header("FFTW3", "r2r", "o", "f", n);
      }
      ~otest()
      {
        fftw_destroy_plan(p);
        bench::free(in, out);
      }
      void op()
      {
        fftw_execute(p);
      };
      string opName() const
      {
        return "fftw_execute()";
      }
    };

    struct itest : bench::Test {
      explicit itest(int n)
      {
        bench::init(in, n);
        p = fftw_plan_r2r_1d(n, reinterpret_cast<double*>(in),
                             reinterpret_cast<double*>(in), FFTW_R2HC, FFTW_MEASURE);
        bench::header("FFTW3","r2r","i","f",n);
      }
      ~itest()
      {
        fftw_destroy_plan(p);
        bench::free(in);
      }
      void op()
      {
        fftw_execute(p);
      };
      string opName() const
      {
        return "fftw_execute()";
      }
    };
  }

  namespace c2c {
    complex<double> *in, *out;
    struct otest : bench::Test {
      explicit otest(int n)
      {
        bench::init(in, n, out, n);
        p = fftw_plan_dft_1d(n, reinterpret_cast<fftw_complex*>(in),
                             reinterpret_cast<fftw_complex*>(out), FFTW_FORWARD, FFTW_MEASURE);
        bench::header("FFTW3", "c2c", "o", "f", n);
      }
      ~otest()
      {
        fftw_destroy_plan(p);
        bench::free(in, out);
      }
      void op()
      {
        fftw_execute(p);
      };
      string opName() const
      {
        return "fftw_execute()";
      }
    };

    struct itest : bench::Test {
      explicit itest(int n)
      {
        bench::init(in, n);
        p = fftw_plan_dft_1d(n, reinterpret_cast<fftw_complex*>(in),
                             reinterpret_cast<fftw_complex*>(in), FFTW_FORWARD, FFTW_MEASURE);
        bench::header("FFTW3", "c2c", "i", "f", n);
      }
      ~itest()
      {
        fftw_destroy_plan(p);
        bench::free(in);
      }
      void op()
      {
        fftw_execute(p);
      };
      string opName() const
      {
        return "fftw_execute()";
      }
    };
  }



  void run(int n, bool verbose)
  {
    // bench namespace verbose locally scoped
    //bench::verbose = true;

    fftw_import_system_wisdom();
    {
      r2c::otest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      r2c::itest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      r2r::otest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      r2r::itest test(n);
      bench::bench(test, n, 0.5, verbose);
    }
    {
      c2c::itest test(n);
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

namespace fftw3 {
  void run(int n, bool verbose)
  {
    cout << "FFTW3 port not available." << endl << endl;
  }
}

#endif // HAVE_FFTW3_FFT

