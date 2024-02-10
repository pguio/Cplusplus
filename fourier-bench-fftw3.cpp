

#ifdef HAVE_FFTW3_FFT

#include "fourier-bench.h"

namespace fftw3 {


#include <fftw3.h>

  void run(int n, bool verbose)
  {
    // bench namespace verbose locally scoped
    //bench::verbose = true;

    fftw_import_system_wisdom();
    {
      double *in=0;
      complex<double> *out=0;
      bench::init(in,out,2*(n/2+1));
      fftw_plan plan;
      int flags = FFTW_MEASURE;
      plan = fftw_plan_dft_r2c_1d(n,
                                  reinterpret_cast<double *>(in),
                                  reinterpret_cast<fftw_complex*>(out),
                                  flags);
      bench::header("FFTW3","r2c","o","f",n);
      FFT_BENCH(fftw_execute(plan);,"fftw_execute", n, 0.5)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    {
      double *in=0;
      complex<double> *out=0;
      bench::init(in,out,2*(n/2+1));
      fftw_plan plan;
      int flags = FFTW_MEASURE;
      plan = fftw_plan_dft_r2c_1d(n,
                                  reinterpret_cast<double*>(in),
                                  reinterpret_cast<fftw_complex*>(in),
                                  flags);
      bench::header("FFTW3","r2c","i","f",n);
      FFT_BENCH(fftw_execute(plan);,"fftw_execute", n, 0.5)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    {
      double *in=0, *out=0;
      bench::init(in,out,2*(n/2+1));
      fftw_plan plan;
      int flags = FFTW_MEASURE;
      plan = fftw_plan_r2r_1d(n,
                              reinterpret_cast<double*>(in),
                              reinterpret_cast<double*>(out),
                              FFTW_R2HC, flags);
      bench::header("FFTW3","r2r","o","f",n);
      FFT_BENCH(fftw_execute(plan);,"fftw_execute", n, 0.5)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    {
      double *in=0, *out=0;
      bench::init(in,out,2*(n/2+1));
      fftw_plan plan;
      int flags = FFTW_MEASURE;
      plan = fftw_plan_r2r_1d(n,
                              reinterpret_cast<double*>(in),
                              reinterpret_cast<double*>(in),
                              FFTW_R2HC, flags);
      bench::header("FFTW3","r2r","i","f",n);
      FFT_BENCH(fftw_execute(plan);,"fftw_execute", n, 0.5)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    {
      complex<double> *in=0, *out=0;
      bench::init(in,out,n);
      fftw_plan plan;
      int flags = FFTW_MEASURE;
      plan = fftw_plan_dft_1d(n,
                              reinterpret_cast<fftw_complex*>(in),
                              reinterpret_cast<fftw_complex*>(out),
                              FFTW_FORWARD, flags);
      bench::header("FFTW3","c2c","o","f",n);
      FFT_BENCH(fftw_execute(plan);,"fftw_execute", n, 1)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    {
      complex<double> *in=0, *out=0;
      bench::init(in,out,n);
      fftw_plan plan;
      int flags = FFTW_MEASURE;
      plan = fftw_plan_dft_1d(n,
                              reinterpret_cast<fftw_complex*>(in),
                              reinterpret_cast<fftw_complex*>(in),
                              FFTW_FORWARD, flags);
      bench::header("FFTW3","c2c","i","f",n);
      FFT_BENCH(fftw_execute(plan);, "fftw_execute", n, 1)
#if 1
      fftw_destroy_plan(plan);
#endif

      bench::free(in,out);
    }
    cout << endl;
  }
}

#endif

