
#include <iostream>

namespace {

  struct plus
    { }; // Represents addition

// X represents a node in the parse tree
  template <typename Left, typename Op, typename Right>
  class X
  { };

  struct Array { // some array class
    template <typename Left, typename Op, typename Right>
    void operator=(X<Left,Op,Right> exp) {
      std::cout << "operator=" << std::endl;
    }
  };

// The overloaded operator which does parsing for
// expressions of the form "A+B+C+D+..."
  template<class T>
  X<T, plus, Array> operator+(T, Array)
  {
    std::cout << "operator+" << std::endl;
    return X<T, plus, Array>();
  }

}

int main()
{
  Array A, B, C, D;
  D = A + B + C;
  return 0;
}

