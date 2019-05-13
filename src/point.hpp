#ifndef POINT_HPP
#define POINT_HPP

#include "graphicObject2D.hpp"

/*! Structures a representation and behavior of a "line segment" */

class Point: public GraphicObject2D {

public:
  Point(string name, vector<Coordinate*> &pointCoordinate) :
    GraphicObject2D(name, POINT, pointCoordinate) {

		}

};

#endif
