#ifndef CURVE3D_HPP
#define CURVE3D_HPP

using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class Curve3D: public Object3D {
protected:
  vector<Curve*> curves;

public:
  Curve3D(string name, vector<Curve*> &curves_) :
      Object3D(name) {
	  this->curves = curves_;
    this->type = CURVE3D;
  }

  ~Curve() {
    vector<Coordinate*>::iterator it;
    for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
	  delete *it;
    }
  }

};

#endif

