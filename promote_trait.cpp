#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

template<class T>
struct precision_trait {
  enum {
    precisionRank = 0, knowPrecisionRank = 0
  };
};

#define BZ_DECLARE_PRECISION(T,rank)                                     \
template<> struct precision_trait< T >                                   \
{                                                                        \
  enum { precisionRank = rank, knowPrecisionRank = 1 };                  \
};

BZ_DECLARE_PRECISION(int,100)
BZ_DECLARE_PRECISION(unsigned int,200)
BZ_DECLARE_PRECISION(long,300)
BZ_DECLARE_PRECISION(unsigned long,400)
BZ_DECLARE_PRECISION(float,500)
BZ_DECLARE_PRECISION(double,600)
BZ_DECLARE_PRECISION(long double,700)

template<class T>
struct autopromote_trait {
  typedef T T_numtype;
};

#define BZ_DECLARE_AUTOPROMOTE(T1,T2)     \
template<> struct autopromote_trait<T1>   \
{                                         \
	typedef T2 T_numtype;                   \
};

BZ_DECLARE_AUTOPROMOTE(bool, int)
BZ_DECLARE_AUTOPROMOTE(char, int)
BZ_DECLARE_AUTOPROMOTE(unsigned char, int)
BZ_DECLARE_AUTOPROMOTE(short int, int)
BZ_DECLARE_AUTOPROMOTE(short unsigned int, unsigned int)

template<class T1, class T2, int promoteToT1>
struct _bz_promote2 {
  typedef T1 T_promote;
};

template<class T1, class T2>
struct _bz_promote2<T1,T2,0> {
  typedef T2 T_promote;
};

template<class T1_orig, class T2_orig>
struct promote_trait {
  typedef typename autopromote_trait<T1_orig>::T_numtype T1;
  typedef typename autopromote_trait<T2_orig>::T_numtype T2;

  enum {
    T1IsBetter = static_cast<int>(precision_trait<T1>::precisionRank)
    > static_cast<int>(precision_trait<T2>::precisionRank),
    knowBothRanks = static_cast<int>(precision_trait<T1>::knowPrecisionRank
    && static_cast<int>(precision_trait<T2>::knowPrecisionRank)),
    knowT1butNotT2 =  static_cast<int>(precision_trait<T1>::knowPrecisionRank
    && !static_cast<int>(precision_trait<T2>::knowPrecisionRank)),
    knowT2butNotT1 =  static_cast<int>(precision_trait<T2>::knowPrecisionRank
    && !static_cast<int>(precision_trait<T1>::knowPrecisionRank)),
    T1IsLarger = sizeof(T1) >= sizeof(T2),
    defaultPromotion = knowT1butNotT2 ? false :
    (knowT2butNotT1 ? true : T1IsLarger)
  };
  enum {
    promoteToT1 = (static_cast<int>(knowBothRanks) ?
    static_cast<int>(T1IsBetter)
    : static_cast<int>(defaultPromotion)) ? 1 : 0
  };

  typedef typename _bz_promote2<T1,T2,T1IsBetter>::T_promote T_promote;
};

#define BZ_PROMOTE(A,B) promote_trait<A,B>::T_promote

int main()
{
  cout << "<int,int> " << typeid(BZ_PROMOTE(int,int)).name() << endl;
  cout << "<int,long> " << typeid(BZ_PROMOTE(int,long)).name() << endl;
  cout << "<long,int> " << typeid(BZ_PROMOTE(long,int)).name() << endl;
  cout << "<int,float> " << typeid(BZ_PROMOTE(int,float)).name() << endl;
  cout << "<float,int> " << typeid(BZ_PROMOTE(float,int)).name() << endl;
  cout << "<int,double> " << typeid(BZ_PROMOTE(int,double)).name() << endl;
  cout << "<double,int> " << typeid(BZ_PROMOTE(double,int)).name() << endl;
  cout << "<long,long> " << typeid(BZ_PROMOTE(long,long)).name() << endl;
  cout << "<long,float> " << typeid(BZ_PROMOTE(long,float)).name() << endl;
  cout << "<float,long> " << typeid(BZ_PROMOTE(float,long)).name() << endl;
  cout << "<long,double> " << typeid(BZ_PROMOTE(long,double)).name() << endl;
  cout << "<double,long> " << typeid(BZ_PROMOTE(double,long)).name() << endl;
  cout << "<float,float> " << typeid(BZ_PROMOTE(float,float)).name() << endl;
  cout << "<float,double> " << typeid(BZ_PROMOTE(float,double)).name() << endl;
  cout << "<double,double> " << typeid(BZ_PROMOTE(double,double)).name() << endl;

}
