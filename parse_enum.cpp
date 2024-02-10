
#include <cstdlib>
#include <iostream>
#include <sstream>


template<typename T>
void convert(const std::string &str, T &val)
{
  char *endptr;
  val = T(strtol(str.c_str(), &endptr, 10));
}

enum bc { dirichlet, neumann, periodic };

int main()
{
  const std::string str("100");

  bc a;
  convert(str, a);
  std::cout << "a=" << a << std::endl;
}
