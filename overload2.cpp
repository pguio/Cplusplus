#include <fstream>
#include <iostream>
#include <map>

using std::endl;
using std::ostream;

class Foo {
public:
  enum {periodic=0, dirichlet, mixed };
private:
  struct Conf {
    std::map<int, const char*> field1_map;
    int field1;
    double field2;
    const char *field3;
    Conf() :  field1_map(), field1(1), field2(20.0), field3("coucou")
    {
      field1_map.insert(std::pair<int, const char*>(periodic,"periodic"));
      field1_map.insert(std::pair<int, const char*>(dirichlet,"dirichlet"));
      field1_map.insert(std::pair<int, const char*>(mixed,"newmann"));
    }
  };
  Conf conf;
  friend ostream& operator<<(ostream& os, const Foo::Conf &conf);
public:
  friend ostream& operator<<(ostream& os, const Foo &foo);
};

inline
ostream& operator<<(ostream& os, const Foo::Conf &conf)
{
  os << "field1=" << (*conf.field1_map.find(conf.field1)).second << endl;
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

  std::cout << foo;

  fid << foo;

  return 0;
}
