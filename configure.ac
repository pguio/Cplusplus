# Process this file with autoconf to produce a configure script.


AC_PREREQ(2.60)

AC_INIT([cpp-examples],[1.7.1],[patrick.guio@gmail.com])

AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([Makefile.am])

AC_CANONICAL_TARGET

dnl AM_INIT_AUTOMAKE([1.9 dist-bzip2])
dnl https://autotools.io/automake/nonrecursive.html
dnl See Warning in 2.1. Achieving Non-Recursive Make
dnl about path prefix in *_SOURCES variables in Makefile.am
AM_INIT_AUTOMAKE([1.9 dist-bzip2 subdir-objects])

dnl Avoid generating makefile rules to rebuild maintainer-only files by
dnl default.  Maintainers may override this default and generate these
dnl makefile rules using the `--enable-maintainer-mode' configure option.
AM_MAINTAINER_MODE

AC_MSG_NOTICE
AC_MSG_NOTICE([Configuring $PACKAGE_STRING for $target])
AC_MSG_NOTICE

dnl C++ compiler
AC_PROG_CXX([xlc++ xlC icpc pathCC pgCC cxx aCC c++ CC g++ KCC FCC])
AC_LANG(C++)
AC_CXX_FLAGS_PRESET

AM_CONDITIONAL(COMPILER_IS_COMPAQ_CXX, [test x"$CXX" = xcxx])

dnl Check if the script was called with --enable-64bit
dnl and if so modify the compilation flags.
AC_COMPILERS_ENABLE_64BITS

dnl Check if the script was called with --enable-optimize,
dnl --enable-debug or --enable-profile, and if so modify
dnl the compilation flags.
AC_CXX_ENABLE_OPTIMIZE
AC_CXX_ENABLE_DEBUG
AC_CXX_ENABLE_PROFILE


dnl from libtool pre 2.2 versions
dnl Enable shared library building 
dnl by default (use --disable-shared to disable)
dnl AC_DISABLE_STATIC
dnl enable building of the convenience library
dnl and set LIBLTDL accordingly
dnl AC_LIBLTDL_CONVENIENCE
dnl substitute LTDLINCL and LIBLTDL in Makefiles
dnl AC_SUBST(INCLTDL)
dnl AC_SUBST(LIBLTDL)
dnl AC_SUBST(LIBTOOL_DEPS)
dnl check for '-dlopen' and 'dlreopen' support in Makefile.am
dnl AC_LIBTOOL_DLOPEN
dnl configure libtool
dnl AC_PROG_LIBTOOL
dnl configure libltdl
dnl AC_CONFIG_SUBDIRS([libltdl])

dnl from libtool 2.2.2
dnl Name the subdirectory that contains sources 
LT_CONFIG_LTDL_DIR([libltdl])
dnl configure libtool with dlopen support if possible
LT_INIT([dlopen disable-static])
AC_SUBST([LIBTOOL_DEPS])
LT_LANG([C++])
# Enable building of the installable libltdl library
LTDL_INIT([convenience])
dnl _LT_SET_OPTION([LTDL_INIT], [convenience])
dnl _LTDL_SETUP

dnl AC_CONFIG_AUX_DIR([libltdl/config])
dnl AC_CONFIG_MACRO_DIR([libltdl/m4])


dnl Checks for libraries
AC_CHECK_FUNC([sin],,[AC_CHECK_LIB(m,sin)])
AC_CHECK_FUNC([popt],,[AC_CHECK_LIB(popt,poptGetContext,[
AC_DEFINE([HAVE_LIBPOPT],[1],[Have popt library])
AC_SUBST(POPT_LIBS,"-lpopt")])])
AC_CHECK_FUNC([dl],,[AC_CHECK_LIB(dl,dlopen,[AC_SUBST(DL_LIBS,"-ldl")])])

dnl Blitz path and derived variables
AC_CHECK_BLITZ

dnl Eigen path and derived variables
AC_CHECK_EIGEN

dnl Armadillo path and derived variables
AC_CHECK_ARMA

dnl FFT library
AC_CHECK_FFTW
AC_CHECK_FFTW3
AC_CHECK_MLIB
AC_CHECK_DXML

dnl HDF path and derived variables
AC_CHECK_HDF4
AC_CHECK_HDF5

dnl Boost
AX_BOOST_BASE
AX_BOOST_SYSTEM
dnl removed unecessary directive that creates problem with pgc++ 18.10
if test "x$BOOST_CPPFLAGS" = "x-I/usr/include" ; then
  BOOST_CPPFLAGS=
fi


# Checks for header files.
AC_CXX_HAVE_STD
AC_CHECK_HEADER([unordered_map], AC_DEFINE(HAVE_UNORDERED_MAP),[
  AC_CHECK_HEADER([hash_map], AC_DEFINE(HAVE_HASH_MAP),[
  AC_CHECK_HEADER([ext/hash_map], AC_DEFINE(HAVE_EXT_HASH_MAP))])])
AC_CHECK_HEADER([sys/times.h], [AC_DEFINE(HAVE_SYS_TIMES_H)])
AC_CHECK_HEADER([popt.h], [AC_DEFINE(HAVE_POPT_H)])


dnl Print variables
AC_ENV

AC_CONFIG_FILES([Makefile])

AC_CONFIG_FILES([makelinks:makelinks.sh.in], [chmod +x makelinks])

AC_OUTPUT
