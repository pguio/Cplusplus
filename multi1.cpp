#include <iostream>

class Base {
protected:
  int data_;
};

class Der1 : public virtual Base {};

class Der2 : public virtual Base {};

class Join : public Der1, public Der2 {
public:
  void method()
  {
    // Derv1 and Derv2 are virtual so only one subobject Base
    data_ = 1;
  }
};

int main()
{
  Join* j = new Join();
  // an instance of Join will have have only a single Base subobject
  Base* b = j;

  std::cout << "j=" << j << std::endl;
  std::cout << "b=" << b << std::endl;

  return 0;
}
