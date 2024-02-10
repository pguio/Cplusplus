
#ifndef DERIVED_H

#include "base.h"

class Derived : public Base {
public:
  Derived();
  virtual ~Derived();

  virtual void whoami();
};


#endif
