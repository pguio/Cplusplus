
#include <cstring>
#include <iostream>
#include <iomanip>

void convert(const char *str, bool &value)
{
  if (! strcmp(str, "yes")) {
    value = true;
    return;
  }
  if (! strcmp(str,  "no")) {
    value = false;
    return;
  }
  throw std::string(str);
}

int main()
{
  const char *str[]= {"yes", "no", "yep"
                     };
  bool value;

  try {
    for (int i=0; i<3; ++i) {
      convert(str[i], value);
      std::cout << "str=" << std::setw(3) << std::right << str[i]
                << " value=" << value << std::endl;
    }
    return 0;
  } catch(std::string &s) {
    std::cerr << " ** exception: could not convert string '" << s
              << "' to boolean." << std::endl;
    return 0;
  }

}
