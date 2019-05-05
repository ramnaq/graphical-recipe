#ifndef POLYGON_HPP
#define POLYGON_HPP

/*! Structures a representation and behavior of a polygon */

class Polygon: public GraphicObject {
private:
	bool filled;
	
public:
	Polygon(string name, vector<Coordinate*> &polygonCoordinates, bool filled) :
		GraphicObject(name, POLYGON, polygonCoordinates) {
			this->filled = filled;
	}

	bool fill() {
		return filled;
	}

};

#endif
