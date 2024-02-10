
#include <iostream>
#include "base.h"
#include "factory.h"

// Helper to keep maintenance down.  This is the unique
// identifier for the class.  It could just as easily be a class static
// variable.

const Base::BASE_KEY_TYPE baseName ("Base");

Base::Base() {}

Base::~Base() {}

void Base::whoami()
{
  std::cout << "I am a Base class" << std::endl;
}

namespace {

  BaseFactory<Base>::BasePtr CreateBase()
  {
    return BaseFactory<Base>::BasePtr(new Base);
  }
  bool dummy = BaseFactory<Base>::instance().RegCreateFn(baseName, CreateBase);


  RegisterInFactory<Base, Base, Base::BASE_KEY_TYPE> registerMe(baseName);

}
