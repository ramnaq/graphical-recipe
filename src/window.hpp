#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

class Window {
  private:
    Coordenada *coordMin;
    Coordenada *coordMax;
  public:
  	Window(double xMin, double yMin, double xMax, double yMax) {
      coordMin = new Coordenada(xMin, yMin);
      coordMax = new Coordenada(xMax, yMax);
    }

    Coordenada* getCoordMin() {
      return coordMin;
    }

    Coordenada* getCoordMax() {
      return coordMax;
    }

    void zoomIn(double passo) {
      coordMin->setX( coordMin->getX() + passo);
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setX( coordMax->getX() - passo);
      coordMax->setY( coordMax->getY() - passo);
    }

    void zoomOut(double passo) {
      coordMin->setX( coordMin->getX() - passo);
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setX( coordMax->getX() + passo);
      coordMax->setY( coordMax->getY() + passo);
    }
};

#endif
