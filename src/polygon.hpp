#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"


/*! Structures a representation and behavior of a polygon */

class Polygon: public GraphicObject {
private:
  vector<Coordinate*> points;
  string name;
  Type type;

public:
	Polygon(string name, vector<Coordinate*> &points) {
    this->points = points;
    this->name = name;
    this->type = POLYGON;
  }

	~Polygon() {
    vector<Coordinate*>::iterator it;
    for(it = points.begin(); it != points.end(); it++) {
      delete *it;
    }
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
};

#endif
