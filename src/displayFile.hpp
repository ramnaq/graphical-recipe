#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include "listEnc.hpp"
#include "point.hpp"


class DisplayFile {

private:
	ListaEnc<GraphicObject*>* displayFile;

public:

	DisplayFile () {
		displayFile = new ListaEnc<GraphicObject*>();
	}

	Elemento<GraphicObject*>* getHead() {
		return displayFile->getHead();
	}

	void insert(GraphicObject* x) {
		displayFile->adiciona(x);
	}

	void remove(int index) {
		delete displayFile->retiraDaPosicao(index);
	}

	ListaEnc<GraphicObject*>* getObjs() {
        return displayFile;
	}

	GraphicObject* getElementoNoIndice(int index) {
		return displayFile->elementoNoIndice(index);
	}

};

#endif
