

#ifdef HAVE_FFTW_FFT

#include "fourier-bench.h"

namespace fftw {

#include <fftw.h>
#include <rfftw.h>

  void run(int n, bool verbose)
  {
    // bench namespace verbose locally scoped
    //bench::verbose = true;

    {
      double *in=0, *out=0;
      bench::init(in,out,n);
      rfftw_plan plan;
      int flags = FFTW_MEASURE | FFTW_OUT_OF_PLACE;
      plan = rfftw_create_plan(n, FFTW_FORWARD, flags);
      bench::header("FFTW2","r2r","o","f",n);
      FFT_BENCH(rfftw_one(plan, reinterpret_cast<fftw_real*>(in),
                          reinterpret_cast<fftw_real*>(out));,
                "rfftw_one", n, 0.5)
      rfftw_destroy_plan(plan);
      bench::free(in,out);
    }
    {
      double *in=0, *out=0;
      bench::init(in,out,n);
      rfftw_plan plan;
      int flags = FFTW_MEASURE | FFTW_IN_PLACE;
      plan = rfftw_create_plan(n, FFTW_FORWARD, flags);
      bench::header("FFTW2","r2r","i","f",n);
      FFT_BENCH(rfftw_one(plan, reinterpret_cast<fftw_real*>(in),0);,
                "rfftw_one", n, 0.5)
      rfftw_destroy_plan(plan);
      bench::free(in,out);
    }
    {
      complex<double> *in=0, *out=0;
      bench::init(in,out,n);
      fftw_plan plan;
      int flags = FFTW_MEASURE | FFTW_OUT_OF_PLACE;
      plan = fftw_create_plan(n, FFTW_FORWARD, flags);
      bench::header("FFTW2","c2c","o","f",n);
      FFT_BENCH(fftw_one(plan, reinterpret_cast<fftw_complex*>(in),
                         reinterpret_cast<fftw_complex*>(out));,
                "fftw_one", n, 1)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    {
      complex<double> *in=0, *out=0;
      bench::init(in,out,n);
      fftw_plan plan;
      int flags = FFTW_MEASURE | FFTW_IN_PLACE;
      plan = fftw_create_plan(n, FFTW_FORWARD, flags);
      bench::header("FFTW2","c2c","i","f",n);
      FFT_BENCH(fftw_one(plan, reinterpret_cast<fftw_complex*>(in),0);,
                "fftw_one", n, 1)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    cout << endl;
  }
}

#endif

