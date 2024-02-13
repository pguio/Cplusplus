
#include <enum.h>



namespace valueTypes {

namespace myExtra {

  const int boolVecR = 100;
  const int intVecR  = 101;
  const int realVecR = 102;

    valueMap::ValueDescPair v_mapInit[] = {
      valueMap::ValueDescPair(boolVecR      , "bool[3]"),
      valueMap::ValueDescPair(intVecR       ,  "int[3]"),
      valueMap::ValueDescPair(realVecR      , "real[3]")
    };

    valueMap::ValueDescPair *v_mapInitEnd(v_mapInit+
                                          sizeof(v_mapInit)/sizeof(v_mapInit[0]));

		//valueMap::ValuesDescList valueMap::values(v_mapInit, v_mapInitEnd);
		}
		valueMap registerMe(myExtra::v_mapInit, myExtra::v_mapInitEnd);

}

using namespace valueTypes;


int main()
{
  {
	  std::cout << "printValueMap() in main()" << std::endl;
	  valueMap::printValueMap();
/*
    valueMap::ValuesDescList::const_iterator i=valueMap::values.begin();
    do {
      std::cout << i->first << " " << i->second << std::endl;
      ++i;
    } while (i != valueMap::values.end());
*/		
  }
  return 0;
}
