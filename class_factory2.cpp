
#if defined(FACTORY_ARGS1)
#include <factory-args1.h>
#else
#include <factory-args.h>
#endif
#include <base-args.h>

typedef GenericFactory<Base, defaultIDKeyType> ClassFactory;
typedef ClassFactory::BasePtr BasePtr;

int main(int nargs, char *args[])
{
  try {

    ClassFactory::instance().content();

    {
      BasePtr object(ClassFactory::instance().create("Base", nargs, args));
      object->whoami();
    }

    {
      BasePtr object(ClassFactory::instance().create("Derived", nargs, args));
      object->whoami();
    }

    {
      BasePtr object(ClassFactory::instance().create("Foo", nargs, args));
      object->whoami();
    }

  }
  catch (std::string &msg) {

    std::cout << msg << std::endl;

    return 0;
  }

}
