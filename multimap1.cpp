
#include <cstring>
#include <iostream>
#include <map>

using std::cout;
using std::endl;


struct ltstr {
  bool operator()(const char* s1, const char* s2) const {
    return strcmp(s1, s2) < 0;
  }
};

typedef std::multimap<const char*, int, ltstr> mmap;
typedef mmap::iterator miterator;
typedef std::pair<const char* const, int> mpair;

int main()
{
  mmap m;

  m.insert(mpair("a", 1));
  m.insert(mpair("c", 2));
  m.insert(mpair("b", 3));
  m.insert(mpair("b", 4));
  m.insert(mpair("a", 5));
  m.insert(mpair("b", 6));

  cout << "Number of elements with key a: " << m.count("a") << endl;
  cout << "Number of elements with key b: " << m.count("b") << endl;
  cout << "Number of elements with key c: " << m.count("c") << endl;

  cout << "Elements in m: " << endl;
  for (miterator it = m.begin(); it != m.end(); ++it)
    cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;
}
