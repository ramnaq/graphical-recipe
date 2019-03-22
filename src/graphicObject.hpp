#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>

#include "coordinate.hpp"
#include "objectType.hpp"


using namespace std;

// TODO Passar as variaveis nome, tipo e vetor de coordenadas para ca, remover dos outros
/*! The generic type of an graphical object (point, line, polygon, etc) */

class GraphicObject {
public:
	GraphicObject() {

  }

	virtual string getObjectName()=0;
	virtual Type getType()=0;
	virtual vector<Coordinate*> getCoordinates()=0;
};

#endif

