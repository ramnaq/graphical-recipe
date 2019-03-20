#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"

class Line: public GraphicObject {
private:
  Point *a;
  Point *b;
  string name;

public:
	Line(string name, Coordenada *a, Coordenada *b) {
    this->a = new Point("Point A", a->getX(), a->getY());
    this->b = new Point("Point B", b->getX(), b->getY());
    this->name = name;
  }

	virtual ~Line() {
    delete this->a;
    delete this->b;
  }

  Coordenada* getCoordenadaIn() {
    return a->getCoordenada();
  }

  Coordenada* getCoordenadaFin() {
    return b->getCoordenada();
  }

  Coordenada* getCoordenada() {}
  void setCoordenada(Coordenada *newCoordenada) {}
};

#endif
