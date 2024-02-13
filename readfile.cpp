
#include <fstream>
#include <iostream>
#include <exception>
#include <string>

using std::cout;
using std::ifstream;
using std::string;

int main()
{
  try {

    const char filename[] = __FILE__;

    {
      // Character by character
      ifstream id(filename);
      if (! id.is_open())
        throw string(filename);
      char c;
      while ( !id.eof() ) {
        id.get(c);
        cout << c ;
      }
      id.close();
    }

    {
      // Line by line
      // there is no "nocreate" in StdC++ :(
      // ios::in is default
      ifstream id(filename);
      if (! id.is_open())
        throw string(filename);
      // automatic memory management, also doesn't overflow
      string str;
      // fixes the usual eof() bug
      while(getline(id, str)) {
        cout << "length " << str.length() << " @" << str << "@\n";
      }
      // id is closed automatically no need for id.close();
    }


    {
      // Line by line
      ifstream id;
      id.open(filename);
      if (! id.is_open())
        throw string(filename);
      string str;
      while (! id.eof()) {
        getline(id, str);
        cout << "length " << str.length() << " @" << str << "@\n";
      }
      id.close();
    }

    return 0;

  }
  catch (string &filename) {

    std::cerr << " ** Error : " << filename << " not found." << std::endl;
    return !0;

  }
}
