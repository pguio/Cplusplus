

#ifdef HAVE_DXML_FFT

#include "fourier-bench.h"

namespace dxml {

#include <dxmldef.h>

  void run(int n, bool verbose)
  {
    // bench namespace verbose locally scoped
    //bench::verbose = true;

    {
      double *in=0, *out=0;
      bench::init(in,out,n);
      int status, stride = 1;
      DXML_D_FFT_STRUCTURE fft_struct;
      status = dfft_init(&n, &fft_struct, &stride);
      bench::header("DXML ","r2r","o","f",n);
      FFT_BENCH(status=dfft_apply("real","real","f",in,out,&fft_struct,&stride);,
                "dfft_apply", n, 0.5)
      dfft_exit(&fft_struct);
      bench::free(in,out);
    }
    {
      complex<double> *in=0, *out=0;
      bench::init(in,out,n);
      int status, stride = 1;
      DXML_Z_FFT_STRUCTURE fft_struct;
      status = zfft_init(&n, &fft_struct, &stride);
      bench::header("DXML ","c2c","o","f",n);
      FFT_BENCH(
        status=zfft_apply("complex","complex","f",in,out,&fft_struct,&stride);,
        "zfft_apply", n, 1)
      zfft_exit(&fft_struct);
      bench::free(in,out);
    }
    cout << endl;
  }
}

#endif

