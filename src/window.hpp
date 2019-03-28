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
      this->coordMin = new Coordinate(xMin, yMin);
      this->coordMax = new Coordinate(xMax, yMax);
    }

    ~Window() {
      delete this->coordMin;
      delete this->coordMax;
    }

    Coordinate* getCoordMin() {
      return coordMin;
    }

    Coordinate* getCoordMax() {
      return coordMax;
    }

    void zoomIn(double step) {
      coordMin->setX( coordMin->getX() + step);
      coordMin->setY( coordMin->getY() + step);
      coordMax->setX( coordMax->getX() - step);
      coordMax->setY( coordMax->getY() - step);
    }

    void zoomOut(double step) {
      coordMin->setX( coordMin->getX() - step);
      coordMin->setY( coordMin->getY() - step);
      coordMax->setX( coordMax->getX() + step);
      coordMax->setY( coordMax->getY() + step);
    }

    void goRight(double step) {
      coordMin->setX( coordMin->getX() + step);
      coordMax->setX( coordMax->getX() + step);
    }

    void goLeft(double step) {
      coordMin->setX( coordMin->getX() - step);
      coordMax->setX( coordMax->getX() - step);
    }

    void goUp(double step) {
      coordMin->setY( coordMin->getY() + step);
      coordMax->setY( coordMax->getY() + step);
    }

    void goDown(double step) {
      coordMin->setY( coordMin->getY() - step);
      coordMax->setY( coordMax->getY() - step);
    }

    void goUpLeft(double step) {
      coordMin->setX( coordMin->getX() - step);
      coordMin->setY( coordMin->getY() + step);
      coordMax->setX( coordMax->getX() - step);
      coordMax->setY( coordMax->getY() + step);
    }

    void goUpRight(double step) {
      coordMin->setX( coordMin->getX() + step);
      coordMin->setY( coordMin->getY() + step);
      coordMax->setX( coordMax->getX() + step);
      coordMax->setY( coordMax->getY() + step);
    }

    void goDownLeft(double step) {
      coordMin->setX( coordMin->getX() - step);
      coordMin->setY( coordMin->getY() - step);
      coordMax->setX( coordMax->getX() - step);
      coordMax->setY( coordMax->getY() - step);
    }

    void goDownRight(double step) {
      coordMin->setX( coordMin->getX() + step);
      coordMin->setY( coordMin->getY() - step);
      coordMax->setX( coordMax->getX() + step);
      coordMax->setY( coordMax->getY() - step);
    }
};

#endif
