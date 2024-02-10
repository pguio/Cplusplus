

#ifndef FACTORY_ARGS1_H
#define FACTORY_ARGS1_H

//#define AUTO_PTR 1

#if defined(AUTO_PTR)
#include <memory>
#endif
#include <cstdlib>
#include <string>
#include <map>
#include <iostream>

namespace factory {
  void baseDummy();
  void derivedDummy();
}

typedef std::string defaultIDKeyType;

template <class ManufacturedType, typename ClassIDKey=defaultIDKeyType>
class GenericFactory {
public:
#if defined(AUTO_PTR)

  typedef std::auto_ptr<ManufacturedType> BasePtr;
#else

  typedef ManufacturedType* BasePtr;
#endif
private:

  typedef BasePtr (*BaseCreateFn)(int, char **);
  typedef std::map<ClassIDKey, BaseCreateFn> FnRegistry;
  FnRegistry registry;

  GenericFactory() : registry() {}
  GenericFactory(const GenericFactory&); // Not implemented
  GenericFactory &operator=(const GenericFactory&); // Not implemented

public:
  static GenericFactory &instance() {
    if ( !bf ) {
      bf = new GenericFactory<ManufacturedType, ClassIDKey>;
      std::atexit(kill);
    }
    return *bf;
  }

  void RegCreateFn(const ClassIDKey & id, BaseCreateFn fn) {
    registry[id] = fn;
  }

  BasePtr create(const ClassIDKey &className,int nargs, char *args[]) const {
    BasePtr theObject(0);
    typename FnRegistry::const_iterator regEntry = registry.find(className);
    if (regEntry != registry.end()) {
      theObject = regEntry->second(nargs,args);
    } else {
      throw std::string("Error: unknown ClassIDKey: "+className);
    }
    return theObject;
  }
  void content() const {
    std::cout << "Factory content: " << std::endl;
    for (typename FnRegistry::const_iterator regEntry = registry.begin();
         regEntry != registry.end(); ++regEntry) {
      std::cout << " * " << regEntry->first << std::endl;
    }
  }
  void init() const {
    factory::baseDummy();
    factory::derivedDummy();
  }
private:
  static GenericFactory<ManufacturedType, ClassIDKey> *bf;
  /// Call by atexit() to clean up.
  static void kill() {
    GenericFactory<ManufacturedType, ClassIDKey> *p(bf);
    bf = 0;
    p->~GenericFactory<ManufacturedType, ClassIDKey>();
  }
};

template <class ManufacturedType, typename ClassIDKey>
GenericFactory<ManufacturedType, ClassIDKey> *GenericFactory<ManufacturedType, ClassIDKey>::bf(0);


template <class AncestorType, class ManufacturedType, typename ClassIDKey=defaultIDKeyType>
class RegisterInFactory {
private:
  typedef GenericFactory<AncestorType, ClassIDKey> Factory;
  typedef typename Factory::BasePtr BasePtr;
public:
  static BasePtr CreateInstance(int nargs, char *args[]) {
    return BasePtr(new ManufacturedType(nargs, args));
  }

  explicit RegisterInFactory(const ClassIDKey &id) {
    Factory::instance().RegCreateFn(id, CreateInstance);
  }
};


#endif
