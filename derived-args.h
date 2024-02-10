
#ifndef DERIVED_H

#include "base-args.h"

class Derived : public Base {
public:
  explicit Derived(int nargs=0, char *args[]=0);
  virtual ~Derived();

  virtual void whoami();
};


#endif
