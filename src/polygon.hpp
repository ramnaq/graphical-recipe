#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "graphicObject2D.hpp"

/*! Structures a representation and behavior of a polygon */

class Polygon: public GraphicObject2D {
private:
	vector<Coordinate*> windowPoints;
	bool filled;
	bool visibility;

public:
	Polygon(string name, vector<Coordinate*> &polygonCoordinates, bool filled) :
		GraphicObject2D(name, POLYGON, polygonCoordinates) {
			this->filled = filled;
			this->visibility = true;
			this->windowPoints = {};
	}

	~Polygon() {
		vector<Coordinate*>::iterator it;
		for(it = windowPoints.begin(); it != windowPoints.end(); it++) {
			delete *it;
		}
	}

	void setVisibility(bool updateVisibility) {
		this->visibility = updateVisibility;
	}

	bool isVisible() {
		return this->visibility;
	}

	bool fill() {
		return filled;
	}

	void updateWindowPoints(vector<Coordinate*> newPoints) {
		this->windowPoints = newPoints;
	}

	vector<Coordinate*> getWindowPoints() {
		return this->windowPoints;
	}

};

#endif
