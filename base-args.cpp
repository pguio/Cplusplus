
#include <iostream>
#include "base-args.h"
#if defined(FACTORY_ARGS1)
#include "factory-args1.h"
#else
#include "factory-args.h"
#endif

// Helper to keep maintenance down.  This is the unique
// identifier for the class.  It could just as easily be a class static
// variable.

const Base::BASE_KEY_TYPE baseName ("Base");

Base::Base(int nargs, char *args[])
{
  std::cout << "Base created with " << nargs << " arguments: ";

  if (nargs > 0) {
    std::cout << args[0];
    for (int i=1; i<nargs; ++i)
      std::cout << ", " << args[i];
  }

  std::cout << std::endl;
}

Base::~Base()
{}

void Base::whoami()
{
  std::cout << "I am a Base class" << std::endl;
}

namespace {
  RegisterInFactory<Base, Base, Base::BASE_KEY_TYPE> registerMe(baseName);
}

namespace factory {
  void baseDummy() {}
}

