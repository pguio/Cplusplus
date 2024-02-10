
#include <gnuplot-interface.h>

const int SLEEP_LGTH=1;
const int NPOINTS=50;

using std::cout;
using std::endl;

using std::vector;

using gnuplot::Gnuplot;
using gnuplot::GnuplotException;


int main(int argc, char *argv[])
{
  cout << "*** example of gnuplot control through C++ ***" << endl;

  Gnuplot g1("lines");

  // Functions
  g1.reset();
  cout << endl << endl << "*** various functions" << endl;
  cout << "y = sin(x)" << endl;
  g1.plot("sin(x)","sine");
  g1.pause(SLEEP_LGTH);

  cout << "y = log(x)" << endl;
  g1.plot("log(x)","logarithm");
  g1.pause(SLEEP_LGTH);

  cout << "y = sin(x) * cos(2*x)" << endl;
  g1.plot("sin(x)*cos(2*x)","sine product");
  g1.pause(SLEEP_LGTH);

  // Styles
  g1.reset();
  cout << endl << endl << "*** showing styles" << endl;
  cout << "sine in points" << endl;
  g1.setLineStyle("points");
  g1.plot("sin(x)","sine");
  g1.pause(SLEEP_LGTH);

  cout << "sine in impulses" << endl;
  g1.setLineStyle("impulses");
  g1.plot("sin(x)","sine");
  g1.pause(SLEEP_LGTH);

  cout << "sine in steps" << endl;
  g1.setLineStyle("steps");
  g1.plot("sin(x)","sine");
  g1.pause(SLEEP_LGTH);

  // User defined 1d and 2d point sets
  cout << endl << endl << "*** user-defined lists of doubles" << endl;
  {
    vector<double> x;
    for (int i = 0; i < NPOINTS; ++i)
      x.push_back((double)i * (double)i);
    g1.reset();
    g1.setLineStyle("impulses");
    g1.plot(x,"user-defined doubles");
  }
  g1.pause(SLEEP_LGTH);


  cout << endl << endl << "*** user-defined lists of points" << endl;
  {
    vector<double> x;
    vector<double> y;
    for (int i = 0; i < NPOINTS; ++i) {
      x.push_back((double)i);
      y.push_back((double)i * (double)i);
    }
    g1.reset();
    g1.setLineStyle("points");
    g1.plot(x,y,"user-defined points");
  }
  g1.pause(SLEEP_LGTH);

  // Multiple output screens
  cout << endl << endl;
  cout << "*** multiple output windows" << endl;
  g1.reset();
  g1.setLineStyle("lines");

  Gnuplot g2("lines");
  Gnuplot g3("lines");

  cout << "window 1: sin(x)" << endl;
  g1.plot("sin(x)","sin(x)");
  g1.pause(SLEEP_LGTH);

  cout << "window 2: x*sin(x)" << endl;
  g2.plot("x*sin(x)","x*sin(x)");
  g2.pause(SLEEP_LGTH);

  cout << "window 3: log(x)/x" << endl;
  g3.plot("log(x)/x","log(x)/x");
  g3.pause(SLEEP_LGTH);

  // Using the GnuplotException class
  try {
    Gnuplot g4("lines");
    cout << "window 4: sin(x)/x" << endl;
    g4.plot("sin(x)/x","sin(x)/x");
    g4.pause(SLEEP_LGTH);

  }
  catch (GnuplotException *ge) {
    cout << ge->what() << endl;
  }

  cout << endl << "*** end of gnuplot example" << endl;

  return 0;
}
