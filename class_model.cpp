
#include <iostream>

class A {
public:
  void print()
  {
    std::cout << "this is A" << std::endl;
  }
};

class B {
public:
  void print(A &a)
  {
    a.print();
    std::cout << "this is B" << std::endl;
  }
};

class C {
public:
  A a;
  B b;
  void print()
  {
    b.print(a);
  }
};

int main()
{
  C c;
  c.print();

  return 0;
}
