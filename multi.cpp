
#include <iostream>

class Base {
protected:
  int data_;
};

class Der1 : public Base {};

class Der2 : public Base {};

class Join : public Der1, public Der2 {
public:
  void method()
  {
    // Assignement to data_ not allowed because ambiguous
    // either Der1::data_ or Der2::data_ must be specified
    Der1::data_ = 1;
  }
};

int main()
{
  Join* j = new Join();
  // Direct cast from Join* to Base* not allowed because ambiguous
  // either "Join* to Der1* then to Base*" or
  //        "Join* to Der2* then to Base*"
  Base* b = reinterpret_cast<Base*>(reinterpret_cast<Der1*>(j));

  std::cout << "j=" << j << std::endl;
  std::cout << "b=" << b << std::endl;

  return 0;
}
