
#include <enum.h>


namespace valueTypes {
  const static int boolVecR = 100;
  const static int intVecR  = 101;
  const static int realVecR = 102;

  namespace {
    valueMap::ValueDescPair v_mapInit[] = {
      valueMap::ValueDescPair(boolVecR      , "bool[3]"),
      valueMap::ValueDescPair(intVecR       ,  "int[3]"),
      valueMap::ValueDescPair(realVecR      , "real[3]")
    };

    valueMap::ValueDescPair *v_mapInitEnd(v_mapInit+
                                          sizeof v_mapInit / sizeof v_mapInit[0]);

    valueMap registerMe(v_mapInit, v_mapInitEnd);
  }
}

using namespace valueTypes;

int main()
{
  {
    valueMap::ValuesDescList::const_iterator i=valueMap::values.begin();
    do {
      std::cout << i->first << " " << i->second << std::endl;
      ++i;
    } while (i != valueMap::values.end());
  }
  return 0;
}
