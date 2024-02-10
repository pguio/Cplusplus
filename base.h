
#ifndef BASE_H
#define BASE_H

class Base {
public:
  typedef std::string BASE_KEY_TYPE;

  Base();
  virtual ~Base();

  virtual void whoami();
};


#endif
