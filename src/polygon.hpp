#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"

class Polygon: public GraphicObject {
private:
  vector<Coordenada*> points;
  string name;

public:
	Polygon(string name, vector<Coordenada*> &points) {
    this->points = points;
    this->name = name;
  }

	~Polygon() {
  }

  vector<Coordenada*> getPolygonPoints() {
    return points;
  }

  Coordenada* getCoordenadaIn() {}
  Coordenada* getCoordenadaFin() {}
  Coordenada* getCoordenada() {}
  void setCoordenada(Coordenada *newCoordenada) {}
};

#endif
