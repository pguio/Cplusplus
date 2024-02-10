
#include <iostream>

using std::cout;
using std::endl;

class Geometry {
public:
  Geometry() {}
  virtual ~Geometry() {}
  virtual void WhatAmI() {
    cout << "a base class geometry object" << endl;
    Coucou();
  }
private:
  virtual void Coucou() {
    cout << "Coucou from geometry" << endl;
  }
};

class Rectangle : public Geometry {
public:
  Rectangle() {}
  virtual ~Rectangle() {}
  void WhatAmI() {
    cout << "augmented object from" << endl;
    Geometry::WhatAmI();
    cout << "to" << endl;
    cout << "a rectangle class geometry object" << endl;
    Coucou();
  }
private:
  void Coucou() {
    cout << "Coucou from rectangle" << endl;
  }
};

class Square : public Rectangle {
public:
  Square() {}
  virtual ~Square() {}
  void WhatAmI() {
    cout << "augmented object from" << endl;
    Rectangle::WhatAmI();
    cout << "to" << endl;
    cout << "a square class geometry object" << endl;
    Coucou();
  }
private:
  void Coucou() {
    cout << "Coucou from square" << endl;
  }
};


int main()
{
  Geometry geometry;
  Rectangle rectangle;
  Square square;

  cout << "\ngeometry.WhatAmI(); " << endl;
  geometry.WhatAmI();

  cout << "\nrectangle.WhatAmI(); " << endl;
  rectangle.WhatAmI();

  cout << "\nsquare.WhatAmI(); " << endl;
  square.WhatAmI();
}
