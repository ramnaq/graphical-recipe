#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"


/*! Structures a representation and behavior of a "line segment" */

class Line: public GraphicObject {
private:
  string name;
  Type type;
  vector<Coordinate*> lineCoordinates;
  double cx, cy;

public:
	Line(string name,  Coordinate* a, Coordinate* b) {
    lineCoordinates.push_back(a);
    lineCoordinates.push_back(b);
    this->name = name;
    this->type = LINE;

    double cx = (a->getX() + b->getX()) / 2;
    double cy = (a->getY() + b->getY()) / 2;
  }

	~Line() {
    delete this->lineCoordinates.front();
    delete this->lineCoordinates.back();
  }

  vector<Coordinate*> getCoordinates() {
    return lineCoordinates;
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
