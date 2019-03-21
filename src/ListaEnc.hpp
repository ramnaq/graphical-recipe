#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "Elemento.hpp"
#include <cstdlib>
template<typename T>

class ListaEnc {
 public:

	ListaEnc() {
	  size = -1;
	  head = NULL;
	}

	~ListaEnc() {
	    destroiLista();
	}

	void adicionaNoInicio(const T& dado) {
	   Elemento<T>* novo = new Elemento<T>(dado, head);
	   if (novo == NULL) throw -1;
	   head = novo;
	   size++;
	}

	T retiraDoInicio() {
	    if (listaVazia()) throw -1;
	    Elemento<T>* saiu = head;
	    T volta = saiu->getInfo();
	    head = saiu->getProximo();
	    size--;
	    free(saiu);
	    return volta;
	}

	void eliminaDoInicio() {
	    if (listaVazia()) throw -1;
	    Elemento<T>* saiu = head;
	    head = saiu->getProximo();
	    size--;
	    free(saiu);
	}

	void adicionaNaPosicao(const T& dado, int pos) {
	    if (pos > size + 1) throw -1;
	    if (pos == 0) {
	        adicionaNoInicio(dado);
	    } else {
	        Elemento<T>* novo = new Elemento<T>(dado, NULL);
	        if (novo == NULL) throw -1;
	        Elemento<T>* anterior = head;
	        for (int i = 0; i < pos - 1; i++) {
	            anterior = anterior->getProximo();
	        }
	        novo->setProximo(anterior->getProximo());
	        anterior->setProximo(novo);
	        size++;
	   }
	}

	int posicao(T dado) {
	    if (listaVazia()) throw -1;
	    Elemento<T>* elemAux = head;
	    T aux = elemAux->getInfo();
	    for (int i = 0; i <= size; i++) {
	         if (aux == dado) return i;
	         if (elemAux->getProximo() == NULL) throw -2;
	         elemAux = elemAux->getProximo();
	         aux = elemAux->getInfo();
	    }
	}

	T* posicaoMem(const T& dado) const {
	    if (listaVazia()) throw -1;
	    Elemento<T>* elemAux = head;
	    T aux = elemAux->getInfo();
	    for (int i = 0; i <= size; i++) {
	         if (aux == dado) return elemAux;
	         if (elemAux->getProximo() == NULL) throw -1;
	         elemAux = elemAux->getProximo();
	         aux = elemAux->getInfo();
	    }
	}

	bool contem(const T& dado) {
	    if (listaVazia()) throw -1;
	    Elemento<T>* elemAux = head;
	    T aux = elemAux->getInfo();
	    for (int i = 1; i <= size+1; i++) {
	         if (aux == dado) return true;
	         if (elemAux->getProximo() == NULL) return false;
	         elemAux = elemAux->getProximo();
	         aux = elemAux->getInfo();
	    }
	}

	T retiraDaPosicao(int pos) {
	    if (listaVazia()) throw -1;
	    if (pos > size) throw -1;
	    if (pos == 0) {
	        return retiraDoInicio();
	    } else {
	        Elemento<T>* anterior = head;
	        for (int i = 0; i < pos - 1; i++) {
	            anterior = anterior->getProximo();
	        }
	        Elemento<T>* eliminar = anterior->getProximo();
	        T volta = eliminar->getInfo();
	        anterior->setProximo(eliminar->getProximo());
	        size--;
	        free(eliminar);
	        return volta;
	   }
	}

	void adiciona(const T& dado) {
	    if (listaVazia()) {
	        adicionaNoInicio(dado);
	    } else {
	        Elemento<T>* anterior = head;
	        Elemento<T>* novo = new Elemento<T>(dado, NULL);
	        if (novo == NULL) throw -1;
	        while (anterior->getProximo() != NULL) {
	            anterior = anterior->getProximo();
	        }
	        anterior->setProximo(novo);
	        size++;
	   }
	}

	T retira() {
	    if (listaVazia()) throw -1;
	    Elemento<T>* anterior;
	    Elemento<T>* atual = head;
	    while (atual->getProximo() != NULL) {
	        anterior = atual;
	        atual = atual->getProximo();
	    }
	    anterior->setProximo(NULL);
	    T volta = atual->getInfo();
	    free(atual);
	    size--;
	    return volta;
	}

	T retiraEspecifico(const T& dado) {
	     if (listaVazia()) throw -1;
	     Elemento<T>* aux = head;
	     for (int i = 0; i < size; i++) {
	        if (igual(dado, aux->getInfo())) {
	            return retiraDaPosicao(i);
	        }
	        aux = aux->getProximo();
	     }
	     throw -1;
	}

	void adicionaEmOrdem(const T& data) {
	    if (listaVazia()) return adicionaNoInicio(data);
	    Elemento<T>* atual = head;
	    int pos = 1;
	    while (atual->getProximo() != NULL && maior(data, atual->getInfo())) {
	        atual = atual->getProximo();
	        pos++;
	    }
	    if (maior(data, atual->getInfo())) adicionaNaPosicao(data, pos + 1);
	    else
	        adicionaNaPosicao(data, pos);
	}

	bool listaVazia() const {
	    return (size == -1);
	}

	bool igual(T dado1, T dado2) {
	    return (dado1 == dado2);
	}

	bool maior(T dado1, T dado2) {
	    return (dado1 > dado2);
	}

	bool menor(T dado1, T dado2) {
	    return (dado1 < dado2);
	}

	void destroiLista() {
	    while (!listaVazia()) {
	        eliminaDoInicio();
	    }
	}

	T primeiroElemento() {
	    return head->getInfo();
	}

	T elementoNoIndice(int indice) {
		if (listaVazia()) throw -1;
	    if (indice > size) throw -1;
	    if (indice == 0) {
	        return primeiroElemento();
	    } else {
	        Elemento<T>* elem = head;
	        for (int i = 0; i < indice; i++) {
	            elem = elem->getProximo();
	        }
	        T volta = elem->getInfo();
	        return volta;
	   }
	}


	Elemento<T>* getHead() {
		return head;
	}

	int getSize() {
		return size+1;
	}

	Elemento<T>* getUltimoElemento() {
		if (listaVazia()) throw -1;
	    Elemento<T>* atual = head;
	    while (atual->getProximo() != NULL) {
	        atual = atual->getProximo();
	    }
	    return atual;
	}

 private:
	Elemento<T>* head;
	int size;
};

#endif
