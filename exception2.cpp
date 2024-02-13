
#include <iostream>
#include <iomanip>

enum range {LO, HI}; // exception of this type will be thrown

int func(int arg)
{
  if(arg > 10)
    throw(HI);
  if(arg < 5)
    throw(LO);
  return arg * 3;
}

int main()
{
  for(int i = 0; i < 14; ++i)
    try {
      std::cout << "func(" << std::setw(2) << std::right << i << ") = "
                << func(i) << std::endl;
      return 0;
    }
    catch (range e) {
      std::cout << "[ Exception: argument too " << (e ? "large" : "small")
                << ']' << std::endl;
    }
  return 0;
}

