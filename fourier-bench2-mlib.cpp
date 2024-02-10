
#if defined(HAVE_MLIB_FFT)

#undef  HAVE_FFTW_FFT
#undef  HAVE_FFTW3_FFT
#undef  HAVE_DXML_FFT

#include <fourier.h>
#include <bench.h>

namespace mlib {
#include <fourier-bench2-utils.h>
}

#else

#include <iostream>

namespace mlib {
  void run(int n, bool verbose)
  {
    std::cout << "MLIB port not available." << std::endl << std::endl;
  }
}

#endif

