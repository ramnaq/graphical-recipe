#ifndef SCN_HPP
#define SCN_HPP

#include "matrix.hpp"

/*! Transform world coordinates to normalized system coordinates. */

class Scn {
  public:
    Scn () {}

    ~Scn () {}

  void transformation(vector<Coordinate*> coordObj, Coordinate* geometriCenter, Coordinate* factor, double angle) {
    double radians = (angle*M_PI)/180;
    Coordinate negCoord(-geometriCenter->getX(), -geometriCenter->getY());

    Matrix translationMatrix(Matrix::translationVectorToMatrix(&negCoord));
    Matrix rotationMatrix(Matrix::rotationVectorToMatrix(radians));
    Matrix scalingMatrix(Matrix::scalingVectorToMatrix(factor));

    Matrix descSCN = translationMatrix * rotationMatrix * scalingMatrix;

    vector<Coordinate*>::iterator it;
    for(it = coordObj.begin(); it != coordObj.end(); it++) {
      Matrix coord(Matrix::coordinateOppToMatrix(*it));

      Matrix translatedObject = descSCN * coord;

      (*it)->setXns(translatedObject.getMatrix()[0][0]);
      (*it)->setYns(translatedObject.getMatrix()[1][0]);
    }

  }
};

#endif
