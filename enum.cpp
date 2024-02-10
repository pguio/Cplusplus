
#include <enum.h>

namespace valueTypes {

  namespace {
    valueMap::ValueDescPair v_mapInit[] = {
      valueMap::ValueDescPair(none      , ""),
      valueMap::ValueDescPair(boolean   , "bool"),
      valueMap::ValueDescPair(character , "char"),
      valueMap::ValueDescPair(integer   , "int"),
      valueMap::ValueDescPair(real      , "real"),
      valueMap::ValueDescPair(charStr   , "string"),
      valueMap::ValueDescPair(boolVect  , "bool[]"),
      valueMap::ValueDescPair(charVect  , "char[]"),
      valueMap::ValueDescPair(intVect   , "int[]"),
      valueMap::ValueDescPair(realVect  , "real[]"),
      valueMap::ValueDescPair(stringVect, "string[]")
    };
    valueMap::ValueDescPair *v_mapInitEnd(v_mapInit+
                                          sizeof v_mapInit / sizeof v_mapInit[0]);
  }
  valueMap::valueMap(const Iter first, const Iter last)
  {
    values.insert(first, last);
  }
  valueMap::ValuesDescList valueMap::values(v_mapInit, v_mapInitEnd);
}

