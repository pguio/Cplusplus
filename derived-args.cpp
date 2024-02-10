
#include <iostream>
#include "derived-args.h"
#if defined(FACTORY_ARGS1)
#include "factory-args1.h"
#else
#include "factory-args.h"
#endif

// Helper to keep maintenance down.  This is the unique
// identifier for the class.  It could just as easily be a class static
// variable.

const Base::BASE_KEY_TYPE baseName ("Derived");

Derived::Derived(int nargs, char *args[]) : Base(nargs, args)
{
  std::cout << "Derived created with " << nargs << " arguments: ";

  if (nargs > 0) {
    std::cout << args[0];
    for (int i=1; i<nargs; ++i)
      std::cout << ", " << args[i];
  }

  std::cout << std::endl;
}

Derived::~Derived()
{}

void Derived::whoami()
{
  std::cout << "I am a Derived class" << std::endl;
  std::cout << "My parents say: ";
  Base::whoami();
}

namespace {
  RegisterInFactory<Base, Derived, Base::BASE_KEY_TYPE> registerMe(baseName);
}

namespace factory {
  void derivedDummy() {}
}

