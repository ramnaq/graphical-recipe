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
	vector<Coordinate*> coordinateList;
	vector<Coordinate*> windowPoints;
	double cx, cy, cz;
	bool visible;

public:
	// TODO Temporary
	GraphicObject(string name,  Type type) {
		this->name = name;
		this->type = type;
		this->visible = true;
	}

	GraphicObject(string name,  Type type, vector<Coordinate*> &coordinateList) {
		this->name = name;
		this->type = type;
		this->coordinateList = coordinateList;
		this->visible = true;
		this->windowPoints = {};
		computeGeometricCenter();
	}

	// TODO descomentar
	~GraphicObject() {
		// vector<Coordinate*>::iterator it;
		// for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
		// 	delete *it;
		// }
	}

	string getObjectName() {
		return this->name;
	}

	Type getType() {
		return this->type;
	}

	bool isVisible() {
		return this->visible;
	}

	void setVisibility(bool updateVisibility) {
		this->visible = updateVisibility;
	}

	vector<Coordinate*> getCoordinates() {
		return coordinateList;
	}

	vector<Coordinate*> getWindowPoints() {
		return windowPoints;
	}

	void updateWindowPoints(vector<Coordinate*> newPoints) {
		this->windowPoints = newPoints;
	}

	Coordinate getGeometricCenter() {
		if (type != OBJECT3D)
			computeGeometricCenter();
		return Coordinate(cx, cy, cz);
	}

	void computeGeometricCenter() {
		cx = 0;
		cy = 0;
		cz = 0;
		vector<Coordinate*>::iterator it;
		for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
			cx += (*it)->getX();
			cy += (*it)->getY();
			cz += (*it)->getZ();
		}
		cx = cx / coordinateList.size();
		cy = cy / coordinateList.size();
		cz = cz / coordinateList.size();
	}
};

#endif
