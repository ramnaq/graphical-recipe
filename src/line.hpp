#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"
#include <stdio.h>


/*! Structures a representation and behavior of a "line segment" */

class Line: public GraphicObject {
private:
  string name;
  Type type;
  vector<Coordinate*> lineCoordinates;

public:
  Line(string name,  Coordinate& a, Coordinate& b) {
    lineCoordinates.push_back(&a);
    lineCoordinates.push_back(&b);
    this->name = name;
    this->type = LINE;
  }

	~Line() {
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
};

#endif

