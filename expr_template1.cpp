
#include <iostream>

namespace {

  struct plus { // Represents addition
    static double apply(double a, double b)
    {
      return a+b;
    }
  };

  struct mult { // Represents addition
    static double apply(double a, double b)
    {
      return a*b;
    }
  };


// X represents a node in the parse tree
  template <typename Left, typename Op, typename Right>
  struct X {
    Left leftNode_;
    Right rightNode_;
    X(Left t1, Right t2) : leftNode_(t1), rightNode_(t2)
    {}
    double operator[](int i)
    {
      return Op::apply(leftNode_[i],rightNode_[i]);
    }
  };

  struct Array { // some array class
    Array(double* data, int N) : data_(data), N_(N)
    {}
    // Assgn an expression to the array
    template <typename Left, typename Op, typename Right>
    void operator=(X<Left,Op,Right> expr)
    {
      for (int i=0; i<N_; ++i)
        data_[i] = expr[i];
    }
    double operator[](int i)
    {
      return data_[i];
    }
    double *data_;
    int N_;
  };

// The overloaded operator which does parsing for
// expressions of the form "A+B+C+D+..."
  template<class Left,class Right>
  X<Left, plus, Right> operator+(Left a, Right b)
  {
    return X<Left, plus, Right>(a, b);
  }

  template<class Left,class Right>
  X<Left, mult, Right> operator*(Left a, Right b)
  {
    return X<Left, mult, Right>(a, b);
  }

}

int main()
{
  double a_data[] = { 2, 3, 5, 9},
                    b_data[] = { 1, 0, 0, 1},
                               c_data[] = { 3, 0, 2, 5},
                                          d_data[4];

  Array A(a_data,4), B(b_data,4), C(c_data,4), D(d_data,4);
  D = A + B + C;
  for (int i=0; i<4; ++i)
    std::cout << D[i] << " ";
  std::cout << std::endl;
  D = A + B * C;
  for (int i=0; i<4; ++i)
    std::cout << D[i] << " ";
  std::cout << std::endl;

  return 0;
}
