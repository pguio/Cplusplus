

#include <iostream>
#include <map>
#include <bench.h>

using std::cerr;
using std::endl;

#if defined(HAVE_BLITZ)

#include <blitz/array.h>

using namespace blitz;
using namespace blitz::tensor;


struct  Functions {
  enum funcEnums { func1=1, func2, func3 };
  typedef Array<double,2> Array2d;
  void f1(Array2d &x) const {
    x=temin;
  }
  void f2(Array2d &x) const {
    int ny = x.cols();
    int jst(x.lbound(secondDim));
    x = dte*exp(-pow2(2.0*(j-jst)/(ny-1)-1.0)/(2.0*stdte2))+temin;
  }
  void f3(Array2d &x) const {
    int nx = x.rows();
    int ist = x.lbound(firstDim);
    x = dte*exp(-pow2(2.0*(i-ist)/(nx-1)-1.0)/(2.0*stdte2))+temin;
  }
  Functions(int nargs, char *args[])
    : funId(nargs>1 ? atoi(args[1]) : func1), temin(2.0), dte(2.0), stdte2(0.25) {
    if (funId<func1 || funId>func3) {
      cerr << "Exception in Function1: funId not registered" << endl;
      throw !0;
    }
  }
  int funId;
  double temin, dte, stdte2;
};


class Function1 : protected Functions {
public:
  Function1(int nargs, char *args[]) : Functions(nargs, args) {}
  void get
  (Array2d &x) const {
    switch (funId) {
    case func1:
      f1(x);
      return;
    case func2:
      f2(x);
      return;
    case func3:
      f3(x);
      return;
    }
  }
  void operator()(Array2d &x) const {
    switch (funId) {
    case func1:
      f1(x);
      return;
    case func2:
      f2(x);
      return;
    case func3:
      f3(x);
      return;
    }
  }
};

class Function2 : protected Functions {
public:
  Function2(int nargs, char *args[]) : Functions(nargs, args), f() {
    switch (funId) {
    case func1:
      f = &Function2::f1;
      break;
    case func2:
      f = &Function2::f2;
      break;
    case func3:
      f = &Function2::f3;
      break;
    }
  }
  void get
  (Array2d &x) const {
    (this->*f)(x);
  }
  void operator()(Array2d &x) const {
    (this->*f)(x);
  }
private:
  void (Function2::*f)(Array2d &x) const;
};

class Function3 : protected Functions {
public:
  Function3(int nargs, char *args[]) : Functions(nargs, args), f() {
    f[1] = &Function3::f1;
    f[2] = &Function3::f2;
    f[3] = &Function3::f3;
  }
  void get
  (Array2d &x) const {
    (this->*f[funId])(x);
  }
  void operator()(Array2d &x) const {
    (this->*f[funId])(x);
  }
private:
  void (Function3::*f[func3+1])(Array2d &x) const;
};

class Function4 : protected Functions {
public:
  Function4(int nargs, char *args[]) : Functions(nargs, args), f() {
    f[func1] = &Function4::f1;
    f[func2] = &Function4::f2;
    f[func3] = &Function4::f3;
  }
  void get
  (Array2d &x) const {
    flist::const_iterator i = this->f.find(funId);
    (this->*(i->second))(x);
  }
  void operator()(Array2d &x) const {
    flist::const_iterator i = this->f.find(funId);
    (this->*(i->second))(x);
  }
private:
  typedef std::map<int, void (Function4::*)(Array2d &) const> flist;
  flist f;
};


// Functionoid
#include <factory.h>
struct Funoid {
  typedef Array<double,2> Array2d;
  Funoid() : temin(2.0), dte(2.0), stdte2(0.25) {}
  virtual ~Funoid() {}
  virtual void doit(Array2d & x) const = 0;
  double temin, dte, stdte2;
};

struct Funoid1 : Funoid {
  virtual void doit(Array2d &x) const {
    x=temin;
  }
};
RegisterInFactory<Funoid, Funoid1, int> r1(1);

struct Funoid2 : Funoid {
  virtual void doit(Array2d &x) const {
    int ny = x.cols();
    int jst(x.lbound(secondDim));
    x = dte*exp(-pow2(2.0*(j-jst)/(ny-1)-1.0)/(2.0*stdte2))+temin;
  }
};
RegisterInFactory<Funoid, Funoid2, int> r2(2);

struct Funoid3 : Funoid {
  void doit(Array2d &x) const {
    int nx = x.rows();
    int ist = x.lbound(firstDim);
    x = dte*exp(-pow2(2.0*(i-ist)/(nx-1)-1.0)/(2.0*stdte2))+temin;
  }
};
RegisterInFactory<Funoid, Funoid3, int> r3(3);

class Function5 {
public:
  typedef Funoid::Array2d Array2d;
  typedef GenericFactory<Funoid, int> Factory;
  Function5(int nargs, char *args[]) :
    fun(Factory::instance()
        .create(nargs>1 ? atoi(args[1]) : Functions::func1)) {}
  void get (Array2d & x) const {
    fun->doit(x);
  }
  void operator()(Array2d & x) const {
    fun->doit(x);
  }
private:
  GenericFactory<Funoid, int>::BasePtr fun;
};


namespace bench {

  const int nx = 10;
  const int ny = 10;
  Functions::Array2d x(nx, ny);

  template <class Function>
  struct Test1 : bench::Test {
    explicit Test1(Function _function) : function(_function) {}
    void op() {
      x = 0.0;
      function.get(x);
    }
    std::string opName() const {
      std::string s(typeid(function).name());
      s.append("::get()");
      return s;
    }
    Function function;
  };

  template <class Function>
  struct Test2 : bench::Test {
    explicit Test2(Function _function) : function(_function) {}
    void op() {
      x = 0.0;
      function(x);
    }
    std::string opName() const {
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

  } catch (int status) {
    return status;
  }
}

#else

int main(int nargs, char *args[])
{
  cerr << args[0] << ": Blitz test not available\n";
}

#endif
