
#include <cstring>
#include <string>
#include <iostream>
#include <stdexcept>
#include <iomanip>

struct bool_conversion_error : public std::exception {
  typedef std::string string;
  explicit bool_conversion_error(const char *str) : s(str)
  {}
  ~bool_conversion_error() throw()
  {}
  const char* what() const throw() {
    string msg(" ** exception: could not convert string '"+s+"' to boolean.");
    return msg.c_str();
  }
  string s;
};

void convert(const char *str, bool &value)
{
  if (! strcmp(str, "yes")) {
    value = true;
    return;
  }
  if (! strcmp(str, "no")) {
    value = false;
    return;
  }
  throw bool_conversion_error(str);
}

int main()
{
  const char *str[] = { "yes", "no", "yep"
                      };
  bool value;

  try {
    for (int i=0; i<3; ++i) {
      convert(str[i],value);
      std::cout << "str=" << std::setw(3) << std::right << str[i]
                << " value=" << value << std::endl;
    }
  } catch(bool_conversion_error& x) {
    std::cerr << x.what() << std::endl;
    return 0;
  }

}
