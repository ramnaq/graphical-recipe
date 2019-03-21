#ifndef POINT_HPP
#define POINT_HPP

class Point: public GraphicObject {
private:
  Coordenada *point;
  string name;
  Type type;

public:
	Point(string name, double x, double y) {
    point = new Coordenada(x, y);
    this->name = name;
    this->type = POINT;
  }

	~Point() {
    delete point;
  }

  Coordenada* getCoordenada() {
    return point;
  }

  void setCoordenada(Coordenada *newCoordenada) {
    point->setX(newCoordenada->getX());
    point->setY(newCoordenada->getY());
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }

  Coordenada* getCoordenadaIn(){}
  Coordenada* getCoordenadaFin(){}
  vector<Coordenada*> getPolygonPoints(){}

};

#endif
