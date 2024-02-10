
#include <map>
#include <string>
#include <iostream>

namespace valueTypes {
  static const int none       = 0;
  static const int boolean    = 1;
  static const int character  = 2;
  static const int integer    = 3;
  static const int real       = 4;
  static const int charStr    = 5;
  static const int boolVect   = 6;
  static const int charVect   = 7;
  static const int intVect    = 8;
  static const int realVect   = 9;
  static const int stringVect = 10;

  struct valueMap {
    typedef int valueType;
    typedef std::map<valueType, const std::string> ValuesDescList;
    typedef ValuesDescList::value_type ValueDescPair;
    typedef ValueDescPair* Iter;
    valueMap(const Iter first, const Iter last);
    static ValuesDescList values;
  };
}

