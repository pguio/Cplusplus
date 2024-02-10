
#include <iostream>

class A { };

class B { };

int main()
{
  A* a = new A;
  B* b = reinterpret_cast<B*>(a);
  std::cout << "reinterpret_cast used to convert A*=" << a
            << " into B*=" << b << std::endl;

  return 0;
}
