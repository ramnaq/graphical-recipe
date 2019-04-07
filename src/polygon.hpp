#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <stdexcept>


/*! Structures a representation and behavior of a polygon */

class Polygon: public GraphicObject {

public:
  Polygon(string name, vector<Coordinate*> &polygonCoordinates) :
    GraphicObject(name, POLYGON, polygonCoordinates) {
  }

};

#endif
