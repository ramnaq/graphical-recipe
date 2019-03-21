#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include <vector>

#include "coordenada.hpp"
#include "objectType.hpp"

using namespace std;

/*! The generic type of an graphical object (point, line, polygon, etc) */

class GraphicObject {
public:
	GraphicObject() {

  }

	virtual string getObjectName()=0;
	virtual Type getType()=0;

	// TODO RETORNAR VETOR DE COORDENADAS
	virtual vector<Coordenada*> getPolygonPoints()=0;
	virtual Coordenada* getCoordenada()=0;
	virtual void setCoordenada(Coordenada *newCoordenada)=0;
	virtual Coordenada* getCoordenadaIn()=0;
	virtual Coordenada* getCoordenadaFin()=0;

};

#endif
