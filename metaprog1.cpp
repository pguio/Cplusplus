
#include <iostream>

template<unsigned long N>
long Bin()
{
  return (N%10) +2*Bin<N/10>();
}

// Template specialisation
template<> long Bin<0>()
{
  return 0L;
}
template<> long Bin<1>()
{
  return 1L;
}


template<unsigned long N>
long BinOrErr()
{
  return 1; // semantic error
}
template<> long BinOrErr<0>()
{
  return 0L;
}
template<> long BinOrErr<1>()
{
  return 1L;
}

template<unsigned long N>
long BinCheck()
{
  return BinOrErr<N%10> +2*BinCheck<N/10>();
}

int main()
{
  long scale = Bin<1101>();
  std::cout << "scale = " << scale << std::endl;

  long nan = Bin<12345>();
  std::cout << "nan = " << nan << std::endl;

//	long toolong = Bin<1110110111111>();
//	cout << "toolong = " << toolong << endl;

  return 0;
}
