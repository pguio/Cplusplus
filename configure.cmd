#!/bin/sh

case `hostname` in

titan*|alun*|kryten*) 
	./configure --with-fftw=$HOME --with-fftw3=$HOME --with-hdf4=$HOME --with-blitz=$HOME --enable-cxx-flags-preset --enable-optimize CXX="g++"
	;;

login*)
  if test "$LOGNAME" = "ucappgu"; then
    ./configure --with-fftw3=$HOME --with-hdf4=$HOME --with-blitz=$HOME --disable-cxx-flags-preset --enable-mpi --enable-optimize CXX="icpc" MPICXX="mpiCC" CXXFLAGS="-xT -axT -O3 -ip -no-prec-div -no-ansi-alias -static"
  elif test "$LOGNAME" = "patrickg"; then
    ./configure --with-fftw=/site/fftw2 --with-fftw3=/site/fftw3 --with-hdf4=$HOME/include,$HOME/lib/gcc --with-blitz=$HOME/include,$HOME/lib/gcc --enable-cxx-flags-preset --enable-optimize CXX="pathCC"
#    ./configure --with-fftw=$HOME/include,$HOME/lib/gcc --with-fftw3=$HOME/include,$HOME/lib/gcc --with-hdf4=$HOME/include,$HOME/lib/gcc --with-blitz=$HOME/include,$HOME/lib/gcc --enable-cxx-flags-preset --enable-optimize CXX="pathCC"
  fi
  ;;

eukalyptus*)
#./configure --with-fftw=/net/pl/fftw --with-fftw3=/net/pl/fftw --with-hdf4=/net/pl/hdf --with-blitz=/net/pl/blitz CXX="condor_compile g++" CXXFLAGS="-O"
#./configure --with-fftw=/usr --with-fftw3=/net/pl/fftw --with-hdf4=/net/pl/hdf --with-blitz=/net/pl/blitz --disable-cxx-flags-preset CXX="g++" CXXFLAGS="-O -DNDEBUG"
#./configure --with-fftw=/usr --with-fftw3=/net/pl/fftw --with-hdf5=/net/pl/hdf5 --with-blitz=/net/pl/blitz --disable-cxx-flags-preset CXX="g++" CXXFLAGS="-O -DNDEBUG"
./configure --with-fftw=/usr --with-fftw3=/net/pl/fftw --with-hdf5=/net/pl/hdf5 --with-blitz=/net/pl/blitz --enable-cxx-flags-preset --enable-optimize CXX="g++"
;;

fimm*)
./configure  --with-blitz=$HOME --with-fftw3=/local/fftw --with-hdf4=/local/HDF --enable-optimize CXX=g++
;;

jazz5*|jazz6*)
./configure CONFIG_SITE=config/sites/f32_x86_64_g++_optim_jazz5
;;

jazz2*|jazz3*)
./configure CONFIG_SITE=config/sites/f31_x86_64_g++_optim_jazz3
#./configure --with-eigen=/usr/include/eigen3 --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --enable-threadsafe-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-xSSSE3 -vec-report1 -restrict"
#./configure --with-eigen=/usr/include/eigen3 --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --enable-threadsafe-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-ansi -std=c++0x -Weffc++ -parallel -xSSE4.2 -O3 -ipo -no-prec-div -ansi-alias -vec-report1 -restrict"
#./configure --with-eigen=/usr/include/eigen3 --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib64/hdf --with-hdf5=/usr/include,/usr/lib64 --with-blitz=/usr/local/blitz2 --enable-threadsafe-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-D__GNUC_MINOR__=5 -ansi -xSSE4.2 -O3 -ipo -no-prec-div -ansi-alias -vec-report1 -restrict"
#./configure --with-eigen=/usr/include/eigen3 --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib64/hdf --with-hdf5=/usr/include,/usr/lib64 --with-blitz=/usr/local/blitz2 --enable-threadsafe-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-ansi -xSSE4.2 -O3 -ipo -no-prec-div -ansi-alias -qopt-report=1 -restrict" ARMA_LIBS="-larmadillo -llapack -lopenblas -lsuperlu -larpack"
#./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-xT -axT -O3 -ip -no-prec-div -ansi-alias"
#./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --enable-optimize CXX=g++ 
#./configure --with-eigen=/usr/include/eigen3 --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --enable-threadsafe-blitz  --disable-cxx-flags-preset CXX=g++ CXXFLAGS="-g -pedantic"
;;

jazz*|fyspc-rp42*|theta*) 
#./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz=/usr/local --disable-cxx-flags-preset CXX=g++ CXXFLAGS="-pedantic -Wall -DNDEBUG -O"
#./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --disable-cxx-flags-preset CXX=g++ CXXFLAGS="-std=c++0x"
./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz CXX=g++
#./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-xN -O3 -ip -no-prec-div -ansi-alias"
#./configure --with-fftw --with-fftw3 --with-hdf4=/usr/include/hdf,/usr/lib/hdf --with-blitz --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-xN -O3 -ip -no-prec-div -ansi-alias"
#./configure --with-fftw --with-fftw3 --with-hdf4 --with-blitz --disable-cxx-flags-preset CXX=g++ CXXFLAGS="-pedantic -Wall -DNDEBUG -O"
#./configure --with-fftw --with-fftw3 --with-hdf5 --with-blitz --disable-cxx-flags-preset CXX=g++ CXXFLAGS="-Wall -DNDEBUG -O"
#./configure --with-fftw=/usr/local/fftw --with-hdf4=/usr/local/hdf --disable-cxx-flags-preset CXX=g++ CXXFLAGS="-Wall"
#./configure --with-fftw=/usr/local/fftw --with-hdf4=/usr/local/hdf CXX=g++ CXXFLAGS="-Wall -O3"
#./configure CXX=icc CXXFLAGS="-D" --with-blitz=/usr/local --with-fftw=/usr/local/fftw --with-hdf4=/usr/local/hdf
;;

phact*|hyades*|ayil*|barakish*|menkar*|markab*|sothi*|thuban*)
#./configure CC=cc CXX=cxx --with-blitz=$HOME --with-fftw=$HOME
./configure CC=cc CXX=cxx --with-blitz=$HOME --with-fftw=$HOME --with-fftw4=$HOME --with-dxml --with-hdf4=$HOME/src/hdf --enable-optimize
;;

tre*)
#./configure CXX=xlC CXXFLAGS="-qrtti=all -O2 -qstrict -Q -qansialias" --with-blitz=$HOME --with-fftw=/usr/local/fftw-2.1.5
#./configure CXX=xlC CXXFLAGS="-qrtti=all -O2" --with-blitz=$HOME --with-fftw=/u sr/local/fftw-2.1.5
#./configure CXX=xlC CXXFLAGS="-O3 -qmaxmem=-1 -qalign=natural -qcache=auto -qansialias -qarch=auto -qtune=auto -qrtti=all" --with-blitz=$HOME --with-fftw=/usr/local/fftw-2.1.5 --with-hdf4=/usr/local/HDF4
./configure CXX=xlC CXXFLAGS="-q64 -b64 -O3 -qmaxmem=-1 -qalign=natural -qcache=auto -qansialias -qarch=auto -qtune=auto -qrtti=dyna -qtempinc -qfuncsect" --with-blitz=$HOME --with-fftw=/usr/local/fftw-2.1.5-64 --with-hdf4=/usr/local/HDF4-64
#./configure CXX=g++ CXXFLAGS="-Wall -O3" --with-blitz=$HOME --with-fftw=/usr/local/fftw-2.1.5
;;

gridur*|embla*|balder*)
#./configure CXX=CC CXXFLAGS="-64 -mips4 -O3 -LANG:std -LANG:restrict -no_auto_include" --with-blitz=$HOME --with-fftw=$HOME --with-hdf4=$HOME
./configure CXX=CC CXXFLAGS="-mips4 -Ofast=ip27 -64 -LANG:std -LANG:restrict -no_auto_include" --with-blitz=$HOME --with-fftw=$HOME --with-hdf4=$HOME
;;

magnum*| pico*)
./configure CC=cc CXX=aCC --enable-optimize --with-blitz=$HOME --with-fftw=/site/fftw --with-hdf4=/site/hdf
;;

*titan*)
#./configure --with-fftw=$HOME/include,$HOME/lib/gcc --with-blitz=$HOME/include,$HOME/lib/gcc --with-hdf4=$HOME/include,$HOME/lib/gcc CXX=g++
#	./configure --with-fftw=$HOME/include,$HOME/lib/intel --with-fftw3=$HOME/include,$HOME/lib/intel --with-blitz=$HOME/include,$HOME/lib/intel --with-hdf4=$HOME/include,$HOME/lib/intel --enable-optimize CXX=icpc
./configure --with-fftw=$HOME/include,$HOME/lib/intel --with-fftw3=$HOME/include,$HOME/lib/intel --with-blitz=$HOME/include,$HOME/lib/intel --with-hdf4=$HOME/include,$HOME/lib/intel --disable-cxx-flags-preset CXX=icpc CXXFLAGS="-xP -O3 -ip -no-prec-div -ansi-alias"
#	./configure --with-fftw=$HOME/include,$HOME/lib/portland --with-fftw3=$HOME/include,$HOME/lib/portland --with-blitz=$HOME/include,$HOME/lib/portland --with-hdf4=$HOME/include,$HOME/lib/portland --enable-optimize CXX=pgCC
;;


snowstorm*)
#./configure CXX=icc CXXFLAGS="-O3" --with-blitz=$HOME --with-fftw=$HOME --with-hdf4=$HOME 
./configure CXX=g++ CXXFLAGS="-O3" --with-blitz=$HOME --with-fftw=$HOME --with-hdf4=$HOME 
;;

nana*)
./configure CXX=aCC --enable-optimize --with-blitz=$HOME --with-fftw=/usr/local/numerics/fftw --with-hdf=/usr/local/hdf/hdf
;;

*) echo No default configuration for machine `hostname`

esac
