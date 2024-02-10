
#include "fourier-bench1.h"

#ifdef HAVE_DXML_FFT

namespace dxml {

#include <dxmldef.h>

  int stride = 1;
  int status;

  namespace r2r {
    DXML_D_FFT_STRUCTURE fft_struct;
    double *in, *out;

    struct otest : bench::Test {
      otest(int n)
      {
        bench::init(in, n, out, n);
        status = dfft_init(&n, &fft_struct, &stride);
        bench::header("DXML", "r2r", "o", "f", n);
      }
      ~otest()
      {
        dfft_exit(&fft_struct);
        bench::free(in, out);
      }
      void op()
      {
        status = dfft_apply("real", "real", "f", in, out, &fft_struct, &stride);
      };
      string opName() const
      {
        return "dfft_apply";
      }
    };
  }

  namespace c2c {
    DXML_Z_FFT_STRUCTURE fft_struct;
    complex<double> *in, *out;

    struct otest : bench::Test {
      otest(int n)
      {
        bench::init(in, n, out, n);
        status = zfft_init(&n, &fft_struct, &stride);
        bench::header("DXML", "c2c", "o", "f", n);
      }
      ~otest()
      {
        zfft_exit(&fft_struct);
        bench::free(in, out);
      }
      void op()
      {
        zfft_apply("complex", "complex", "f", in, out, &fft_struct, &stride);
      };
      string opName() const
      {
        return "zfft_apply";
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
      c2c::otest test(n);
      bench::bench(test, n, 1.0, verbose);
    }
    cout << endl;
  }
}

#else

namespace dxml {
  void run(int n, bool verbose)
  {
    cout << "DXML port not available." << endl << endl;
  }
}

#endif // HAVE_DXML_FFT

