#ifndef SCN_HPP
#define SCN_HPP

#include "matrix.hpp"

/*! Transform world coordinates to normalized system coordinates. */

class Scn {
  public:
    Scn () {}

    ~Scn () {}

  void transformation(GraphicObject* obj, Coordinate* geometriCenter, Coordinate* factor, double angle) {
    double radians = (angle*M_PI)/180;
    Coordinate negCoord(-geometriCenter->getX(), -geometriCenter->getY());

    Matrix translationMatrix(Matrix::translationVectorToMatrix(&negCoord));
    Matrix rotationMatrix(Matrix::rotationVectorToMatrix(radians));
    Matrix scalingMatrix(Matrix::scalingVectorToMatrix(factor));

    Matrix descSCN = translationMatrix * rotationMatrix * scalingMatrix;

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinateToMatrix(*it));

      Matrix translatedObject = descSCN * coord;

      (*it)->setXns(translatedObject.getMatrix()[0][0]);
      (*it)->setYns(translatedObject.getMatrix()[1][0]);
    }

  }
};

#endif
