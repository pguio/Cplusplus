#include <iostream>
#include "circle.h"

using std::cout;

void circle::draw()
{
  // simple ascii circle<\n>
  cout << "\n";
  cout << "      ****\n";
  cout << "    *      *\n";
  cout << "   *        *\n";
  cout << "   *        *\n";
  cout << "   *        *\n";
  cout << "    *      *\n";
  cout << "      ****\n";
  cout << "\n";
}


extern "C" void registerShape()
{
  registerInFactory<circle> registerMe("circle");
}
