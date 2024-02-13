
#include <iostream>
#include <vector>

using std::boolalpha;
using std::cerr;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;

#if defined(HAVE_BLITZ)
#include <blitz/array.h>
#endif

template<class T>
ostream& operator<<(ostream &os, const vector<T> &v)
{
  if (!v.empty()) {
    typename vector<T>::const_iterator i = v.begin();
    typename vector<T>::const_iterator end = v.end();
    os << *i;
    for ( ++i; i != end; ++i ) os << ',' << *i;
  }
  return os;
}

#include <parser2.h>
using namespace parser;

static const char *package = "Parser";
static const char *ver = "1.0";
static const char *copyright =
  "Copyright (c) 2000-2011 Patrick Guio <patrick.guio@gmail.com>\n\n"
  "This is free software; see the source for copying conditions.  There is NO\n"
  "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";

class Foo : public parser::Parser {
public:
  enum { val1, val2, val3 };

  typedef Parser::LUT LUT;
  typedef Parser::LUTPair Pair;

  Foo(int nargs, char *args[]);
  ~Foo()
  {}

  void parseParameters();
  friend ostream& operator<<(ostream &os, const Foo &foo);

private:

  bool Boolean;
  char Character;
  char *String;
  int Integer;
  int Enum;
  float Float;
  double Double;
  vector<bool> VectBool;
  vector<char> VectChar;
  vector<char*> VectStr;
  vector<int> VectInt;
  vector<double> VectDouble;
  vector<std::string> DirList;
#if defined(HAVE_BLITZ)
  blitz::TinyVector<float,3> RealVec3;
  blitz::Array<float,1> RealArray1d;
#endif

  static LUT Enum_map;
};

const Foo::Pair enum_map[] = {
  Foo::Pair(Foo::val1, "val1"),
  Foo::Pair(Foo::val2, "val2"),
  Foo::Pair(Foo::val3, "val3")
};

Foo::LUT Foo::Enum_map(enum_map, enum_map+3);

class Test {
public:
  explicit Test(int value) : val(value), allowed(enum_map, enum_map+3)
  {}
  ~Test()
  {}
  void run()
  {
    if (allowed.find(val) == allowed.end()) {
      std::map<int, std::string>::const_iterator i(allowed.begin());
      std::string msg("Parameter should be "+ i->second);
      for (++i; i!=allowed.end(); ++i)
        msg += ", " + i->second;
      throw ParserException(msg);
    }
  }
private:
  int val;
  std::map<int, std::string> allowed;
};

Foo::Foo(int nargs, char *args[]) : Parser(nargs, args),
  Boolean(false), Character('\0'), String((char*)"coucou"),
  Integer(1), Enum(val1), Float(2.0), Double(2.3),
  VectBool(0), VectChar(0), VectStr(0), VectInt(0), VectDouble(0),
  DirList(0)
#if defined(HAVE_BLITZ)
  , RealVec3(0.0), RealArray1d(0)
#endif
{
  using namespace parser::types;

  Parser::registerClass("Foo");
  Parser::registerPackage(package, ver, copyright);

  Parser::insertOption("--boolean", boolean, "Parse a boolean", Any(Boolean));
  Parser::insertOptionAlias("--boolean","boolean");

  Parser::insertOption("--character", character, "Parse a character", Any(Character));
  Parser::insertOptionAlias("--character", "character");

  Parser::insertOption("--string", charStr, "Parse a string", Any(String));
  Parser::insertOptionAlias("--string","string");

  Parser::insertOption("--integer", integer, "Parse an integer", Any(Integer));
  Parser::insertOptionAlias("--integer","integer");

  Parser::insertOption("int_enum", integer, "Parse an int_enum", Any(Enum));

  Parser::insertOption("real32", real, "Parse a float", Any(Float));
  Parser::insertOption("real64", real, "Parse a double", Any(Double));

  Parser::insertOption("vectbool", boolVect, "Parse a vector of boolean", Any(VectBool));
  Parser::insertOption("vectchar", charVect, "Parse a vector of character", Any(VectChar));
  Parser::insertOption("vectstr", stringVect, "Parse a vector of string", Any(VectStr));
  Parser::insertOption("vectint", intVect, "Parse a vector of integer", Any(VectInt));
  Parser::insertOption("vectdouble", realVect, "Parse an array of double", Any(VectDouble));

  Parser::insertOption("-I", charStr, "Parse include directories",Any(DirList));

#if defined(HAVE_BLITZ)
  Parser::insertOption("realvec3", realVect, "Parse blitz::TinyVector<float,3>",Any(RealVec3));
  Parser::insertOption("realarray1d", realVect, "Parse blitz::Array<float,1>",Any(RealArray1d));
#endif
}

void Foo::parseParameters()
{
  if (Parser::parseOption("--boolean",Boolean))
    cout << "Boolean    = " << boolalpha << Boolean << " parsed." << endl;
  if (Parser::parseOption("--character",Character))
    cout << "Character  = " << Character << " parsed." << endl;
  if (Parser::parseOption("--string",String))
    cout << "String     = " << String << " parsed." << endl;
  if (Parser::parseOption("--integer",Integer))
    cout << "Integer    = " << Integer << " parsed." << endl;
  if (Parser::parseOption<int,Test>("int_enum",Enum))
    cout << "Enum       = " << parser::map_elt(Enum_map,Enum) << endl;
  if (Parser::parseOption("real32",Float))
    cout << "Float      = " << Float << " parsed." << endl;
  if (Parser::parseOption("real64",Double))
    cout << "Double     = " << Double << " parsed." << endl;
  if (Parser::parseOption("vectbool",VectBool))
    cout << "VectBool   = " << VectBool << " parsed." << endl;
  if (Parser::parseOption("vectchar",VectChar))
    cout << "VectChar   = " << VectChar << " parsed." << endl;
  if (Parser::parseOption("vectstr",VectStr))
    cout << "VectStr    = " << VectStr << " parsed." << endl;
  if (Parser::parseOption("vectint",VectInt))
    cout << "VectInt    = " << VectInt << " parsed." << endl;
  if (Parser::parseOption("vectdouble",VectDouble))
    cout << "VectDouble = " << VectDouble << " parsed." << endl;
  if (Parser::parseOptions("-I",DirList))
    cout << "DirList = " << DirList << " parsed." << endl;
#if defined(HAVE_BLITZ)
  if (Parser::parseOption("realvec3",RealVec3))
    cout << "RealVec3 = " << RealVec3 << " parsed." << endl;
  if (Parser::parseOption("realarray1d",RealArray1d))
    cout << "RealVec3 = " << RealArray1d << " parsed." << endl;
#endif
}

ostream& operator<<(ostream &os, const Foo &foo)
{
  return os << header("Foo set up")
         << "Boolean    = " << yesno(foo.Boolean) << '\n'
         << "Character  = " << foo.Character << '\n'
         << "String     = " << foo.String << '\n'
         << "Integer    = " << foo.Integer << '\n'
         << "Enum       = " << parser::map_elt(foo.Enum_map,foo.Enum) << '\n'
         << "Float      = " << foo.Float << '\n'
         << "Double     = " << foo.Double << '\n'
         << "VectBool   = " << foo.VectBool << '\n'
         << "VectChar   = " << foo.VectChar << '\n'
         << "VectStr    = " << foo.VectStr << '\n'
         << "VectInt    = " << foo.VectInt << '\n'
         << "VectDouble = " << foo.VectDouble << '\n'
         << "DirList    = " << foo.DirList << '\n'
#if defined(HAVE_BLITZ)
         << "RealVec3   = " << foo.RealVec3 << '\n'
         << "RealVec3   = " << foo.RealArray1d << '\n'
#endif
         << "**********";
}


int main(int nargs, char *args[])
{
  try {

    parser::Parser parser(nargs, args);
    parser.registerProgram(args[0]);
    parser.registerPackage(package, ver, copyright);

    Foo foo(nargs, args);

    if (parser.parseHelp()) {
      foo.parseHelp();
      return 0;
    }

    if (parser.parseVersion()) {
      foo.parseVersion();
      return 0;
    }

    if (parser.parseTemplate()) {
      foo.parseTemplate();
      return 0;
    }

    parser.printCmd(cout);

    parser.viewArgs(cout);
    foo.viewArgs(cout);

    foo.parseParameters();

    cout << foo << endl;

    return 0;

  }
  catch (ClassException& e) {
    cerr << e.what() << endl;
    return !0;
  }
}
