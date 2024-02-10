
#include <map>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

typedef std::map<int, const char*> LUT;
typedef LUT::iterator LUTiter;
typedef LUT::const_iterator LUTconst_iter;
typedef LUT::value_type Pair;

const Pair opt[] = {
  Pair(0, "periodic"),
  Pair(1, "dirichlet"),
  Pair(3, "neumann")
};

class Foo {
  LUT options;
public:
  Foo() : options(opt, opt+3) {}
  friend ostream& operator<<(ostream& os, const Foo & foo) {
    LUTconst_iter last=foo.options.end();
    for (LUTconst_iter i=foo.options.begin(); i!=last; ++i)
      cout << "(" << i->first << "," << i->second << ")" << endl;
    return os;
  }
};

class Foo1 {
  static LUT options;
public:
  Foo1() {}
  friend ostream& operator<<(ostream& os, const Foo1 & foo) {
    LUTconst_iter last=foo.options.end();
    for (LUTconst_iter i=foo.options.begin(); i!=last; ++i)
      cout << "(" << i->first << "," << i->second << ")" << endl;
    return os;
  }
};

LUT Foo1::options(opt, opt+3);

int main()
{
  LUT options(opt, opt+3);

  LUTiter last=options.end();
  for (LUTiter i=options.begin(); i!=last; ++i)
    cout << "(" << i->first << "," << i->second << ")" << endl;
  cout << endl;

  Foo foo;
  cout << foo << endl;

  Foo1 foo1;
  cout << foo1 << endl;
}
