#include <iostream>
#include "square.h"

using std::cout;

void square::draw()
{
  // simple ascii square
  cout << "\n";
  cout << "    *********\n";
  cout << "    *       *\n";
  cout << "    *       *\n";
  cout << "    *       *\n";
  cout << "    *       *\n";
  cout << "    *********\n";
  cout << "\n";
}

extern "C" void registerShape()
{
  registerInFactory<square> registerMe("square");
}


