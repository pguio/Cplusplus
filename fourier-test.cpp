/**************************************************************************
 *
 * $Id: fourier-test.cpp,v 1.13 2011/03/26 07:10:50 patrick Exp $
 *
 * Copyright (c) 2001-2011 Patrick Guio <patrick.guio@gmail.com>
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2.  of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/

#include <iostream>

using std::cout;
using std::endl;

#if defined(FOURIER_FFTW)
#if defined(HAVE_FFTW_FFT)
#undef HAVE_FFTW3_FFT
#undef HAVE_DXML_FFT
#undef HAVE_MLIB_FFT
#define HAVE_FOURIER 1
#else
#define HAVE_FOURIER 0
#endif
const char fft_name[] = "fftw";
#elif defined(FOURIER_FFTW3)
#if defined(HAVE_FFTW3_FFT)
#undef HAVE_FFTW_FFT
#undef HAVE_DXML_FFT
#undef HAVE_MLIB_FFT
#define HAVE_FOURIER 1
#else
#define HAVE_FOURIER 0
#endif
const char fft_name[] = "fftw3";
#elif defined(FOURIER_DXML)
#if defined(HAVE_DXML_FFT)
#undef HAVE_FFTW_FFT
#undef HAVE_FFTW3_FFT
#undef HAVE_MLIB_FFT
#define HAVE_FOURIER 1
#else
#define HAVE_FOURIER 0
#endif
const char fft_name[] = "dxml";
#elif defined(FOURIER_MLIB)
#if defined(HAVE_MLIB_FFT)
#undef HAVE_FFTW_FFT
#undef HAVE_FFTW3_FFT
#undef HAVE_DXML_FFT
#define HAVE_FOURIER 1
#else
#define HAVE_FOURIER 0
#endif
const char fft_name[] = "mlib";
#else
#define HAVE_FOURIER 0
const char fft_name[] = "";
#endif

#if HAVE_FOURIER==1 && HAVE_BLITZ==1

#include <fourier.h>
using namespace blitz;

template <class Array>
void initArray(int sign, Array &A)
{
  switch (sign) {
  case -1:
    A = 1.0;
    break;
  case  1:
    A = 0.0;
    A(0) = A.size();
    break;
  }
}

template <class T1, class T2>
void itest(int n1, int sign)
{
  fourier::IDFT1D<T1,T2> dft1d(n1, sign);
  cout << " DFT1D = " << dft1d << endl;
  typename fourier::IDFT1D<T1,T2>::Array1di A(n1);
  initArray(sign, A);
  cout << "A = " << A << endl;
  dft1d.direct(A);
  cout << "A =  DFT(A) " << A << endl;
  dft1d.inverse(A);
  cout << "A = IDFT(A) " << A << endl << endl;
}

template <class T1, class T2>
void otest(int n1, int n2, int sign)
{
  fourier::ODFT1D<T1,T2> dft1d(n1, sign);
  cout << " DFT1D = " << dft1d << endl;
  typename fourier::ODFT1D<T1,T2>::Array1di A(n1);
  typename fourier::ODFT1D<T1,T2>::Array1do B(n2);
  initArray(sign, A);
  cout << "A = " << A << endl;
  dft1d.direct(A, B);
  cout << "B =  DFT(A) " << B << endl;
  dft1d.inverse(B, A);
  cout << "A = IDFT(B) " << A << endl << endl;
}


int main(int nargs, char *args[])
{
  try {
    int n = ( nargs == 2 ? atoi(args[1]) : 6);

    itest<fourier::complex, fourier::complex>(n,-1);
    itest<fourier::complex, fourier::complex>(n, 1);
    otest<fourier::complex, fourier::complex>(n,n,-1);
    otest<fourier::complex, fourier::complex>(n,n, 1);

    itest<double, double>(n,-1);
    itest<double, double>(n, 1);
    otest<double, double>(n,n,-1);
    otest<double, double>(n,n, 1);

#if defined(HAVE_FFTW3_FFT)
    itest<double, fourier::complex>(n,-1);
    itest<double, fourier::complex>(n, 1);
    otest<double, fourier::complex>(n,n/2+1,-1);
    otest<double, fourier::complex>(n,n/2+1, 1);
#endif

    return 0;

  }
  catch(int status) {
    return status;
  }
  catch(ClassException& c) {
    cerr << c.what() << endl;
    return !0;
  }
}
#else

int main()
{
  cout << "Cannot test " << __FILE__ << " with " << fft_name
       << " implementation.\n" << "Not supported on this platform" << endl;

  return 0;
}

#endif


