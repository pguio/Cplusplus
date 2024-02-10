

#include <iostream>

class C {};

int main()
{
  {
    const C* a = new C;
    C* b = const_cast<C*>(a);
    std::cout << "const_cast used to remove constness "
              << a << " -> " << b << std::endl;
  }
  {
    C* a = new C;
    const C* b = const_cast<C*>(a);
    std::cout << "const_cast used to set constness    "
              << a << " -> " << b << std::endl;
  }

  return 0;
}
