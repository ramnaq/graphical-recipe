#ifndef LINE_HPP
#define LINE_HPP

#include "graphicObject2D.hpp"

/*! Structures a representation and behavior of a "line segment" */

class Line: public GraphicObject2D {
public:
	Line(string name,  vector<Coordinate*> &lineCoordinates) :
		GraphicObject2D(name, LINE, lineCoordinates) {}
};

#endif
