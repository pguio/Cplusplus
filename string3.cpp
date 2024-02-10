
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void split(string &str)
{
  cout << "str " << str << endl;
  string::size_type pos = str.find('=');
  string::size_type len = str.length();
  //cout << "pos " << pos << " len " << len << endl;
  if (pos==string::npos || pos==len-1) {
    cout << "str " << str << endl;
  } else {
    string str1(str.substr(0, pos));
    string str2(str.substr(pos+1));
    cout << "str1 " << str1 << " str2 " << str2 << endl;
  }
  cout << "====================" << endl;
}

int main()
{
  string str1("coucou=bobo");
  string str2("coucou");
  string str3("coucou=");

  split(str1);
  split(str2);
  split(str3);

  return 0;
}
