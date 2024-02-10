
#include <iostream>

class A {};
class B : public A {};

int main(void)
{
  try {
    throw B();
  } catch( A a )    {
    std::cout   << "Caught an A\n";
    return 0;
  } catch( B b )    {
    std::cout   << "Caught a B\n";
    return 0;
  }
}
