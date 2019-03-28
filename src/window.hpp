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
    Coordinate const *defaultCoordMin;
    Coordinate const *defaultCoordMax;

  public:
  	Window(double xMin, double yMin, double xMax, double yMax) {
      coordMin = new Coordinate(xMin, yMin);
      coordMax = new Coordinate(xMax, yMax);
      this->defaultCoordMin = new Coordinate(xMin, yMin);
      this->defaultCoordMax = new Coordinate(xMax, yMax);
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

    Coordinate const * getDefaultCoordMin() const {
      return this->defaultCoordMin;
	}

    Coordinate const * getDefaultCoordMax() const {
      return this->defaultCoordMax;
    }
};

#endif
