
#if defined(HAVE_FFTW_FFT)

#undef  HAVE_FFTW3_FFT
#undef  HAVE_DXML_FFT
#undef  HAVE_MLIB_FFT

#include <fourier.h>
#include <bench.h>

namespace fftw2 {
#include <fourier-bench2-utils.h>
}

#else

#include <iostream>

namespace fftw2 {
  void run(int n, bool verbose)
  {
    std::cout << "FFTW port not available." << std::endl << std::endl;
  }
}

#endif

