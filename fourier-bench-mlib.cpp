


#ifdef HAVE_MLIB_FFT

#include "fourier-bench.h"

namespace mlib {

#include <veclib.h>

  void run(int n, bool verbose)
  {
    // bench namespace verbose locally scoped
    //bench::verbose = true;
    {
      double *in=0, *out=0;
      bench::init(in,out,n);
      int iopt=-3, ier;
      double *work = new double[2*n];
      drc1ft(in, &n, work, &iopt, &ier);
      bench::header("MLIB ","r2r","i","f",n);
      iopt = 1;
      FFT_BENCH(drc1ft(in,&n,work,&iopt,&ier);,
                "drc1ft", n, 0.5)
      bench::free(in,out);
      delete[] work;
    }
    {
      complex<double> *in=0, *out=0;
      bench::init(in,out,n);
      int iopt=-3, ier;
      double *work = new double[(5*n)>>1];
      z1dfft(reinterpret_cast<complex16_t*>(in), &n, work, &iopt, &ier);
      bench::header("MLIB ","c2c","i","f",n);
      iopt = 1;
      FFT_BENCH(z1dfft(reinterpret_cast<complex16_t*>(in),&n,work,&iopt, &ier);,
                "z1dfft", n, 1)
      bench::free(in,out);
      delete[] work;
    }
    cout << endl;
  }
}

#endif

