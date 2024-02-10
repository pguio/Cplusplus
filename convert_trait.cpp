#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

template <class _Tp>
struct typeClass_base {
  static const string typeName;
  static string name() {
    return typeName;
  }
};


const string typeClass_base<bool>::typeName = "boolean";
const string typeClass_base<char>::typeName = "character";
const string typeClass_base<int>::typeName = "integer";
const string typeClass_base<char*>::typeName = "string";
const string typeClass_base<string>::typeName = "string";
const string typeClass_base<float>::typeName = "real";
const string typeClass_base<double>::typeName = "real";


const string typeClass_base<vector<bool> >::typeName = "vector<"+typeClass_base<bool>::typeName+">";
const string typeClass_base<vector<char> >::typeName = "vector<"+typeClass_base<char>::typeName+">";
const string typeClass_base<vector<int> >::typeName = "vector<"+typeClass_base<int>::typeName+">";
const string typeClass_base<vector<char*> >::typeName = "vector<"+typeClass_base<char*>::typeName+">";
const string typeClass_base<vector<string> >::typeName = "vector<"+typeClass_base<string>::typeName+">";
const string typeClass_base<vector<float> >::typeName = "vector<"+typeClass_base<float>::typeName+">";
const string typeClass_base<vector<double> >::typeName = "vector<"+typeClass_base<double>::typeName+">";

template <class _Tp>
_Tp string_cast(const string & str)
{
  istringstream iss(str);
  _Tp res;
  iss >> res;
  return res;
}

struct typeClass {
  virtual ~typeClass() {}
  virtual string name() = 0;
};

template <class _Tp>
struct type : typeClass_base<_Tp> {
  static _Tp convert(const string & str) throw(string &) {
    stringstream iss;
    iss << str;
    //    iss.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
    iss.exceptions(ifstream::failbit | ifstream::badbit);
    _Tp res(0);

    try {
      //		cout << "iss.str()='" << iss.str() << "'" << " eof()=" << iss.eof() << endl;
      iss >> res;
      //		cout << "iss.str()='" << iss.str() << "'" << " eof()=" << iss.eof() << endl;
      if (iss.eof())
        return res;
      else
        throw string("string "+iss.str()+" could not be converted to "+name());
    } catch (ifstream::failure & e) {
      cout << e.what() << endl;
    }
  }
};

template<>
struct type<bool> : typeClass_base<bool> {
  static bool convert(const string & str) throw(string &) {
    if (!str.compare(0, str.npos, "yes") ||
        !str.compare(0, str.npos, "true") ||
        !str.compare(0, str.npos, "1"))
      return true;
    if (!str.compare(0, str.npos,  "no") ||
        !str.compare(0, str.npos, "false") ||
        !str.compare(0, str.npos, "0"))
      return false;
    throw string("string "+str+" could not be converted to "+name());
  }
};

template<>
struct type<char> : typeClass_base<char> {
  static char convert(const string & str) {
    return *str.c_str();
  }
};

template<>
struct type<char*> : typeClass_base<char*> {
  static char *convert(const string & str) {
    return strdup(str.c_str());
  }
};

template<>
struct type<string> : typeClass_base<string> {
  static string convert(const string & str) {
    return string(str);
  }
};

template <class T>
struct type< std::vector<T> > : typeClass_base<vector<T> > {
  static vector<T> convert(string str) throw(string &) {
    try {
      vector<T> vec(0);
      string::size_type e;
      while ( (e=str.find(',')) != str.npos ) {
        string sstr = str.substr(0,e);
        vec.push_back(type<T>::convert(sstr));
        str.erase(0, e+1);
      }
      vec.push_back(type<T>::convert(str));
      return vec;
    } catch (string & error) {
      error.append("\nstring "+str+" could not be converted to "+name());
      throw error;
    }
  }
};


template<class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v)
{
  if ( !v.empty() ) {
    typename std::vector<T>::const_iterator i = v.begin();
    typename std::vector<T>::const_iterator end = v.end();
    os << *i;
    for ( ++i; i != end; ++i )
      os << ',' << *i;
  }
  return os;
}


template <class T>
void test(const string & s)
{
  cout << "s=" << s << "\ttype=" << type<T>::name() << " converted " << type<T>::convert(s) << endl;
}

template <class T>
void test(const string & s, const type<T> & type)
{
  cout << "s=" << s << "\ttype=" << type.name() << " converted " << type.convert(s) << endl;
}

int main()
{
  try {

    test<bool>("true");
    test<char>("c");
    test<char*>("abc");
    test<string>("abc");
    test<int>("2004");
    test< vector<bool> >("1,1,0,0");
    test< vector<string> >("ab,cd,ef,gh");
    test< vector<float> >("1,1.1,-1e-3,4.2e+4");

    test("true", type<bool>());
    test("c", type<char>());
    test("abc", type<char*>());
    test("abc", type<string>());
    test("2004", type<int>());
    test("1,1,0,0", type<vector<bool> >());
    test("ab,cd,ef,gh", type<vector<string> >());
    test("1a,1.1,-1e-3,4.2e+4", type<vector<float> >());


    map<int, typeClass*> m;
    m[1] = new type<bool>();


  } catch (string &error) {
    cout << error << endl;
  }
}
