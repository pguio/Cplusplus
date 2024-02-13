
#include <memory>
#include <iostream>

using std::cout;
using std::endl;

// https://softwareengineering.stackexchange.com/questions/291141/how-to-handle-design-changes-for-auto-ptr-deprecation-in-c11
#if __cplusplus >= 201103L
template <typename T>
using auto_ptr = std::unique_ptr<T>;
#else
using std::auto_ptr;
#endif

class MyClass {
public:
  MyClass()
  {
    cout << "I am created" << endl;
  }
  ~MyClass()
  {
    cout << "I am destroyed" << endl;
  }
  void DoSomething()
  {
    cout << "I am doing something" << endl;
  }
};

int main()
{
  {
    MyClass* p(new MyClass);
    p->DoSomething();
    delete p;
    cout << endl;
  }

  {
    auto_ptr<MyClass> p(new MyClass);
    p->DoSomething();
    cout << endl;
  }

  {
    MyClass* p(new MyClass);
    MyClass* q = p;
    delete p;
    p->DoSomething(); // Watch out! p is now dangling
    p = 0; // p is no longer dangling
    q->DoSomething(); // Ouch! q is still dangling!
  }

  return 0;
}
