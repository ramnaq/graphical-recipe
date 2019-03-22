#include "ListaEnc.hpp"
#include "point.hpp"

#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

class DisplayFile {

private:
	ListaEnc<GraphicObject*> *displayFile;

public:

	DisplayFile () {
		displayFile = new ListaEnc<GraphicObject*>();
	}

	Elemento<GraphicObject*>* getHead() {
		return displayFile->getHead();
	}

	void insereGraphicObject(GraphicObject* elemento) {
		displayFile->adiciona(elemento);
	}

	void inserirNovoPonto(Point* p) {
		displayFile->adiciona(p);
	}

	// void inserirNovaReta(Reta* r) {
	// 	displayFile->adiciona(r);
	// }
  //
	// void inserirNovoPoligono(Poligono* pol) {
	// 	displayFile->adiciona(pol);
	// }

	void deletarElemento(int index) {
		displayFile->retiraDaPosicao(index);
	}

	GraphicObject* getElementoNoIndice(int index) {
		return displayFile->elementoNoIndice(index);
	}

};

#endif

