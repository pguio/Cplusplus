
# include <iostream>
# include <map>
# include <string>

using std::cout;
using std::endl;

class totoclass {
public:
  enum OptionEnum { nx, ny, nz, nxa, nxb, nyc, nyd };
  typedef std::multimap<int, const char*> Options;
  typedef std::pair<OptionEnum, const char* const> OptionPair;

  totoclass() : SolverOption()
  {
    MapInit();
  }
  ~totoclass()
  {}

  void listoption()
  {
    Options::iterator I=SolverOption.begin();
    do {
      cout << "enum= " << (*I).first << " name= " << (*I).second << endl;
      ++I;
    }
    while (I != SolverOption.end());
  }

  void listoptionkey(int key)
  {
    Options::iterator I=SolverOption.find(key);
    do {
      cout << "key= " << key << " name= " << (*I).second << endl;
      ++I;
    }
    while (I != SolverOption.upper_bound(key));
  }

private :

  Options SolverOption;

  void MapInit()
  {
    SolverOption.insert(OptionPair(nx, "nx"));
    SolverOption.insert(OptionPair(nx, "-nx"));
    SolverOption.insert(OptionPair(ny, "ny"));
    SolverOption.insert(OptionPair(ny, "-ny"));
    SolverOption.insert(OptionPair(nxa, "nxa"));
    SolverOption.insert(OptionPair(nxa, "-nxa"));
    SolverOption.insert(OptionPair(nxb, "nxb"));
    SolverOption.insert(OptionPair(nxb, "-nxb"));
    SolverOption.insert(OptionPair(nyc, "nyc"));
    SolverOption.insert(OptionPair(nyc, "-nyc"));
    SolverOption.insert(OptionPair(nyd, "nyd"));
    SolverOption.insert(OptionPair(nyd, "-nyd"));
    SolverOption.insert(OptionPair(nx, "-Nx"));
  }

};

int main(int argc, char *argv[])
{

  totoclass toto;
  toto.listoption();
  toto.listoptionkey(0);

  return 0;
}
