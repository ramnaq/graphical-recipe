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

    Matrix translation(Matrix::translation3DVectorToMatrix(rotationVector));
    Matrix rotationX(ObjectTransformation::getRotationMatrix(ObjectTransformation::getAngleX(rotationVector), 1));
    Matrix rotationZ(ObjectTransformation::getRotationMatrix(ObjectTransformation::getAnguloZ(rotationVector), 3));
    Matrix rotationMatrix(ObjectTransformation::getRotationMatrix(radians, whichAxis));
    Matrix rotationZinv(ObjectTransformation::getRotationMatrix(-ObjectTransformation::getAnguloZ(rotationVector), 3));
    Matrix rotationXinv(ObjectTransformation::getRotationMatrix(-ObjectTransformation::getAngleX(rotationVector), 1));
    Matrix translationInv(Matrix::translation3DVectorToMatrix(&negRotationVector));

    Matrix result = translation * rotationX * rotationZ * rotationMatrix * rotationZinv * rotationXinv * translationInv;

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix rotatedObject = result * coord;

      (*it)->setX(rotatedObject.getMatrix()[0][0]);
      (*it)->setY(rotatedObject.getMatrix()[1][0]);
      (*it)->setZ(rotatedObject.getMatrix()[2][0]);
    }
  }

  static void cameraRotation(vector<Coordinate*> coordinates, Coordinate* geoCenter, double angleX, double angleY, double angleZ) {
    Coordinate negRotationVector(-geoCenter->getX(), -geoCenter->getY(), -geoCenter->getZ());
    double radiansX = (angleX*M_PI)/180;
    double radiansY = (angleY*M_PI)/180;
    double radiansZ = (angleZ*M_PI)/180;

    Matrix translation(Matrix::translation3DVectorToMatrix(geoCenter));

    Matrix rotationMatrixX(Matrix::rotationXVectorToMatrix(radiansX));
    Matrix rotationMatrixY(Matrix::rotationYVectorToMatrix(radiansY));
    Matrix rotationMatrixZ(Matrix::rotationZVectorToMatrix(radiansZ));

    Matrix translationInv(Matrix::translation3DVectorToMatrix(&negRotationVector));

    Matrix rotationMatrix = translation * rotationMatrixX * rotationMatrixY * rotationMatrixZ * translationInv;

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix rotatedObject = rotationMatrix * coord;
      //cout << coord.getMatrix()[0][0] << " " << coord.getMatrix()[1][0] << " " << coord.getMatrix()[2][0] << " --> " << rotatedObject.getMatrix()[0][0] << " " << rotatedObject.getMatrix()[1][0] << " " << rotatedObject.getMatrix()[2][0] << endl;
      (*it)->setXop(rotatedObject.getMatrix()[0][0]);
      (*it)->setYop(rotatedObject.getMatrix()[1][0]);
      (*it)->setZop(rotatedObject.getMatrix()[2][0]);
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

  static double getAngleX(Coordinate* coord) {
    if (coord->getZ() == 0) {
      if (coord->getY() > 0) {
        return 0;
      } else {
        return 0;
      }
    } else {
      double angulo = atan(coord->getY()/coord->getZ());
      angulo = (angulo * M_PI) / 180;
      return angulo;
    }
  }

  static double getAnguloZ(Coordinate* coord) {
    if (coord->getX() == 0) {
      if (coord->getY() > 0) {
        return 0;
      } else {
        return 0;
      }
    } else {
      double angulo = atan(coord->getY()/coord->getX());
      angulo = (angulo * M_PI) / 180;
      return angulo;
    }
  }

};


#endif
