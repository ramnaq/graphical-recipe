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
    double radians = (angle*M_PI)/180;

    Coordinate negRotationVector(-rotationVector->getX(), -rotationVector->getY(), -rotationVector->getZ());
    double cx = rotationVector->getX();
    double cy = rotationVector->getY();
    double cz = rotationVector->getZ();
    double d = sqrt((cy*cy) + (cz*cz));

    Matrix translation(Matrix::translation3DVectorToMatrix(rotationVector));
    Matrix rotationAlpha(Matrix::genericRotationAlpha(cy, cz, d));
    Matrix rotationBeta(Matrix::genericRotationBeta(cx, d));
    Matrix rotationMatrix(ObjectTransformation::getRotationMatrix(radians, whichAxis));
    Matrix rotationAlphainv(Matrix::genericRotationAlpha(cy, cz, -d));
    Matrix rotationBetainv(Matrix::genericRotationBeta(-cx, -d));
    Matrix translationInv(Matrix::translation3DVectorToMatrix(&negRotationVector));

    Matrix result = translation * rotationAlpha * rotationBeta * rotationMatrix * rotationAlphainv * rotationBetainv * translationInv;

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix rotatedObject = result * coord;

      (*it)->setX(rotatedObject.getMatrix()[0][0]);
      (*it)->setY(rotatedObject.getMatrix()[1][0]);
      (*it)->setZ(rotatedObject.getMatrix()[2][0]);
    }
  }

  static void windowRotation(vector<Coordinate*> coordinates, double angle, int whichAxis) {
    double radians = (angle*M_PI)/180;

    Matrix rotationMatrix(ObjectTransformation::getRotationMatrix(radians, whichAxis));

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix rotatedObject = rotationMatrix * coord;

      (*it)->setX(rotatedObject.getMatrix()[0][0]);
      (*it)->setY(rotatedObject.getMatrix()[1][0]);
      (*it)->setZ(rotatedObject.getMatrix()[2][0]);
    }
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
