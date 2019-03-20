#ifndef POINT_HPP
#define POINT_HPP

class Point: public GraphicObject {
private:
  Coordenada *point;
  string name;
public:
	Point(string name, double x, double y) {
    point = new Coordenada(x, y);
    this->name = name;
  }

	virtual ~Point() {delete point;}

  Coordenada* getCoordenada() {
    return point;
  }

  void setCoordenada(Coordenada *newCoordenada) {
    point->setX(newCoordenada->getX());
    point->setY(newCoordenada->getY());
  }

  Coordenada* getCoordenadaIn(){};
  Coordenada* getCoordenadaFin(){};

};

#endif
