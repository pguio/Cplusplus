

#ifndef FACTORY_ARGS_H
#define FACTORY_ARGS_H

//#define AUTO_PTR 1

#if defined(AUTO_PTR)
#include <memory>
#endif
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
    static GenericFactory<ManufacturedType, ClassIDKey> bf;
    return bf;
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
    typename FnRegistry::const_iterator regEntry = registry.begin();
    std::cout << "Factory content: " << std::endl;
    for ( ; regEntry != registry.end(); ++regEntry) {
      std::cout << " * " << regEntry->first << std::endl;
    }
  }
  void init() const {
    factory::baseDummy();
    factory::derivedDummy();
  }
};


template <class AncestorType, class ManufacturedType, typename ClassIDKey=defaultIDKeyType>
class RegisterInFactory {
private:
  typedef GenericFactory<AncestorType,ClassIDKey> Factory;
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
