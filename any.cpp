
#include <vector>
#include <string>
#include <iostream>

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

#include <any.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef vector<bool> boolVect;
#if defined(HAVE_ANY_NAMESPACE)
typedef any::Any Any;
#endif
typedef vector<Any> anyVect;
typedef anyVect::const_iterator anyVectConstIter;

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

  vector<boolVect> vectvectbool;
  vectvectbool.push_back(vectbool);
  vectvectbool.push_back(vectbool);

  cout << "vectvectbool=" << vectvectbool << endl;

  anyVect values;

  values.push_back(double(2.0));
  values.push_back(string("hello"));
  values.push_back(int(100));
  values.push_back(bool(false));
  values.push_back(vectbool);
  cout << "values=" << values << endl;

  {
    anyVectConstIter i = values.begin();
    for (unsigned c=0; c<values.size(); ++c)
      cout << *i++ << endl;
  }

  {
    anyVectConstIter i = values.begin();
    anyVectConstIter end = values.end();
    cout << *i;
    for ( ++i; i != end; ++i ) cout << ',' << *i;
    cout << endl;
  }

  {
    anyVectConstIter i = values.begin();
    anyVectConstIter end = values.end();
    for ( ; i != end; ++i )
      cout << *i << " " << (*i).type().name() << endl;
  }

  return 0;
}

