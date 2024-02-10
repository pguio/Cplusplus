
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;

int main()
{
  std::istringstream iss("2.45 4 1 2e4/1e3");
  double d;
  int i;
  bool flag;
  char c;
  double d2;
  if ( iss >> d >> i >> flag) {
    cout << "extracted: " << d << ", " << i << ", " << flag << endl;
  } else {
    cerr << "Didn't work" << endl;
  }
  if ( iss >> d >> c >> d2 && c == '/') {
    cout << "extracted: " << d/d2 << endl;
  } else {
    cerr << "Didn't work" << endl;
  }

  return 0;
}

