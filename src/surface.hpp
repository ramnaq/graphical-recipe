#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "object3D.hpp"

using namespace std;

class Surface: public Object3D {
protected:
  vector<Curve*> curves;

public:
  Surface(string name) : Object3D(name) {
    this->type = SURFACE;
  }

  Surface(string name, vector<Curve*> &curves_) :
      Object3D(name) {
	  this->curves = curves_;
    this->type = SURFACE;
  }

  ~Surface() {
    vector<Curve*>::iterator it;
    for(it = curves.begin(); it != curves.end(); it++) {
      delete *it;
    }
  }

  vector<Curve*> getCurves() {
    return this->curves;
  }
};

#endif  //!< SURFACE_HPP

