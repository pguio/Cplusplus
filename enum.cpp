
#include <enum.h>

namespace valueTypes {

  namespace myBase {

    const int none       = 0;
    const int boolean    = 1;
    const int character  = 2;
    const int integer    = 3;
    const int real       = 4;
    const int charStr    = 5;
    const int boolVect   = 6;
    const int charVect   = 7;
    const int intVect    = 8;
    const int realVect   = 9;
    const int stringVect = 10;


    valueMap::ValueDescPair v_mapInit[] = {
      valueMap::ValueDescPair(none, ""),
      valueMap::ValueDescPair(boolean, "bool"),
      valueMap::ValueDescPair(character, "char"),
      valueMap::ValueDescPair(integer, "int"),
      valueMap::ValueDescPair(real, "real"),
      valueMap::ValueDescPair(charStr, "string"),
      valueMap::ValueDescPair(boolVect, "bool[]"),
      valueMap::ValueDescPair(charVect, "char[]"),
      valueMap::ValueDescPair(intVect, "int[]"),
      valueMap::ValueDescPair(realVect, "real[]"),
      valueMap::ValueDescPair(stringVect, "string[]")
    };

    valueMap::ValueDescPair *v_mapInitEnd(v_mapInit+
                                          sizeof(v_mapInit)/sizeof(v_mapInit[0]));

  }

  valueMap::valueMap(const Iter first, const Iter last)
  {
	  std::cout << "valueMap constructor(first,last) with" << std::endl;
	  Iter i = first;
		do { 
	  std::cout << i->first << " " << i->second << std::endl;
		++i;
		} while (i != last);
    std::cout << "insert in values with" << std::endl;
    printValueMap();
    values.insert(first, last);
		std::cout << "inserted" << std::endl;
  }

	void valueMap::printValueMap()
	{
	  ValuesDescList::const_iterator i=values.begin();
		do {
      std::cout << i->first << " " << i->second << std::endl;
      ++i;
    } while (i != values.end());
	}

}

valueTypes::valueMap::ValuesDescList valueTypes::valueMap::values(myBase::v_mapInit, myBase::v_mapInitEnd);
