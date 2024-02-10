
#if defined(HAVE_EIGEN)

#include <iostream>
#include <Eigen/Core>
// import most common Eigen types
using namespace Eigen;

int main(int, char *[])
{
  Matrix3f m3;
  m3 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  Matrix4f m4 = Matrix4f::Identity();
  Vector4i v4(1, 2, 3, 4);

  std::cout << "m3\n" << m3 << "\nm4:\n"
            << m4 << "\nv4:\n" << v4 << std::endl;

  // matrix being constructed by blocks
  Matrix4f m;
  m << Matrix2f::Identity(),             Matrix2f::Zero(),
  (Matrix2f()<<1,2,3,4).finished(), Matrix2f::Identity();

  std::cout << "m\n" << m << std::endl;



  return 0;
}

#else

#include <iostream>

int main()
{
  std::cout << "EIGEN not available." << std::endl << std::endl;
}

#endif
