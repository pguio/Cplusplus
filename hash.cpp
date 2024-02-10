
#include <iostream>

#if defined(HAVE_HASH_MAP)
#include <hash_map>
#elif defined(HAVE_EXT_HASH_MAP)
#include <ext/hash_map>
#elif defined(HAVE_UNORDERED_MAP)
#include <unordered_map>
#endif

using std::cout;
using std::endl;

#if !defined(HAVE_UNORDERED_MAP) && defined(__GNUC__)
using __gnu_cxx::hash;
#endif

#if defined(HAVE_HASH_MAP) || defined(HAVE_EXT_HASH_MAP)
int main()
{
  hash<const char*> H;
  cout << "foo -> " << H("foo") << endl;
  cout << "bar -> " << H("bar") << endl;
  cout << "bonjour -> " << H("bonjour") << endl;
  cout << "toto -> " << H("toto") << endl;
}

#else

int main(int nargs, char *args[])
{
  cout << args[0] << " not supported" << endl;
  return 0;
}

#endif
