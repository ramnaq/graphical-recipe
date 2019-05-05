#ifndef LINE_HPP
#define LINE_HPP

#include "graphicObject.hpp"

/*! Structures a representation and behavior of a "line segment" */

class Line: public GraphicObject {

public:
	Line(string name,  vector<Coordinate*> &lineCoordinates) :
		GraphicObject(name, LINE, lineCoordinates) {}
};

#endif
