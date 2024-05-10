
ACLOCAL_AMFLAGS  = -I m4

SUBDIRS = libltdl

libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

# Executable targets
bin_PROGRAMS = \
abc abc1 abc2 \
any any1 any2 \
arma1 arma2 \
auto \
auto_ptr \
bench_tensor \
class_factory class_factory1 class_factory2 class_factory3 \
class_model class_model1 class_model2 \
const_cast dynamic_cast reinterpret_cast \
cpu_timer1 cpu_timer2 cpu_timer_info \
create_hdf4_sd create_hdf5_sd \
dll \
eigen1 eigen2 \
exception0 exception1 exception2 exception3 \
expr_template expr_template1 \
functions functions1 \
fourier-bench fourier-bench1 fourier-bench2 fourier-dxml fourier-fftw fourier-fftw3 fourier-mlib \
gnuplot-example \
hash \
loop \
map0 map1 map2 map3 map4 \
metaprog metaprog1 \
multi multi1 multi2 \
multimap multimap1 \
overload overload1 overload2 \
popt \
promote_trait \
readfile \
static_dynamic_class \
string0 string1 string2 string3 \
string_convert \
test-dcl test-dcl1 \
test-enum \
test-parser test-parser2 \
typeid \
virtual virtual1 \
voronoi

cpptools_dir = $(top_srcdir)/c++-tools

EXTRA_DIST = base.h base-args.h circle.h derived.h derived-args.h enum.h \
factory.h factory-args.h factory-args1.h fourier-bench2-utils.h \
shape.h square.h $(cpptools_dir)/*

CLEANFILES = test-parse-string.cpp

# create source
test-parser-string.cpp: test-parser.cpp
	$(SED) -e 's/parser.h/parser-string.h/' $< > $@

AM_CPPFLAGS = -I$(cpptools_dir)

abc_SOURCES = abc.cpp
abc1_SOURCES = abc1.cpp
abc2_SOURCES = abc2.cpp

any_SOURCES = any.cpp 
any1_SOURCES = any1.cpp 
any2_SOURCES = any2.cpp 

arma1_SOURCES = arma1.cpp 
arma1_CXXFLAGS = $(ARMA_CPPFLAGS)
arma1_LDFLAGS = $(ARMA_LDFLAGS)
arma1_LDADD = $(ARMA_LIBS)

arma2_SOURCES = arma2.cpp
arma2_CXXFLAGS = $(ARMA_CPPFLAGS) 
arma2_LDFLAGS = $(ARMA_LDFLAGS)
arma2_LDADD = $(ARMA_LIBS)

auto_SOURCES = auto.cpp

auto_ptr_SOURCES = auto_ptr.cpp

bench_tensor_SOURCES = bench_tensor.cpp
bench_tensor_CXXFLAGS = $(EIGEN_CPPFLAGS) $(BLITZ_CPPFLAGS)
bench_tensor_LDFLAGS = $(BLITZ_LDFLAGS)
bench_tensor_LDADD = $(BLITZ_LIBS)

class_factory_SOURCES = class_factory.cpp base.cpp derived.cpp
class_factory1_SOURCES = class_factory1.cpp base.cpp derived.cpp
class_factory2_SOURCES = class_factory2.cpp base-args.cpp derived-args.cpp
class_factory3_SOURCES = class_factory2.cpp base-args.cpp derived-args.cpp
class_factory3_CXXFLAGS = -DFACTORY_ARGS1

class_model_SOURCES = class_model.cpp
class_model1_SOURCES = class_model1.cpp
class_model2_SOURCES = class_model2.cpp

const_cast_SOURCES = const_cast.cpp
dynamic_cast_SOURCES = dynamic_cast.cpp
reinterpret_cast_SOURCES = reinterpret_cast.cpp

cpu_timer1_SOURCES = cpu_timer1.cpp
cpu_timer1_CXXFLAGS = $(BOOST_CPPFLAGS)
cpu_timer1_LDFLAGS = $(BOOST_LDFLAGS)
cpu_timer1_LDADD = $(BOOST_SYSTEM_LIB) -lboost_timer 

cpu_timer2_SOURCES = cpu_timer2.cpp
cpu_timer2_CXXFLAGS = $(BOOST_CPPFLAGS)
cpu_timer2_LDFLAGS = $(BOOST_LDFLAGS)
cpu_timer2_LDADD = $(BOOST_SYSTEM_LIB) -lboost_timer

cpu_timer_info_SOURCES = cpu_timer_info.cpp
cpu_timer_info_CXXFLAGS = $(BOOST_CPPFLAGS)
cpu_timer_info_LDFLAGS = $(BOOST_LDFLAGS)
cpu_timer_info_LDADD = $(BOOST_SYSTEM_LIB) -lboost_timer -lboost_chrono -lboost_system

create_hdf4_sd_SOURCES = create_hdf_sd.cpp $(cpptools_dir)/hdf-interface.cpp \
 $(cpptools_dir)/parser.cpp
create_hdf4_sd_CXXFLAGS = $(BLITZ_CPPFLAGS) $(HDF4_CPPFLAGS) -UHAVE_HDF5
create_hdf4_sd_LDFLAGS = $(BLITZ_LDFLAGS) $(HDF4_LDFLAGS) 
create_hdf4_sd_LDADD = $(BLITZ_LIBS) $(HDF4_LIBS) 

create_hdf5_sd_SOURCES = create_hdf_sd.cpp $(cpptools_dir)/hdf-interface.cpp \
 $(cpptools_dir)/parser.cpp
create_hdf5_sd_CXXFLAGS = $(BLITZ_CPPFLAGS) $(HDF5_CPPFLAGS) -UHAVE_HDF4
create_hdf5_sd_LDFLAGS = $(BLITZ_LDFLAGS) $(HDF5_LDFLAGS)
create_hdf5_sd_LDADD = $(BLITZ_LIBS) $(HDF5_LIBS)

dll_SOURCES = dll.cpp
dll_LDFLAGS = -export-dynamic
dll_LDADD   = $(DL_LIBS)

eigen1_SOURCES = eigen1.cpp
eigen1_CXXFLAGS = $(EIGEN_CPPFLAGS)
eigen2_SOURCES = eigen2.cpp
eigen2_CXXFLAGS = $(EIGEN_CPPFLAGS)

exception0_SOURCES = exception.cpp
exception1_SOURCES = exception1.cpp
exception2_SOURCES = exception2.cpp
exception3_SOURCES = exception3.cpp

expr_template_SOURCES  = expr_template.cpp
expr_template1_SOURCES = expr_template1.cpp

fourier_bench_SOURCES  = fourier-bench.cpp fourier-bench-fftw.cpp \
fourier-bench-fftw3.cpp fourier-bench-dxml.cpp fourier-bench-mlib.cpp
fourier_bench_CXXFLAGS = $(FFTW_CPPFLAGS) $(FFTW3_CPPFLAGS) $(DXML_CPPFLAGS) $(MLIB_CPPFLAGS)
fourier_bench_LDFLAGS  = $(FFTW_LDFLAGS) $(FFTW3_LDFLAGS) $(DXML_LDFLAGS) $(MLIB_LDFLAGS)
fourier_bench_LDADD    = $(FFTW_LIBS) $(FFTW3_LIBS) $(DXML_LIBS) $(MLIB_LIBS)

fourier_bench1_SOURCES  = fourier-bench1.cpp fourier-bench1-fftw.cpp \
fourier-bench1-fftw3.cpp fourier-bench1-dxml.cpp fourier-bench1-mlib.cpp
fourier_bench1_CXXFLAGS = $(FFTW_CPPFLAGS) $(FFTW3_CPPFLAGS) $(DXML_CPPFLAGS) $(MLIB_CPPFLAGS)
fourier_bench1_LDFLAGS  = $(FFTW_LDFLAGS) $(FFTW3_LDFLAGS) $(DXML_LDFLAGS) $(MLIB_LDFLAGS)
fourier_bench1_LDADD    = $(FFTW_LIBS) $(FFTW3_LIBS) $(DXML_LIBS) $(MLIB_LIBS)

fourier_bench2_SOURCES  = fourier-bench2.cpp fourier-bench2-fftw.cpp \
fourier-bench2-fftw3.cpp fourier-bench2-dxml.cpp fourier-bench2-mlib.cpp
fourier_bench2_CXXFLAGS = $(BLITZ_CPPFLAGS) $(FFTW_CPPFLAGS) $(FFTW3_CPPFLAGS) $(DXML_CPPFLAGS) $(MLIB_CPPFLAGS)
fourier_bench2_LDFLAGS  = $(FFTW_LDFLAGS) $(FFTW3_LDFLAGS) $(DXML_LDFLAGS) $(MLIB_LDFLAGS)
fourier_bench2_LDADD    = $(FFTW_LIBS) $(FFTW3_LIBS) $(DXML_LIBS) $(MLIB_LIBS)

fourier_fftw_SOURCES  = fourier-test.cpp
fourier_fftw_CXXFLAGS = -DFOURIER_FFTW $(BLITZ_CPPFLAGS) $(FFTW_CPPFLAGS)
fourier_fftw_LDFLAGS  = $(BLITZ_LDFLAGS) $(FFTW_LDLAGS)
fourier_fftw_LDADD    = $(BLITZ_LIBS) $(FFTW_LIBS)

fourier_fftw3_SOURCES  = fourier-test.cpp
fourier_fftw3_CXXFLAGS = -DFOURIER_FFTW3 $(BLITZ_CPPFLAGS) $(FFTW3_CPPFLAGS)
fourier_fftw3_LDFLAGS  = $(BLITZ_LDFLAGS) $(FFTW3_LDFLAGS)
fourier_fftw3_LDADD    = $(BLITZ_LIBS) $(FFTW3_LIBS)

fourier_dxml_SOURCES  = fourier-test.cpp
fourier_dxml_CXXFLAGS = -DFOURIER_DXML $(BLITZ_CPPFLAGS) $(DXML_CPPFLAGS)
fourier_dxml_LDFLAGS  = $(BLITZ_LDFLAGS) $(DXML_LDFLAGS)
fourier_dxml_LDADD    = $(BLITZ_LIBS) $(DXML_LIBS)

fourier_mlib_SOURCES  = fourier-test.cpp
fourier_mlib_CXXFLAGS = -DFOURIER_MLIB $(BLITZ_CPPFLAGS) $(MLIB_CPPFLAGS)
fourier_mlib_LDFLAGS  = $(BLITZ_LDFLAGS) $(MLIB_LDLAGS)
fourier_mlib_LDADD    = $(BLITZ_LIBS) $(MLIB_LIBS)

functions_SOURCES = functions.cpp

functions1_SOURCES  = functions1.cpp
functions1_CXXFLAGS = $(BLITZ_CPPFLAGS)
functions1_LDFLAGS  = $(BLITZ_LDFLAGS)
functions1_LDADD    = $(BLITZ_LIBS)

gnuplot_example_SOURCES = gnuplot-example.cpp $(cpptools_dir)/gnuplot-interface.cpp

hash_SOURCES = hash.cpp

loop_SOURCES  = loop.cpp
loop_CXXFLAGS = $(BLITZ_CPPFLAGS) $(ARMA_CPPFLAGS)
loop_LDFLAGS  = $(BLITZ_LDFLAGS) $(ARMA_LDFLAGS)
loop_LDADD    = $(BLITZ_LIBS) $(ARMA_LIBS)

map0_SOURCES = map0.cpp
map1_SOURCES = map1.cpp
map2_SOURCES = map2.cpp
map3_SOURCES = map3.cpp
map4_SOURCES = map4.cpp

metaprog_SOURCES = metaprog.cpp
metaprog1_SOURCES = metaprog1.cpp

multi_SOURCES = multi.cpp
multi1_SOURCES = multi1.cpp
multi2_SOURCES = multi2.cpp

multimap_SOURCES = multimap.cpp
multimap1_SOURCES = multimap1.cpp

overload_SOURCES = overload.cpp
overload1_SOURCES = overload1.cpp
overload2_SOURCES = overload2.cpp

popt_SOURCES = popt.cpp
popt_LDADD    = $(POPT_LIBS)

promote_trait_SOURCES = promote_trait.cpp

readfile_SOURCES = readfile.cpp

static_dynamic_class_SOURCES = static_dynamic_class.cpp

string_convert_SOURCES = string_convert.cpp

string0_SOURCES = string0.cpp
string1_SOURCES = string1.cpp
string2_SOURCES = string2.cpp
string3_SOURCES = string3.cpp

test_dcl_SOURCES = test-dcl.cpp 
test_dcl_LDFLAGS = -export-dynamic
test_dcl_LDADD = $(DL_LIBS) "-dlopen" self "-dlopen" libcircle.la "-dlopen" libsquare.la
test_dcl_DEPENDENCIES = $(DL_LIBS) libcircle.la libsquare.la

test_dcl1_SOURCES = test-dcl1.cpp 
test_dcl1_CPPFLAGS = $(INCLTDL)
test_dcl1_LDFLAGS = -export-dynamic
test_dcl1_LDADD = $(LIBLTDL) "-dlopen" self "-dlopen" libcircle.la "-dlopen" libsquare.la
test_dcl1_DEPENDENCIES = $(LIBLTDL) libcircle.la libsquare.la

lib_LTLIBRARIES = libcircle.la libsquare.la
libcircle_la_SOURCES = circle.cpp
libsquare_la_SOURCES = square.cpp

test_enum_SOURCES = enum.cpp test-enum.cpp 

test_parser_SOURCES  = test-parser.cpp $(cpptools_dir)/parser.cpp 
test_parser_CXXFLAGS = $(BLITZ_CPPFLAGS)
test_parser_LDFLAGS  = $(BLITZ_LDFLAGS)
test_parser_LDADD    = $(BLITZ_LIBS)

test_parser2_SOURCES  = test-parser2.cpp $(cpptools_dir)/parser2.cpp 
test_parser2_CXXFLAGS = $(BLITZ_CPPFLAGS)
test_parser2_LDFLAGS  = $(BLITZ_LDFLAGS)
test_parser2_LDADD    = $(BLITZ_LIBS)

typeid_SOURCES = typeid.cpp

virtual_SOURCES = virtual.cpp
virtual1_SOURCES = virtual1.cpp

voronoi_SOURCES = voronoi.cpp
voronoi_LDADD   = -lvigraimpex

check: 
	@echo Running test suite...
	@for prog in $(bin_PROGRAMS); do \
		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
	done
	@echo All tests passed.

## Clean up template repositories
clean-local:
	-rm -rf cxx_repository ii_files
