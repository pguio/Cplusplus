
#include <map>
#include <iostream>

using std::cout;
using std::endl;
using std::map;

typedef map<const char *, const char *> smap;

class foo {
public:
  static smap::value_type s_mapInit[], *s_mapInitEnd;
  static smap s_map;
};

smap::value_type foo::s_mapInit[] = {
  smap::value_type("key1", "data1"),
  smap::value_type("key2", "data2"),
  smap::value_type("key3", "data3")
};

smap::value_type *foo::s_mapInitEnd(s_mapInit +
                                    sizeof s_mapInit / sizeof s_mapInit[0]);

smap foo::s_map (s_mapInit, s_mapInitEnd);


int main()
{
  for (smap::iterator i=foo::s_map.begin(); i!=foo::s_map.end(); ++i)
    cout << i->first << "  " << i->second << endl;

  foo foo1;
  for (smap::iterator i=foo1.s_map.begin(); i!=foo1.s_map.end(); ++i)
    cout << i->first << "  " << i->second << endl;
}
