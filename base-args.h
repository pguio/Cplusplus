
#ifndef BASE_ARGS_H
#define BASE_ARGS_H

class Base {
public:
  typedef std::string BASE_KEY_TYPE;

  explicit Base(int nargs=0, char *args[]=0);
  virtual ~Base();

  virtual void whoami();
};


#endif // BASE_ARGS_H
