
# include <iostream>
# include <map>
# include <string>

using std::cout;
using std::endl;
using std::map;

class Foo {
  enum OptionEnum { nx, ny, nz, nxa, nxb, nyc, nyd };
  typedef map<OptionEnum, const char *> Options;

public:
  Foo() : SolverOption()
  {
    MapInit();
  }
  ~Foo() {}
  void listoption()
  {
    Options::iterator iter=SolverOption.begin();
    do {
      cout << "enum= " << iter->first << " name= " << iter->second << endl;
      ++iter;
    }
    while (iter != SolverOption.end());
  }

private:

  Options SolverOption;

  void MapInit()
  {
    SolverOption[nx]="nx";
    SolverOption[ny]="ny";
    SolverOption[nxa]="nxa";
    SolverOption[nxb]="nxb";
    SolverOption[nyc]="nyc";
    SolverOption[nyd]="nyd";
  }
};

int main(int argc, char *argv[])
{
  Foo foo;
  foo.listoption();
  return 0;
}
