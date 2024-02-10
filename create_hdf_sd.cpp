

#if defined(HAVE_BLITZ) && (defined(HAVE_HDF4) || defined(HAVE_HDF5))

#include <hdf-interface.h>
#include <blitz/array.h>

#include <iostream>

const char  varName[]  = "sd2dVar";
const char  dim1Name[] = "firstDim";
const char  dim2Name[] = "secondDim";

const int   dim1       = 10;
const float dim1Min    = 0.0;
const float dim1Max    = 1.0;

const int   dim2       = 5;
const float dim2Min    = 0.0;
const float dim2Max    = 5.0;

const char  varName2[]  = "sd2dVar-slab";

int main(int nargs, char *args[])
{
  try {

    hdf::Hdf hdf(nargs, args);


    if (hdf.parseHelp())
      return 0;
    if (hdf.parseVersion())
      return 0;
    if (hdf.parseTemplate())
      return 0;

    // Prepare HDF-SD variables
    hdf.createSD("Test HDF-SD Dummy Id");

    std::cout << hdf << std::endl;

    hdf::SDvar V(2);

    V.varname = varName;
    V.vartype =  hdf::type<float>::def;

    V.dimsize[0] = dim1;
    V.dimtype[0] = hdf::type<float>::def;
    V.dimname[0] = dim1Name;
    V.start[0] = dim1Min;
    V.stride[0] = (dim1Max-dim1Min)/(dim1-1);
    V.end[0] = dim1Max;

    V.dimsize[1] = dim2;
    V.dimtype[1] = hdf::type<float>::def;
    V.dimname[1] = dim2Name;
    V.start[1] = dim2Min;
    V.stride[1] = (dim2Max-dim2Min)/(dim2-1);
    V.end[1] = dim2Max;

    std::cout << "V = " << V << std::endl;

    hdf.initSDvar(V);

#if 0
    hdf.endInitSD();
#endif

    // Create a Blitz variable
    blitz::Array<float,2> A(dim1,dim2);
    A = dim2*blitz::tensor::i+blitz::tensor::j;
    std::cout << " A =" << A << std::endl;


    // Write the Blitz variable into the HDF-SD variable
    hdf::VecInt start(2);
    hdf::VecInt edge(2);

    start[0] = 0;
    edge[0] = dim1;
    start[1] = 0;
    edge[1] = dim2;

    hdf.writeSDvar(varName, start, edge, A.data());

    // copy V into Vslab variable
    hdf::SDvar Vslab(V);
    Vslab.varname = varName2;

    hdf.initSDvar(Vslab);

    // Create a Blitz array
    blitz::Array<float,2> zeros(dim1,dim2);
    zeros = 0;

    // initialise file variable with zeros
    hdf.writeSDvar(varName2, start, edge, zeros.data());

    // define slab limits
    start[0] = 2;
    edge[0] = dim1-4;
    start[1] = 1;
    edge[1] = dim2-2;

    // Create a Blitz variable of size slab
    blitz::Array<float,2> slab(edge[0],edge[1]);
    slab = A(blitz::Range(start[0],start[0] + edge[0]),
             blitz::Range(start[1],start[1] + edge[1]));
    std::cout << " slab =" << slab << std::endl;

    // write slab A(2:end-4,1:end-2)
    hdf.writeSDvar(varName2, start, edge, slab.data());

    return 0;

  } catch (ClassException& c) {
    std::cerr << c.what() << std::endl;
    return !0;
  }
}

#else

int main()
{
  return 0;
}

#endif
