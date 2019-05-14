#ifndef GRAPHICOBJECT2D_HPP
#define GRAPHICOBJECT2D_HPP

#include "graphicObject.hpp"

using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class GraphicObject2D: public GraphicObject {
protected:
	vector<Coordinate*> coordinateList;

public:
	GraphicObject2D(string name,  Type type, vector<Coordinate*> &coordinateList) :
    GraphicObject(name, type) {
		this->coordinateList = coordinateList;
		computeGeometricCenter();
	}

	~GraphicObject2D() {
		vector<Coordinate*>::iterator it;
		for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
			delete *it;
		}
	}

  vector<Coordinate*> getCoordinates() {
		return this->coordinateList;
	}

	Coordinate getGeometricCenter() {
		computeGeometricCenter();
		return Coordinate(cx, cy, cz);
	}

	void computeGeometricCenter() {
		cx = 0;
		cy = 0;
		cz = 0;
		vector<Coordinate*>::iterator it;
		for(it = this->coordinateList.begin(); it != this->coordinateList.end(); it++) {
			cx += (*it)->getX();
			cy += (*it)->getY();
			cz += (*it)->getZ();
		}
		cx = cx / this->coordinateList.size();
		cy = cy / this->coordinateList.size();
		cz = cz / this->coordinateList.size();
	}
};

#endif
