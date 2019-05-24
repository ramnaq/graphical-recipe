#ifndef OPP_HPP
#define OPP_HPP

#include "matrix.hpp"
#include "window.hpp"

/*! Transform world coordinates to normalized system coordinates. */

class Opp {
private:
  double angleX, angleY;

public:
  Opp () {}
  ~Opp () {}

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

    // TODO Another quick fix, but less ugly
    w1t->setXop(w1t->getX()); w1t->setYop(w1t->getY()); w1t->setZop(w1t->getZ());
    w2t->setXop(w2t->getX()); w2t->setYop(w2t->getY()); w2t->setZop(w2t->getZ());
  }

  void transformation(vector<Coordinate*> coord, Coordinate* geometriCenter) {
    Coordinate negCoord(-geometriCenter->getX(), -geometriCenter->getY(), -geometriCenter->getZ());

    Matrix trans = Matrix::translation3DVectorToMatrix(&negCoord);
    Matrix rotx  = Matrix::rotationXVectorToMatrix(this->angleX);
    Matrix roty  = Matrix::rotationYVectorToMatrix(this->angleY);

    Matrix transform = trans * rotx * roty;

    vector<Coordinate*>::iterator it;
    for(it = coord.begin(); it != coord.end(); it++) {
        Matrix coord(Matrix::coordinate3DToMatrixOp((*it)));

        Matrix translatedObject = transform * coord;

        (*it)->setXop(translatedObject.getMatrix()[0][0]);
        (*it)->setYop(translatedObject.getMatrix()[1][0]);
        (*it)->setZop(translatedObject.getMatrix()[2][0]);
    }
  }

};

#endif
