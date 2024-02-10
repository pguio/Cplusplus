#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

class Foo {
private:
  struct Conf {
    int field1;
    double field2;
    const char *field3;
    Conf() :  field1(1), field2(20.0), field3("coucou")
    {}
  };
  friend ostream& operator<<(ostream& os, const Conf &conf);
  virtual void printOn(ostream& os) const;
protected:
  Conf conf;
  friend ostream& operator<<(ostream& os, const Foo &foo);
public:
  Foo () : conf()
  {}
  virtual ~Foo ()
  {}
};

inline
ostream& operator<<(ostream& os, const Foo::Conf &conf)
{
  os << "field1=" << conf.field1 << endl;
  os << "field2=" << conf.field2 << endl;
  os << "field3=" << conf.field3 << endl;
  return os;
}

void Foo::printOn(ostream& os) const
{
  os << conf;
}

inline
ostream& operator<<(ostream& os, const Foo &foo)
{
  foo.printOn(os);
  return os;
}

class FooFoo : public Foo {
private:
  struct ConfAll {
    int field4;
    const char *field5;
    ConfAll() :  field4(1), field5("bonjour")
    {}

  };
  ConfAll confall;
  friend ostream& operator<<(ostream& os, const ConfAll &confall);
  virtual void printOn(ostream& os) const;
public:
  friend ostream& operator<<(ostream& os, const FooFoo &foofoo);
};

inline
ostream& operator<<(ostream& os, const FooFoo::ConfAll &confall)
{
  os << "field4=" << confall.field4 << endl;
  os << "field5=" << confall.field5 << endl;
  return os;
}

void FooFoo::printOn(ostream& os) const
{
  os << conf;
  os << confall;
}

inline
ostream& operator<<(ostream& os, const FooFoo &foofoo)
{
  foofoo.printOn(os);
  return os;
}

int main()
{
  Foo foo;
  std::ofstream fid("overload.dat");

  cout << "foo\n" << foo;
  fid << "foo\n" << foo;

  FooFoo foofoo;
  cout << "foofoo\n" << foofoo;
  fid << "foofoo\n" << foofoo;

  vector<Foo *> foolist;
  foolist.insert(foolist.end(), new Foo);
  foolist.insert(foolist.end(), new FooFoo);
  vector<Foo *>::iterator i=foolist.begin();
  vector<Foo *>::iterator last=foolist.end();
  int index = 0;
  for (; i!=last; ++i) {
    cout << "\nindex " << index++ << endl;
    cout << **i << endl;
  }

  return 0;
}

