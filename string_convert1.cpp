
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <class Type>
Type convert(const string & str)
{
  istringstream iss(str);
  Type res;
  if (iss >> res) return res;
  else throw string(str " couldn't be converted.");
}


float convert(const string & str)
{
  istringstream iss(str);
  float value;
  char op;
  do {
    if (iss >> value >> )
    }

}


int main()
{
  istringstream iss("2.45 4 1 2e4/1e3");
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
  if ( iss >> d >> c >> d2  ) {
    cout << "extracted: " << d/d2 << endl;
  } else {
    cerr << "Didn't work" << endl;
  }

  return 0;
}

