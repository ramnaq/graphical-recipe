#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>

#include "coordinate.hpp"
#include "enum.hpp"


using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class GraphicObject {
private:
	string name;
	Type type;
	vector<Coordinate*> coordinateList;
	double cx, cy;
	bool visible;

public:
	GraphicObject(string name,  Type type, vector<Coordinate*> &coordinateList) {
		this->name = name;
		this->type = type;
		this->coordinateList = coordinateList;
		this->visible = true;
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

	bool isVisible() {
		return this->visible;
	}

	void setVisibility(bool updateVisibility) {
		this->visible = updateVisibility;
	}

	vector<Coordinate*> getCoordinates() {
		computeGeometricCenter();
		return coordinateList;
	}

	void updatePoints(vector<Coordinate*> newPoints) {
		this->coordinateList = newPoints;
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
