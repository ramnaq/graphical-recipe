#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"


/*! Structures a representation and behavior of a "line segment" */

class Line: public GraphicObject {
private:
  string name;
  Type type;
  vector<Coordenada*> lineCoordinates;

public:
	Line(string name,  Coordenada *a, Coordenada *b) {
    lineCoordinates.push_back(a);
    lineCoordinates.push_back(b);
    this->name = name;
    this->type = LINE;
  }

	~Line() {
    delete this->lineCoordinates.front();
    delete this->lineCoordinates.back();
  }

  vector<Coordenada*> getCoordenadas() {
    return lineCoordinates;
  }

  string getObjectName() {
    return name;
  }

  Type getType() {
    return type;
  }
};

#endif
