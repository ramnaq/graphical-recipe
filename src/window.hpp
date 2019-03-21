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

    void goRight(double passo) {
      coordMin->setX( coordMin->getX() + passo);
      coordMax->setX( coordMax->getX() + passo);
    }

    void goLeft(double passo) {
      coordMin->setX( coordMin->getX() - passo);
      coordMax->setX( coordMax->getX() - passo);
    }

    void goUp(double passo) {
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goDown(double passo) {
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setY( coordMax->getY() - passo);
    }


    void goUpLeft(double passo) {
      coordMin->setX( coordMin->getX() - passo);
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setX( coordMax->getX() - passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goUpRight(double passo) {
      coordMin->setX( coordMin->getX() + passo);
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setX( coordMax->getX() + passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goDownLeft(double passo) {
      coordMin->setX( coordMin->getX() - passo);
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setX( coordMax->getX() - passo);
      coordMax->setY( coordMax->getY() - passo);
    }

    void goDownRight(double passo) {
      coordMin->setX( coordMin->getX() + passo);
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setX( coordMax->getX() + passo);
      coordMax->setY( coordMax->getY() - passo);
    }
};

#endif
