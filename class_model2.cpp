
#include <iostream>
#include <bench.h>

const int N1=1000;

struct A {
  void dummy() {
    for (int i=1; i<N1; ++i);
  }
  A & self() {
    return *this;
  }
};
struct B {
  void dummy(A &a) {
    for (int i=1; i<N1; ++i) a.dummy();
  }
};
struct C1 {
  A a;
  B b;
  void dummy() {
    for (int i=1; i<N1; ++i) b.dummy(a);
  }
};

struct C2 : public A, public B {
  void dummy() {
    for (int i=1; i<N1; ++i) B::dummy(A::self());
  }
};

struct Test1 : bench::Test {
  void op() {
    C1 c;
    c.dummy();
  }
  std::string opName() const {
    return "C1";
  }
};

struct Test2 : bench::Test {
  void op() {
    C2 c;
    c.dummy();
  }
  std::string opName() const {
    return "C2";
  }
};

int main()
{
  bench::verbose = true;

  Test1 t1;
  bench::benchClassOp(t1, 0.5);
  Test2 t2;
  bench::benchClassOp(t2, 0.5);

  return 0;
}
