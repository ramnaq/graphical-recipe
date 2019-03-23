#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>


//! Window is the visible area of a graphical world.
/*!
 * The graphical world moves (horizontally, vertically, diagonally) and the window
 * shows a limited area of it.
 */

class Window {
  private:
    Coordinate *coordMin;
    Coordinate *coordMax;
  public:
  	Window(double xMin, double yMin, double xMax, double yMax) {
      coordMin = new Coordinate(xMin, yMin);
      coordMax = new Coordinate(xMax, yMax);
    }

    Coordinate* getCoordMin() {
      return coordMin;
    }

    Coordinate* getCoordMax() {
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
