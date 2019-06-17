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

  void setAllCoordinates() {
    for (int curve = 0; curve < curves.size(); curve++) {
      vector<Coordinate*> curveCoords = curves[curve]->getCoordinates();
      for (int coord = 0; coord < curveCoords.size(); coord++) {
        addCoordinate(curveCoords[coord]);
      }
    }
  }

};

#endif  //!< SURFACE_HPP

