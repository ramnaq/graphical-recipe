#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>

#include "coordinate.hpp"
#include "objectType.hpp"


using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class GraphicObject {
private:
	string name;
	Type type;
	vector<Coordinate*> coordinateList;
	double cx, cy;
public:
	GraphicObject(string name,  Type type, vector<Coordinate*> &coordinateList) {
		this->name = name;
		this->type = type;
		this->coordinateList = coordinateList;
		computeGeometricCenter();
  }

	~GraphicObject() {
		vector<Coordinate*>::iterator it;
		for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
			delete *it;
		}
	}

	string getObjectName() {
		return this->name;
	}

	Type getType() {
		return this->type;
	}

	vector<Coordinate*> getCoordinates() {
		computeGeometricCenter();
		return coordinateList;
	}

	Coordinate getGeometricCenter() {
		return Coordinate(cx, cy);
	}

	void computeGeometricCenter() {
		cx = 0;
		cy = 0;
		vector<Coordinate*>::iterator it;
		for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
			cx += (*it)->getX();
			cy += (*it)->getY();
		}
		cx = cx / coordinateList.size();
		cy = cy / coordinateList.size();
	}
};

#endif
