#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"

class Polygon: public GraphicObject {
private:
  vector<Coordenada*> points;
  string name;
  Type type;

public:
	Polygon(string name, vector<Coordenada*> &points) {
    this->points = points;
    this->name = name;
    this->type = POLYGON;
  }

	~Polygon() {
    vector<Coordenada*>::iterator it;
    for(it = points.begin(); it != points.end(); it++) {
      delete *it;
    }
  }

  vector<Coordenada*> getCoordenadas() {
    return points;
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }
};

#endif
