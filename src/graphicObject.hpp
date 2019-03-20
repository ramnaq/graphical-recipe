#ifndef GRAPHICOBJECT_HPP
#define GRAPHICOBJECT_HPP

#include "coordenada.hpp"

class GraphicObject {
public:
	GraphicObject() {

  }

	virtual Coordenada* getCoordenada()=0;
	virtual void setCoordenada(Coordenada *newCoordenada)=0;

};

#endif
