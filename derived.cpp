
#include <iostream>
#include "derived.h"
#include "factory.h"

// Helper to keep maintenance down.  This is the unique
// identifier for the class.  It could just as easily be a class static
// variable.

const Base::BASE_KEY_TYPE baseName ("Derived");

Derived::Derived() {}

Derived::~Derived() {}

void Derived::whoami()
{
  std::cout << "I am a Derived class" << std::endl;
  std::cout << "My parents say: ";
  Base::whoami();
}

namespace {

  REGISTER_CLASS(Base,Derived)


  RegisterInFactory<Base, Derived, Base::BASE_KEY_TYPE> registerMe(baseName);

}
