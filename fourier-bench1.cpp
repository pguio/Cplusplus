
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
  int n = (nargs == 2 ? atoi(args[1]) : 4096);

  bool verbose = false;

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(0);

  fftw::run(n, verbose);
  fftw3::run(n, verbose);
  dxml::run(n, verbose);
  mlib::run(n, verbose);

  return 0;
}


