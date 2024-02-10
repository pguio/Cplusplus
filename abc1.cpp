#include <fstream>
#include <iostream>
#include <typeinfo>

class ABC {
public:
  ABC() {}
  virtual ~ABC() {}

public:
  virtual void printOn(std::ostream &os) const=0;
};

class Imp1 : public ABC {
public:
  void printOn(std::ostream &os) const {
    os << "This is an Imp1 instance";
  }
};

class Imp2 : public ABC {
public:
  void printOn(std::ostream &os) const {
    os << "This is an Imp2 instance";
  }
};

template<class T>
class Master {
public:
  Master() : abc() {}
  virtual ~Master() {}
  T abc;
  void printOn(std::ostream &os) const {
    abc.printOn(os);
  }
  void hello() const;
};

template<class T>
void Master<T>::hello() const
{
  std::cout << "Typeid = " << typeid(*this).name() << std::endl;
  std::cout << "hello world!" << std::endl;
}

class Derived1 : public Master<Imp1> {};
class Derived2 : public Master<Imp2> {};

int main()
{
  Derived1 master1;
  Derived2 master2;

  master1.printOn(std::cout);
  std::cout << std::endl;
  master1.hello();
  master2.printOn(std::cout);
  std::cout << std::endl;
  master2.hello();

  return 0;
}
