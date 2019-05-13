#ifndef CURVE_HPP
#define CURVE_HPP

#include "graphicObject2D.hpp"

using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class Curve: public GraphicObject2D {
protected:
	vector<Coordinate*> coordinateList;
  vector<Coordinate*> windowPoints;
  bool visibility;

public:
	Curve(string name,  Type type, vector<Coordinate*> &coordinateList) :
    GraphicObject2D(name, type, coordinateList) {
			this->windowPoints = {};
      this->visibility = true;
	}

	~Curve() {
		vector<Coordinate*>::iterator it;
		for(it = coordinateList.begin(); it != coordinateList.end(); it++) {
			delete *it;
		}
	}

  void setVisibility(bool updateVisibility) {
    this->visibility = updateVisibility;
  }

  bool isVisible() {
    return this->visibility;
  }

  vector<Coordinate*> getWindowPoints() {
    return windowPoints;
  }

  void updateWindowPoints(vector<Coordinate*> newPoints) {
    this->windowPoints = newPoints;
  }

};

#endif
