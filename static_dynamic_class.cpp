
#include <iostream>

using std::ostream;

class Solver {
  struct solver_conf {
    int field1;
    double field2;
    solver_conf() : field1(1), field2(5e-3) {}
  }
  conf;
public:
  Solver() : conf() {}
  friend ostream& operator<<(ostream& o, const Solver& s);
};

ostream& operator<<(ostream& os, const Solver& s)
{
  os << "conf : (" << s.conf.field1 << ", " << s.conf.field2 << ")";
  return os;
}

int main()
{
  Solver solver;
  //    Solver *ps = new Solver();
  Solver *ps;
  ps = new Solver();

  std::cout << solver << std::endl;
  std::cout << *ps << std::endl;

  delete ps;

  return 0;
}

