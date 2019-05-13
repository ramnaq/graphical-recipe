#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>

#include "coordinate.hpp"
#include "enum.hpp"

using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class GraphicObject {
protected:
	string name;
	Type type;
	double cx, cy, cz;

public:
	GraphicObject(string name,  Type type) {
		this->name = name;
		this->type = type;
	}

	~GraphicObject() {}

	string getObjectName() {
		return this->name;
	}

	Type getType() {
		return this->type;
	}

	Coordinate getGeometricCenter() {
		return Coordinate(cx, cy, cz);
	}

	virtual void computeGeometricCenter()=0;
};

#endif
