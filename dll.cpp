
#include <cmath>
#include <iostream>

#if defined(HAVE_DLFCN_H)

#include <dlfcn.h>

#include <gnu/lib-names.h>  /* Defines LIBM_SO (which will be a
                                      string such as "libm.so.6") */


int main(int argc, char **argv)
{
  void *handle;
  double (*cosine)(double);
  const char *error;

  handle = dlopen (LIBM_SO, RTLD_LAZY);
  if (!handle) {
    std::cerr << "dlopen: " << dlerror() << std::endl;
    return !0;
  }

  cosine = (double (*)(double))dlsym(handle, "cos");
  if ((error = dlerror()))  {
    std::cerr << "dlsym: " << error << std::endl;
    return !0;
  }

  std::cout << "(*cosine)(2.0)=" << (*cosine)(2.0) << std::endl;
  std::cout << "cos(2.0)      =" << cos(2.0) << std::endl;

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

