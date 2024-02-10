
#include <cmath>
#include <iostream>

#if defined(HAVE_DLFCN_H)

#include <dlfcn.h>


int main(int argc, char **argv)
{
  void *handle;
  double (*cosine)(double);
  const char *error;

  handle = dlopen ("libm.so", RTLD_LAZY);
  if (!handle) {
    std::cerr << dlerror() << std::endl;
    return !0;
  }

  cosine = (double (*)(double))dlsym(handle, "cos");
  if ((error = dlerror()))  {
    std::cerr << error << std::endl;
    return !0;
  }

  std::cout << "(*cosine)(2.0)=" << (*cosine)(2.0) << std::endl;
  std::cout << "cos(2.0)=" << cos(2.0) << std::endl;
  dlclose(handle);
  return 0;
}

#else

int main()
{
  std::cout << "(Cannot test " << __FILE__ <<
            " not supported on this platform)" << std::endl;

  return 0;
}

#endif

