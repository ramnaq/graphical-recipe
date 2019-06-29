#ifndef CURVE_HPP
#define CURVE_HPP

#include "graphicObject2D.hpp"

using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class Curve: public GraphicObject2D {
protected:
	vector<Coordinate*> windowPoints;
  bool visibility;

public:
  Curve(string name) : GraphicObject2D(name, CURVE) {
    this->windowPoints = {};
    this->visibility = true;
  }

  Curve(string name,  Type type, vector<Coordinate*> &coordinateList) :
      GraphicObject2D(name, type, coordinateList) {
    this->windowPoints = {};
    this->visibility = true;
  }

  ~Curve() {
    vector<Coordinate*>::iterator it;
    for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
	  delete *it;
    }
  }

  void setVisibility(bool updateVisibility) {
    this->visibility = updateVisibility;
  }

  bool isVisible() {
    return this->visibility;
  }

  vector<Coordinate*> getWindowPoints() {
    return windowPoints;
  }

  void addCoordinate(Coordinate* c) {
    this->coordinateList.push_back(c);
  }

  void updateCoordinateList(vector<Coordinate*> v) {
    this->coordinateList = v;
  }

  void updateWindowPoints(vector<Coordinate*> newPoints) {
    this->windowPoints = newPoints;
  }

};

#endif
