#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include "coordenada.hpp"

class GraphicObject {
public:
	GraphicObject() {

  }

	// TODO RETORNAR VETOR DE COORDENADAS
	virtual Coordenada* getCoordenada()=0;
	virtual void setCoordenada(Coordenada *newCoordenada)=0;
	virtual Coordenada* getCoordenadaIn()=0;
	virtual Coordenada* getCoordenadaFin()=0;

};

#endif
