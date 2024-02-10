

#ifndef FACTORY_H
#define FACTORY_H

//#define AUTO_PTR 1

#if defined(AUTO_PTR)
#include <memory>
#endif
#include <string>
#include <map>
#include <iostream>


typedef std::string defaultIDKeyType;

// CPP macro implementation

template <class Base>
class BaseFactory {
public:
#if defined(AUTO_PTR)
  typedef std::auto_ptr<Base> BasePtr;
#else
  typedef Base* BasePtr;
#endif
private:
  typedef BasePtr (*BaseCreateFn)();
  typedef std::map<defaultIDKeyType, BaseCreateFn> FnRegistry;
  FnRegistry registry;

  BaseFactory() : registry() {}
  BaseFactory(const BaseFactory &); // Not implemented
  BaseFactory & operator=(const BaseFactory &); // Not implemented

public:
  static BaseFactory & instance() {
    static BaseFactory bf;
    return bf;
  }

  bool RegCreateFn(const defaultIDKeyType &className, BaseCreateFn fn) {
    registry[className] = fn;
    return true;
  }

  BasePtr create(const defaultIDKeyType &className) const {
    BasePtr theObject(0);
    typename FnRegistry::const_iterator regEntry = registry.find(className);
    if (regEntry != registry.end()) {
      theObject = regEntry->second();
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
};


#define REGISTER_CLASS(BASE_CLASS, DERIVED_CLASS)                 \
namespace                                                         \
{                                                                 \
    BaseFactory<BASE_CLASS>::BasePtr Create##DERIVED_CLASS()      \
    {                                                             \
        return BaseFactory<BASE_CLASS>::BasePtr(new DERIVED_CLASS); \
    }                                                             \
    bool dummy = BaseFactory<BASE_CLASS>::instance().RegCreateFn( \
         #DERIVED_CLASS, Create##DERIVED_CLASS);                  \
}                                                                 \
 
// Generic implementation

template <class ManufacturedType, typename ClassIDKey=defaultIDKeyType>
class GenericFactory {
public:
#if defined(AUTO_PTR)
  typedef std::auto_ptr<ManufacturedType> BasePtr;
#else
  typedef ManufacturedType* BasePtr;
#endif
private:
  typedef BasePtr (*BaseCreateFn)();
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

  BasePtr create(const ClassIDKey &className) const {
    BasePtr theObject(0);
    typename FnRegistry::const_iterator regEntry = registry.find(className);
    if (regEntry != registry.end()) {
      theObject = regEntry->second();
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

};


template <class AncestorType,
         class ManufacturedType,
         typename ClassIDKey=defaultIDKeyType>
class RegisterInFactory {
private:
  typedef GenericFactory<AncestorType, ClassIDKey> Factory;
  typedef typename Factory::BasePtr BasePtr;
public:
  static BasePtr CreateInstance() {
    return BasePtr(new ManufacturedType);
  }

  explicit RegisterInFactory(const ClassIDKey &id) {
    Factory::instance().RegCreateFn(id, CreateInstance);
  }
};


#endif
