#ifndef OBJECTTRANSFORMATION_HPP
#define OBJECTTRANSFORMATION_HPP

#include "matrix.hpp"
#include "orthogonalParallelProjection.hpp"

/*! Applies translation, scaling or rotation transformations to an object. */

class ObjectTransformation {

public:

  static void translation(vector<Coordinate*> coordinates, Coordinate* translationVector) {
    Matrix translationMatrix(Matrix::translation3DVectorToMatrix(translationVector));

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix translatedObject = translationMatrix * coord;

      (*it)->setX(translatedObject.getMatrix()[0][0]);
      (*it)->setY(translatedObject.getMatrix()[1][0]);
      (*it)->setZ(translatedObject.getMatrix()[2][0]);
    }
  }

  static void scaling(vector<Coordinate*> coordinates, Coordinate* objCenter, Coordinate* scalingVector) {
    Coordinate negativeObjCenter(-objCenter->getX(), -objCenter->getY(), -objCenter->getZ());

    Matrix scalingMatrix(Matrix::scaling3DVectorToMatrix(scalingVector));
    Matrix translationMatrix1(Matrix::translation3DVectorToMatrix(objCenter));
    Matrix translationMatrix2(Matrix::translation3DVectorToMatrix(&negativeObjCenter));

    Matrix scalingOperation = translationMatrix1 * scalingMatrix * translationMatrix2;

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix scaledObject = scalingOperation * coord;

      (*it)->setX(scaledObject.getMatrix()[0][0]);
      (*it)->setY(scaledObject.getMatrix()[1][0]);
      (*it)->setZ(scaledObject.getMatrix()[2][0]);
    }
  }

  static void rotation(vector<Coordinate*> coordinates, double angle, Coordinate* rotationVector, int whichAxis) {
    // Matrix rotation = getMatrix(whichAxis);
    // Matrix translation = Matrix::translation3DVectorToMatrix(rotationVector);
    // Matrix rotationX =
    // Matrix rotationZ =
    // Matrix translationInv =
    // Matrix rotationXinv =
    // Matrix rotationZinv =

  }

  static Matrix getRotationMatrix(double angle, int whichAxis) {
    switch (whichAxis) {
      case 1:
        return Matrix::rotationXVectorToMatrix(angle);
        break;
      case 2:
        return Matrix::rotationYVectorToMatrix(angle);
        break;
      case 3:
        return Matrix::rotationZVectorToMatrix(angle);
        break;
    }
  }

};

#endif
