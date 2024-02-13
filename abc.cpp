#include <fstream>
#include <iostream>

class ABC {
public:
  ABC() {}
  virtual ~ABC() {}
  virtual void printOn(std::ostream &os) const=0;
};

class Imp1 : public ABC {
public:
  void printOn(std::ostream &os) const
  {
    os << "This is an Imp1 instance";
  }
};

class Imp2 : public ABC {
public:
  void printOn(std::ostream &os) const
  {
    os << "This is an Imp2 instance";
  }
};

class Master {
public:
  explicit Master(ABC *_abc) : abc(_abc) {}
  virtual ~Master() {}
  ABC *abc;
  void printOn(std::ostream &os) const
  {
    abc->printOn(os);
  }
};

class Derived1 : public Master {
public:
  Derived1() : Master(new Imp1) {}
  ~Derived1()
  {
    delete abc;
  }
};

class Derived2 : public Master {
public:
  Derived2() : Master(new Imp2) {}
  ~Derived2()
  {
    delete abc;
  }
};


int main()
{
  Derived1 master1;
  Derived2 master2;

  master1.printOn(std::cout);
  std::cout << std::endl;
  master2.printOn(std::cout);
  std::cout << std::endl;

  return 0;
}
