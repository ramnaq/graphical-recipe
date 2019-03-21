#ifndef POINT_HPP
#define POINT_HPP


/*! Structures a representation and behavior of a "line segment" */

class Point: public GraphicObject {
private:
  vector<Coordenada*> pointCoordinate;
  string name;
  Type type;

public:
  // TODO Homogeinizar a passagem de parametros dos objetos (Ou passa x/y ou passa
  // objeto coordenada (Prefiro esse))
	Point(string name, double x, double y) {
    Coordenada* point = new Coordenada(x, y);
    pointCoordinate.push_back(point);
    this->name = name;
    this->type = POINT;
  }

	~Point() {
    delete pointCoordinate.front();
  }

  vector<Coordenada*> getCoordenadas() {
    return pointCoordinate;
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }
};

#endif
