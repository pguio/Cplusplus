
#include <factory.h>
#include <base.h>

typedef BaseFactory<Base> ClassFactory;
typedef ClassFactory::BasePtr BasePtr;


int main()
{

  ClassFactory::instance().content();

  BasePtr object1(ClassFactory::instance().create("Base"));
  object1->whoami();

  BasePtr object2(ClassFactory::instance().create("Derived"));
  object2->whoami();

  return 0;
}
