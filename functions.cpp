

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <typeinfo>
#include <bench.h>

namespace fun {
  inline double f1(double x)
  {
    return x*x;
  }
  inline double f2(double x)
  {
    return exp(-x*x);
  }
  inline double f3(double x)
  {
    return x*exp(-x*x);
  }
  enum funcEnums { func1=1, func2, func3 };
}

struct Functions {
  double f1(double x) const
  {
    return fun::f1(x);
  }
  double f2(double x) const
  {
    return fun::f2(x);
  }
  double f3(double x) const
  {
    return fun::f3(x);
  }
  Functions(int nargs, char *args[])
    : funId(nargs>1 ? atoi(args[1]) : fun::func1)
  {
    if (funId < fun::func1 || funId > fun::func3) {
      std::cerr << "Exception in Function1: funId=" << funId
                << " not registered" << std::endl;
      throw !0;
    }
  }
  int funId;
};


class Function1 : protected Functions {
public:
  Function1(int nargs, char *args[]) : Functions(nargs, args) {}
  double get (double x) const
  {
    switch (funId) {
    case fun::func1:
      return f1(x);
    case fun::func2:
      return f2(x);
    case fun::func3:
      return f3(x);
    default:
      std::cerr << "funId="<< funId << " not registered" << std::endl;
      throw !0;
    }
  }
  double operator()(double x) const
  {
    switch (funId) {
    case fun::func1:
      return f1(x);
    case fun::func2:
      return f2(x);
    case fun::func3:
      return f3(x);
    default:
      std::cerr << "funId="<< funId << " not registered" << std::endl;
      throw !0;
    }
  }
};

class Function2 : protected Functions {
public:
  Function2(int nargs, char *args[]) : Functions(nargs, args), f(0)
  {
    switch (funId) {
    case fun::func1:
      f = &Function2::f1;
      break;
    case fun::func2:
      f = &Function2::f2;
      break;
    case fun::func3:
      f = &Function2::f3;
      break;
    }
  }
  double get
  (double x) const
  {
    return (this->*f)(x);
  }
  double operator()(double x) const
  {
    return (this->*f)(x);
  }
private:
  double (Function2::*f)(double x) const ;
};

class Function3 : protected Functions {
public:
  Function3(int nargs, char *args[]) : Functions(nargs, args), f()
  {
    f[1] = &Function3::f1;
    f[2] = &Function3::f2;
    f[3] = &Function3::f3;
  }
  double get
  (double x) const
  {
    return (this->*f[funId])(x);
  }
  double operator()(double x) const
  {
    return (this->*f[funId])(x);
  }
private:
  double (Function3::*f[fun::func3+1])(double x) const ;
};

class Function4 : protected Functions {
public:
  Function4(int nargs, char *args[]) : Functions(nargs, args), f()
  {
    f[fun::func1] = &Function4::f1;
    f[fun::func2] = &Function4::f2;
    f[fun::func3] = &Function4::f3;
  }
  double get
  (double x) const
  {
    flist::const_iterator i = this->f.find(funId);
    return (this->*(i->second))(x);
  }
  double operator()(double x) const
  {
    flist::const_iterator i = this->f.find(funId);
    return (this->*(i->second))(x);
  }
private:
  typedef std::map<int, double (Function4::*)(double) const> flist;
  flist f;
};


// Functionoid
#include <factory.h>
struct Funoid {
  virtual ~Funoid() {}
  virtual double doit(double x) const = 0;
};

struct Funoid1 : Funoid {
  virtual double doit(double x) const
  {
    return fun::f1(x);
  }
};
RegisterInFactory<Funoid, Funoid1, int> r1(1);

struct Funoid2 : Funoid {
  virtual double doit(double x) const
  {
    return fun::f2(x);
  }
};
RegisterInFactory<Funoid, Funoid2, int> r2(2);

struct Funoid3 : Funoid {
  virtual double doit(double x) const
  {
    return fun::f3(x);
  }
};
RegisterInFactory<Funoid, Funoid3, int> r3(3);

class Function5 {
public:
  typedef GenericFactory<Funoid, int> Factory;
  Function5(int nargs, char *args[]) :
    fun(Factory::instance().create(nargs>1 ? atoi(args[1]) : fun::func1))
  {
  }
  double get (double x) const
  {
    return fun->doit(x);
  }
  double operator()(double x) const
  {
    return fun->doit(x);
  }
private:
  Factory::BasePtr fun;
};


namespace bench {

  double x;

  template <class Function>
  struct Test1 : bench::Test {
    explicit Test1(Function _function) : function(_function) {}
    void op()
    {
      x = 0.0;
      function.get(x);
    }
    std::string opName() const
    {
      std::string s(typeid(function).name());
      s.append("::get()");
      return s;
    }
    Function function;
  };

  template <class Function>
  struct Test2 : bench::Test {
    explicit Test2(Function _function) : function(_function) {}
    void op()
    {
      x = 0.0;
      function(x);
    }
    std::string opName() const
    {
      std::string s(typeid(function).name());
      s.append("()     ");
      return s;
    };
    Function function;
  };

}


int main(int nargs, char *args[])
{
  try {

    double minTime = 2.0;
    bench::verbose = true;

    Function1 f1(nargs, args);
    Function2 f2(nargs, args);
    Function3 f3(nargs, args);
    Function4 f4(nargs, args);
    Function5 f5(nargs, args);

    {
      bench::Test1<Function1> T1(f1);
      bench::Test1<Function2> T2(f2);
      bench::Test1<Function3> T3(f3);
      bench::Test1<Function4> T4(f4);
      bench::Test1<Function5> T5(f5);
      bench::benchClassOp(T1, minTime);
      bench::benchClassOp(T2, minTime);
      bench::benchClassOp(T3, minTime);
      bench::benchClassOp(T4, minTime);
      bench::benchClassOp(T5, minTime);
    }

    {
      bench::Test2<Function1> T1(f1);
      bench::Test2<Function2> T2(f2);
      bench::Test2<Function3> T3(f3);
      bench::Test2<Function4> T4(f4);
      bench::Test2<Function5> T5(f5);
      bench::benchClassOp(T1, minTime);
      bench::benchClassOp(T2, minTime);
      bench::benchClassOp(T3, minTime);
      bench::benchClassOp(T4, minTime);
      bench::benchClassOp(T5, minTime);
    }

  }
  catch (int status) {
    return status;
  }
}


