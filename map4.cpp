
#include <map>
#include <string>
#include "bench.h"

typedef std::map<int, std::string> lut;
typedef lut::value_type pair;

namespace one {

  struct test1 : bench::Test {
    void op() {
      lut a;
      a.insert(pair(1,"foo1"));
    }
    std::string opName() const {
      return "map(); map.insert(key,value)";
    }
  };
  struct test2 : bench::Test {
    void op() {
      lut a;
      a[1]="foo1";
    }
    std::string opName() const {
      return "map(); map[key]=value       ";
    }
  };

}

namespace two {

  lut a;
  struct test1 : bench::Test {
    void op() {
      a.insert(pair(1,"foo1"));
    }
    std::string opName() const {
      return "map.insert(key,value)       ";
    }
  };

  struct test2 : bench::Test {
    void op() {
      a[1]="foo1";
    }
    std::string opName() const {
      return "map[key]=value              ";
    }
  };

}

namespace three {

  const int n=1000;

  struct test1 : bench::Test {
    void op() {
      lut a;
      for (int i=0; i<n; ++i)
        a.insert(pair(i,"foo1"));
    }
    std::string opName() const {
      return "1000 x map.insert(key,value)";
    }
  };

  struct test2 : bench::Test {
    void op() {
      lut a;
      for (int i=0; i<n; ++i)
        a[i] = "foo1";
    }
    std::string opName() const {
      return "1000 x map[key]=value       ";
    }
  };

}

int main()
{
  const double minTime = 1.0;
  bench::verbose = true;

  {
    one::test1 t1;
    bench::benchClassOp(t1, minTime);
    one::test2 t2;
    bench::benchClassOp(t2, minTime);
  }

  {
    two::test1 t1;
    bench::benchClassOp(t1, minTime);
    two::test1 t2;
    bench::benchClassOp(t2, minTime);
  }

  {
    three::test1 t1;
    bench::benchClassOp(t1, minTime);
    three::test2 t2;
    bench::benchClassOp(t2, minTime);
  }

  return 0;
}
