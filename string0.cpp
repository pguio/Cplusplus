
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

int main()
{

  std::string s(10u,' ');
  const char * A = "This is a test";

  s += A;
  cout << "s = " << (s + '\n');
  cout << "As a null-terminated sequence: " << s.c_str() << endl;
  cout << "The sixteenth character is: " << s[15] << endl;

  std::reverse (s.begin(), s.end());
  //s.push_back('\n');
  s.append("\n");
  cout << s;

  return 0;
}

