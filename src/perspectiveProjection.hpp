#ifndef PERSPECTIVE_HPP
#define PERSPECTIVE_HPP

#include "matrix.hpp"
#include "window.hpp"

/*! Transform world coordinates to normalized system coordinates. */

class Perspective {
private:
  double angleX, angleY;

public:
  Perspective () {}
  ~Perspective () {}

  Coordinate intersection(Coordinate* obj, double cop) {
    double xp, yp;

    xp = obj->getXop() / (obj->getZop() / d);
    yp = obj->getYop() / (obj->getZop() / d);

    return Coordinate(xp, yp, cop);
  }

  void computeAngle(Window* window, Coordinate* vrp) {
    Coordinate negCoord(-vrp->getX(), -vrp->getY(), -vrp->getZ());
    Matrix trans = Matrix::translation3DVectorToMatrix(&negCoord);

    vector<Coordinate*> coordinates = window->getCoordinates();
    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix translatedObject = trans * coord;

      (*it)->setXop(-translatedObject.getMatrix()[0][0]);
      (*it)->setYop(-translatedObject.getMatrix()[1][0]);
      (*it)->setZop(-translatedObject.getMatrix()[2][0]);
    }

    Coordinate* w1t = window->getCoordinates()[0];
    Coordinate* w2t = window->getCoordinates()[1];

    // Cross product
    double x = w1t->getYop()*w2t->getZop() - w2t->getYop()*w1t->getZop();
    double y = w1t->getZop()*w2t->getXop() - w1t->getXop()*w2t->getZop();
    double z = w1t->getXop()*w2t->getYop() - w2t->getXop()*w1t->getYop();

    // Angles
    this->angleX = (y == 0 || z == 0) ? 0 : (atan(y/z)*M_PI)/180;
    this->angleY = (x == 0 || z == 0) ? 0 : (atan(x/z)*M_PI)/180;
  }

  void transformation(vector<Coordinate*> coord, double cop) {
    // Steps 1,2 e 3
    Coordinate negCoord(-copCoord->getX(), -copCoord->getY(), -copCoord->getZ());

    Matrix trans = Matrix::translation3DVectorToMatrix(&negCoord);
    Matrix rotx  = Matrix::rotationXVectorToMatrix(this->angleX);
    Matrix roty  = Matrix::rotationYVectorToMatrix(this->angleY);

    Matrix transform = trans * rotx * roty;

    vector<Coordinate*>::iterator it;
    for(it = coord.begin(); it != coord.end(); it++) {
        Matrix coord(Matrix::coordinate3DToMatrix((*it)));

        Matrix translatedObject = transform * coord;

        (*it)->setXop(translatedObject.getMatrix()[0][0]);
        (*it)->setYop(translatedObject.getMatrix()[1][0]);
        (*it)->setZop(translatedObject.getMatrix()[2][0]);

        // Compute intersection
        Coordinate x = intersection(*it, cop);
        (*it)->setXop(x.getX());
        (*it)->setYop(x.getY());
    }

  }
};

#endif
