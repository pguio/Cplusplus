
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

class Base {
public:
  Base()
  {}
  virtual ~Base()
  {}
protected:
  virtual void dummy()
  {}
};

class Derived : public Base {};

int main()
{
  {
    Base* b1 = new Derived;
    Base* b2 = new Base;

    Derived* d1 = dynamic_cast<Derived*>(b1);
    if (d1)
      cout << "Derived* d1 = dynamic_cast<Derived*>(b1) successfull" << endl;
    else
      cout << "Derived* d1 = dynamic_cast<Derived*>(b1) unsuccessfull" << endl;

    Derived* d2 = dynamic_cast<Derived*>(b2);
    if (d2)
      cout << "Derived* d2 = dynamic_cast<Derived*>(b2) successfull" << endl;
    else
      cout << "Derived* d2 = dynamic_cast<Derived*>(b2) unsuccessfull" << endl;
  }

  {
    try {
      Base* b1 = new Derived;
      Base* b2 = new Base;

      Derived& d1 = dynamic_cast<Derived&>(*b1);
      std::cout << "dynamic_cast used to convert b1=" << b1
                << " into d1=" << &d1 << std::endl;

      Derived& d2 = dynamic_cast<Derived&>(*b2);
      std::cout << "dynamic_cast used to convert b2=" << b2
                << " into d2=" << &d2 << std::endl;

      return 0;
    }
    catch (std::bad_cast& x) {
      std::cerr << "dynamic_cast failed: " <<  x.what() << endl;
      return 0;
    }
  }
}
