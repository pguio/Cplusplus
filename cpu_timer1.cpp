

#if defined(HAVE_BOOST)

// http://www.boost.org/doc/libs/1_51_0/libs/timer/doc/cpu_timers.html

#include <boost/timer/timer.hpp>
#include <cmath>

// When the auto_cpu_timer object is created, it starts timing. When it is
// destroyed at the end of the scope, its destructor stops the timer and
// displays timing information on the default output stream, std::cout.
//
// The output of this program will look something like this:
//
// 5.713010s wall, 5.709637s user + 0.000000s system = 5.709637s CPU (99.9%)
//
// In other words, this program ran in 5.713010 seconds as would be measured
// by a clock on the wall, the operating system charged it for 5.709637
// seconds of user CPU time and 0 seconds of system CPU time, the total of
// these two was 5.709637, and that represented 99.9 percent of the wall
// clock time.
//
// The output stream, number of decimal places reported, and reporting
// format can be controlled by auto_cpu_timer constructor arguments. Here is
// what the output from the above program would look like for several
// different sets of constructor arguments:
//
// t 	5.713010s wall, 5.709637s user + 0.000000s system = 5.709637s CPU (99.9%)
// t(std::cerr, 2) 	5.71s wall, 5.70s user + 0.00s system = 5.70s CPU (99.9%)
// t(1) 	5.7s wall, 5.7s user + 0.0s system = 5.7s CPU (99.9%)
// t(3, "%w seconds\n") 	5.713 seconds
// t("%t sec CPU, %w sec real") 	5.709637 sec CPU, 5.713010 sec real
//
// where
//
// %w 	times.wall
// %u 	times.user
// %s 	times.system
// %t 	times.user + times.system
// %p 	The percentage of times.wall represented by times.user + times.system

int main()
{
  boost::timer::auto_cpu_timer t;

  for (long i = 0; i < 100000000; ++i)
    std::sqrt(123.456L); // burn some time

  return 0;
}

#else

#include <iostream>

int main()
{
  std::cout << "Boost not available." << std::endl << std::endl;
}

#endif
