
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

#include <bench.h>

#if defined(HAVE_BLITZ)
#include <blitz/array.h>
using blitz::Array;
using blitz::cos;
using blitz::tensor::i;
using blitz::tensor::j;
using blitz::tensor::k;
#else
#include <cmath>
#endif

#if defined(HAVE_ARMA)
#include <armadillo>
#endif

namespace bench {

  struct Array3d {
    Array3d() : a(0), nx(-1), ny(-1), nz(-1) {}
    ~Array3d() {
      freemem();
    }

    void resize(int _nx, int _ny, int _nz) {
      freemem();
      nx = _nx;
      ny = _ny;
      nz = _nz;
      a = new double**[nx];
      for (int i=0; i<nx; ++i)
        a[i] = new double*[ny];
      for (int i=0; i<nx; ++i)
        for (int j=0; j<ny; ++j)
          a[i][j] = new double[nz];

    }
    void freemem() {
      for (int i=0; i<nx; ++i)
        for (int j=0; j<ny; ++j)
          delete a[i][j];
      for (int i=0; i<nx; ++i)
        delete a[i] ;
      delete a;
    }
    double ***a;
    int nx, ny, nz;
  };

  Array3d array;

  struct OuterMost : bench::Test {
    void op() {
      for (int i=0; i<array.nx; ++i)
        for (int j=0; j<array.ny; ++j)
          for (int k=0; k<array.nz; ++k)
            array.a[i][j][k] = cos(static_cast<double>(i)*j+j*k);
    }
    string opName() const {
      return "Outermost C";
    }
  };


  struct InnerMost : bench::Test {
    void op() {
      for (int k=0; k<array.nz; ++k)
        for (int j=0; j<array.ny; ++j)
          for (int i=0; i<array.nx; ++i)
            array.a[i][j][k] = cos(static_cast<double>(i)*j+j*k);
    }
    string opName() const {
      return "Innermost C";
    }
  };

#if defined(HAVE_BLITZ)

  Array<double,3> Barray;

  struct BlitzArray :  bench::Test {
    BlitzArray() {
      Barray.resize(array.nx,array.ny,array.nz);
    }
    void op() {
      Barray = cos(1.0*(i*j+j*k));
    }
    string opName() const {
      return "Blitz array";
    }
  };
#endif

#if defined(HAVE_ARMA)

  arma::Cube<double> Aarray;

  struct ArmaArray : bench::Test {
    ArmaArray() {
      Aarray.set_size(array.nx,array.ny,array.nz);
    }
    void op() {
#if 0
      for (int k=0; k<array.nz; ++k) // SLOWER
        for (int j=0; j<array.ny; ++j)
          for (int i=0; i<array.nx; ++i)
#else
      for (int i=0; i<array.nx; ++i) // FASTER
        for (int j=0; j<array.ny; ++j)
          for (int k=0; k<array.nz; ++k)
#endif
            Aarray(i,j,k) = static_cast<double>(i)*j+j*k;
      Aarray= cos(Aarray);
    }
    string opName() const {
      return "Arma   cube";
    }
  };
#endif

  void loop(int nx, int ny, int nz)
  {
    cout << "Bench array[" << nx << "][" << ny << "][" << nz << "]" << endl;
    array.resize(nx,ny,nz);
    OuterMost outer;
    bench::benchClassOp(outer, 1.0);
    InnerMost inner;
    bench::benchClassOp(inner, 1.0);
#if defined(HAVE_BLITZ)
    BlitzArray blitzarray;
    bench::benchClassOp(blitzarray, 1.0);
#endif
#if defined(HAVE_ARMA)
    ArmaArray armaarray;
    bench::benchClassOp(armaarray, 1.0);
#endif
  }


}

int main()
{
  bench::verbose = true;

  bench::loop(10,10,10);

  bench::loop(10,20,10);
  bench::loop(20,10,10);
  bench::loop(10,10,20);

  bench::loop(20,10,20);
  bench::loop(10,20,20);
  bench::loop(20,20,10);

  bench::loop(10,20,30);
  bench::loop(20,30,10);
  bench::loop(30,10,20);

  bench::loop(30,20,10);
  bench::loop(20,10,30);
  bench::loop(10,30,20);

  return 0;
}
