#ifndef POINT_HPP
#define POINT_HPP

#include <stdio.h>


/*! Structures a representation and behavior of a "line segment" */

class Point: public GraphicObject {

public:
  Point(string name, vector<Coordinate*> &pointCoordinate) :
    GraphicObject(name, POINT, pointCoordinate) {}

};

#endif
