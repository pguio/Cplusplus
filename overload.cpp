#include <fstream>
#include <iostream>

using std::endl;
using std::ostream;

class Foo {
private:
  struct Conf {
    int field1;
    double field2;
    const char *field3;
    Conf() : field1(1), field2(20.0), field3("coucou")
    { }

  };
  Conf conf;
  friend ostream& operator<<(ostream& os, const Conf &conf);
public:
  void ViewConf(ostream& os)
  {
    os << conf;
  }
  friend ostream& operator<<(ostream& os, const Foo &foo);
};

inline
ostream& operator<<(ostream& os, const Foo::Conf &conf)
{
  os << "field1=" << conf.field1 << endl;
  os << "field2=" << conf.field2 << endl;
  os << "field3=" << conf.field3 << endl;
  return os;
}

inline
ostream& operator<<(ostream& os, const Foo &foo)
{
  os << foo.conf;
  return os;
}

int main()
{
  Foo foo;
  std::ofstream fid("overload.dat");

  foo.ViewConf(std::cout);
  std::cout << foo;

  foo.ViewConf(fid);
  fid << foo;

  return 0;
}
