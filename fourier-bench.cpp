

#include <cstdlib>
#include <iostream>

namespace fftw {
  void run(int n, bool verbose);
}

namespace fftw3 {
  void run(int n, bool verbose);
}

namespace dxml {
  void run(int n, bool verbose);
}

namespace mlib {
  void run(int n, bool verbose);
}

int main(int nargs, char *args[])
{
  int n=4096;
  if (nargs == 2)
    n = atoi(args[1]);

  bool verbose = false;

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(0);

#ifdef HAVE_FFTW_FFT
  fftw::run(n, verbose);
#endif

#ifdef HAVE_FFTW3_FFT
  fftw3::run(n, verbose);
#endif

#ifdef HAVE_DXML_FFT
  dxml::run(n, verbose);
#endif

#ifdef HAVE_MLIB_FFT
  mlib::run(n, verbose);
#endif

  return 0;
}
