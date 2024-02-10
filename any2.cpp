
#include <map>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

template<class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v)
{
  if ( !v.empty() ) {
    typename std::vector<T>::const_iterator i = v.begin();
    typename std::vector<T>::const_iterator end = v.end();
    os << *i;
    for ( ++i; i != end; ++i ) os << ',' << *i;
  }
  return os;
}

template<class K, class V>
std::ostream& operator<<(std::ostream &os, const std::map<K,V> &v)
{
  if ( !v.empty() ) {
    typename std::map<K,V>::const_iterator i = v.begin();
    typename std::map<K,V>::const_iterator end = v.end();
    os << '(' << i->first << ';' << i->second << ')' ;
    for ( ++i; i != end; ++i )
      os << ',' << '(' << i->first << ';' << i->second << ')';
  }
  return os;
}

#include <any.h>

typedef std::vector<bool> boolVect;
#if defined(HAVE_ANY_NAMESPACE)
typedef any::Any Any;
#endif
typedef std::map<int, Any> anyMap;
typedef anyMap::value_type anyPair;
typedef anyMap::const_iterator anyMapConstIter;

int main()
{
  boolVect vectbool;

  vectbool.push_back(true);
  vectbool.push_back(false);
  vectbool.push_back(true);
  vectbool.push_back(true);
  vectbool.push_back(false);
  vectbool.push_back(true);

  cout << "vectbool=" << vectbool << endl;

  std::vector<boolVect> vectvectbool;
  vectvectbool.push_back(vectbool);
  vectvectbool.push_back(vectbool);

  cout << "vectvectbool=" << vectvectbool << endl;

  anyMap values;

  values[1] = double(2.0);
  values[2] = std::string("hello");
  values[3] = int(100);
  values[4] = bool(false);
  values[5] = vectbool;
  cout << "values=" << values << endl;


  {
    anyMapConstIter i = values.begin();
    for (unsigned c=0; c<values.size(); ++c)
      cout << (i++)->second << endl;
  }

  {
    anyMapConstIter i = values.begin();
    anyMapConstIter end = values.end();
    cout << i->second;
    for ( ++i; i != end; ++i ) cout << ',' << i->second;
    cout << endl;
  }
  {
    anyMapConstIter i = values.begin();
    anyMapConstIter end = values.end();
    for ( ; i != end; ++i ) {
      cout << i->second << " " << i->second.type().name() << endl;
    }
  }

  return 0;
}

