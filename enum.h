
#include <map>
#include <string>
#include <iostream>

namespace valueTypes {


  struct valueMap {
    typedef int valueType;
    typedef std::map<valueType, const std::string> ValuesDescList;
    typedef ValuesDescList::value_type ValueDescPair;
    typedef ValueDescPair* Iter;

    valueMap(const Iter first, const Iter last);

		static void printValueMap();

    static ValuesDescList values;
  };


}

