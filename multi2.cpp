
#include <iostream>

class Base {
public:
  Base()
  {}
  virtual ~Base()
  {}
  virtual void foo() = 0;
  virtual void bar() = 0;
};

class Der1 : public virtual Base {
public:
  virtual void foo()
  {
    std::cout << "I am a Der1::foo() calling this->bar()" << std::endl;
    // Cross delegation
    // when Der1::foo() calls this->bar(), it ends up calling Der2::bar().
    this->bar();
  }
};

class Der2 : public virtual Base {
public:
  virtual void bar()
  {
    std::cout << "I am a Der2::bar()" << std::endl;
  }
};

class Join : public Der1, public Der2 {
};

int main()
{
  Join* p1 = new Join();
  Der1* p2 = p1;
  Der2* p3 = p1;
  Base* p4 = p1;

  p1->foo();
  p2->foo();
  p3->foo();
  p4->foo();

  p1->bar();
  p2->bar();
  p3->bar();
  p4->bar();
}
