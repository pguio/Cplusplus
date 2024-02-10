
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

template<class T>
ostream& operator<<(ostream &os, const vector<T> &v)
{
  if (!v.empty()) {
    typename vector<T>::const_iterator i = v.begin();
    typename vector<T>::const_iterator end = v.end();
    os << *i;
    for ( ++i; i != end; ++i ) os << ',' << *i;
  }
  return os;
}

int main()
{
  vector<string> cstrvect;

  cstrvect.push_back("coucou");

  const string s1("coucou");
  const string s2("riri");

  string s1s2(s1);
  s1s2.append(s2);

  cout << s1s2 << " " << s1s2.find_first_not_of(s1) << endl;

  vector<string> strvect;

  cstrvect.push_back("coucou");
  cstrvect.push_back("gros minet");
  const string str(*cstrvect.begin());
  cstrvect.push_back(str);

  cout << cstrvect << endl;
  cout << strvect << endl;

}
