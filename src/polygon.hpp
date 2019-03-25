#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"


/*! Structures a representation and behavior of a polygon */

class Polygon: public GraphicObject {
private:
  vector<Coordinate*> points;
  string name;
  Type type;
  double cx;
  double cy;

public:
	Polygon(string name, vector<Coordinate*> &points) {
    this->points = points;
    this->name = name;
    this->type = POLYGON;
    computeGeometricCenter();
  }

	~Polygon() {
    vector<Coordinate*>::iterator it;
    for(it = points.begin(); it != points.end(); it++) {
      delete *it;
    }
  }

  void computeGeometricCenter() {
    cx = 0;
    cy = 0;
    vector<Coordinate*>::iterator it;
    for(it = points.begin(); it != points.end(); it++) {
      cx += (*it)->getX();
      cy += (*it)->getY();
    }
    cx = cx / points.size();
    cy = cy / points.size();
  }

  vector<Coordinate*> getCoordinates() {
    return points;
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }

  Coordinate getGeometricCenter() {
    return Coordinate(cx, cy);
  }

};

#endif
