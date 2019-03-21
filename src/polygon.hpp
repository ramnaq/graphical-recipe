#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"


/*! Structures a representation and behavior of a polygon */

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
  }

  vector<Coordenada*> getPolygonPoints() {
    return points;
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }

  Coordenada* getCoordenadaIn() {}
  Coordenada* getCoordenadaFin() {}
  Coordenada* getCoordenada() {}
  void setCoordenada(Coordenada *newCoordenada) {}
};

#endif
