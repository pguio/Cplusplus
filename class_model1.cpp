#include <iostream>

class A {
public:
  void print() {
    std::cout << "this is A" << std::endl;
  }
  A &self() {
    return *this;
  }
};

class B {
public:
  void print(A &a) {
    a.print();
    std::cout << "this is B" << std::endl;
  }
};

class C : public A, public B {
public:
  void print() {
    B::print(A::self());
  }
};

int main()
{
  C c;
  c.print();

  return 0;
}
