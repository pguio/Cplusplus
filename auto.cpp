
#include <vector>
#include <iostream>

// https://stackoverflow.com/questions/15927033/what-is-the-correct-way-of-using-c11s-range-based-for

// A sample test class, with custom copy semantics.
class X {
public:
  X()
    : m_data(0)
  {}

  X(int data)
    : m_data(data)
  {}

  ~X()
  {}

  X(const X& other)
    : m_data(other.m_data)
  {
    std::cout << "X copy ctor.\n";
  }

  X& operator=(const X& other)
  {
    m_data = other.m_data;
    std::cout << "X copy assign.\n";
    return *this;
  }

  int Get() const
  {
    return m_data;
  }

private:
  int m_data;
};

std::ostream& operator<<(std::ostream& os, const X& x)
{
  os << x.Get();
  return os;
}

int main()
{
  {
    std::vector<int> v = {1, 3, 5, 7, 9};

    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << std::endl;

  }

  {
    std::vector<X> v = {1, 3, 5, 7, 9};

    std::cout << "\nElements:\n";
    for (auto x : v) {
      std::cout << x << ' ';
    }
    std::cout << std::endl;
    for (const auto& x : v) {
      std::cout << x << ' ';
    }
    std::cout << std::endl;
  }

}
