
#if defined(HAVE_DXML_FFT)

#undef  HAVE_FFTW_FFT
#undef  HAVE_FFTW3_FFT
#undef  HAVE_MLIB_FFT

#include <fourier.h>
#include <bench.h>

namespace dxml {
#include <fourier-bench2-utils.h>
}

#else

#include <iostream>

namespace dxml {
  void run(int n, bool verbose)
  {
    std::cout << "DXML port not available." << std::endl << std::endl;
  }
}

#endif

