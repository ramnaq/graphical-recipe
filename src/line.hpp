#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"

class Line: public GraphicObject {
private:
  Point *a;
  Point *b;
  string name;
  Type type;

public:
	Line(string name,  Coordenada *a, Coordenada *b) {
    this->a = new Point("Point A", a->getX(), a->getY());
    this->b = new Point("Point B", b->getX(), b->getY());
    this->name = name;
    this->type = LINE;
  }

	~Line() {
    delete this->a;
    delete this->b;
  }

  Coordenada* getCoordenadaIn() {
    return a->getCoordenada();
  }

  Coordenada* getCoordenadaFin() {
    return b->getCoordenada();
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }

  Coordenada* getCoordenada() {}
  void setCoordenada(Coordenada *newCoordenada) {}
  vector<Coordenada*> getPolygonPoints() {}
};

#endif
