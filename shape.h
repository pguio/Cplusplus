#ifndef SHAPE_H
#define SHAPE_H
#include <map>
#include <string>
// base class for all shapes
class shape {
public:
  virtual ~shape() {}
  virtual void draw()=0;
};

// our global factory
class shapeFactory {
public:
  typedef shape* shapePtr;
  typedef shapePtr (*shapeCreateFn)();
  typedef std::map<std::string, shapeCreateFn> registry_t;
  registry_t registry;
public:
  shapeFactory() : registry() {}
  static shapeFactory &instance() {
    static shapeFactory bf;
    return bf;
  }
  void registerShape(const std::string &name, shapeCreateFn bf) {
    registry[name] = bf;
  }
  shapePtr create(const std::string &name) const {
    shapePtr theObject(0);
    registry_t::const_iterator regEntry = registry.find(name);
    if (regEntry != registry.end()) {
      theObject = regEntry->second();
      std::cout << "creating " << name << " shape" << std::endl;
    }
    return theObject;
  }
  registry_t::iterator begin() {
    return registry.begin();
  }
  registry_t::iterator end() {
    return registry.end();
  }
};

template<class shapeType>
class registerInFactory {
private:
  typedef shapeFactory::shapePtr shapePtr;
public:
  static shapePtr createInstance() {
    return shapePtr(new shapeType);
  }
  explicit registerInFactory(const std::string &name) {
    std::cout << "registering " << name << " in factory" << std::endl;
    shapeFactory::instance().registerShape(name, createInstance);
  }
};

typedef shapeFactory::registry_t factory_t;
typedef factory_t::iterator factory_iterator;


#endif // __SHAPE_H
