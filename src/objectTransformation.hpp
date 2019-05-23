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
    double cx = rotationVector->getX();
    double cy = rotationVector->getY();
    double cz = rotationVector->getZ();
    double d = sqrt((cy*cy) + (cz*cz));

    Coordinate negRotationVector(-rotationVector->getX(), -rotationVector->getY(), -rotationVector->getZ());

    // Matrix translation(Matrix::translation3DVectorToMatrix(&negRotationVector));
    // Matrix rotationAlpha(Matrix::genericRotationAlpha(cy, cz, d));
    // Matrix rotationBeta(Matrix::genericRotationBeta(-cx, d));
    // Matrix rotationMatrix(ObjectTransformation::getRotationMatrix(radians, whichAxis));
    // Matrix rotationAlphainv(Matrix::genericRotationAlpha(-cy, cz, d));
    // Matrix rotationBetainv(Matrix::genericRotationBeta(cx, d));
    // Matrix translationInv(Matrix::translation3DVectorToMatrix(rotationVector));

    Matrix translation(Matrix::translation3DVectorToMatrix(&negRotationVector));
    Matrix rotationAlpha(ObjectTransformation::getRotationMatrix(ObjectTransformation::getAnguloX(rotationVector), 1));
    Matrix rotationBeta(ObjectTransformation::getRotationMatrix(ObjectTransformation::getAnguloZ(rotationVector), 3));
    Matrix rotationMatrix(ObjectTransformation::getRotationMatrix(radians, whichAxis));
    Matrix rotationAlphainv(ObjectTransformation::getRotationMatrix(-ObjectTransformation::getAnguloX(rotationVector), 1));
    Matrix rotationBetainv(ObjectTransformation::getRotationMatrix(-ObjectTransformation::getAnguloZ(rotationVector), 3));
    Matrix translationInv(Matrix::translation3DVectorToMatrix(rotationVector));

    Matrix result = translation * rotationAlpha * rotationBeta * rotationMatrix * rotationBetainv * rotationAlphainv * translationInv;

    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix rotatedObject = result * coord;

      (*it)->setX(rotatedObject.getMatrix()[0][0]);
      (*it)->setY(rotatedObject.getMatrix()[1][0]);
      (*it)->setZ(rotatedObject.getMatrix()[2][0]);
    }
  }

  static void cameraRotation(vector<Coordinate*> coordinates, double angleX, double angleY, double angleZ) {
    double radiansX = (angleX*M_PI)/180;
    double radiansY = (angleY*M_PI)/180;
    double radiansZ = (angleZ*M_PI)/180;

    Matrix rotationMatrixX(Matrix::rotationXVectorToMatrix(radiansX));
    Matrix rotationMatrixY(Matrix::rotationYVectorToMatrix(radiansY));
    Matrix rotationMatrixZ(Matrix::rotationZVectorToMatrix(radiansZ));

    Matrix rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

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


  static double getAnguloX(Coordinate* coord) {
  if (coord->getZ() == 0) {
      if (coord->getY() > 0) {
        return 90;
      } else {
        return -90;
      }
    } else {
      double angulo = atan(coord->getY()/coord->getZ());
      angulo = (angulo * 180.0) / M_PI;
      return angulo;
    }
  }

  //! Método que diz o angulo em que um vetor se encontra em relação ao eixo Y.
  /*!
    /param coord é um ponto que indica um vetor
    /return o angulo entre o vetor e o eixo Y
  */
  static double getAnguloY(Coordinate* coord) {
    if (coord->getZ() == 0) {
      if (coord->getX() > 0) {
        return 90;
      } else {
        return -90;
      }
    } else {
      double angulo = atan(coord->getX()/coord->getZ());
      angulo = (angulo * 180.0) / M_PI;
      return angulo;
    }
  }

  //! Método que diz o angulo em que um vetor se encontra em relação ao eixo Z.
  /*!
    /param coord é um ponto que indica um vetor
    /return o angulo entre o vetor e o eixo X
  */
  static double getAnguloZ(Coordinate* coord) {
    if (coord->getX() == 0) {
      if (coord->getY() > 0) {
        return 90;
      } else {
        return -90;
      }
    } else {
      double angulo = atan(coord->getY()/coord->getX());
      angulo = (angulo * 180.0) / M_PI;
      return angulo;
    }
  }

};


#endif
