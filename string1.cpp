
#include <iostream>
#include <sstream>
#include <string>

int main()
{
  int n = 10;

  std::ostringstream os;
  os << n << " " << 20;
  std::string str(os.str());

  std::cout << str << std::endl;

}
