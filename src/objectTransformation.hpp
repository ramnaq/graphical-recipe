#ifndef OBJECTTRANSFORMATION_HPP
#define OBJECTTRANSFORMATION_HPP

#include "matrix.hpp"

/*! Applies translation, scaling or rotation transformations to an object. */

class ObjectTransformation {

public:

  static void translation(GraphicObject* obj, Coordinate* translationVector) {
    Matrix translationMatrix(Matrix::translationVectorToMatrix(translationVector));

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinateToMatrix(*it));

      Matrix translatedObject = translationMatrix * coord;

      (*it)->setX(translatedObject.getMatrix()[0][0]);
      (*it)->setY(translatedObject.getMatrix()[1][0]);
    }
  }

  static void scaling(GraphicObject* obj, Coordinate* scalingVector) {
    Coordinate objCenter = obj->getGeometricCenter();
    Coordinate negativeObjCenter(-objCenter.getX(), -objCenter.getY());

    Matrix scalingMatrix(Matrix::scalingVectorToMatrix(scalingVector));
    Matrix translationMatrix1(Matrix::translationVectorToMatrix(&objCenter));
    Matrix translationMatrix2(Matrix::translationVectorToMatrix(&negativeObjCenter));

    Matrix scalingOperation = translationMatrix1 * scalingMatrix * translationMatrix2;

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinateToMatrix(*it));

      Matrix scaledObject = scalingOperation * coord;

      (*it)->setX(scaledObject.getMatrix()[0][0]);
      (*it)->setY(scaledObject.getMatrix()[1][0]);
    }
  }

  static void rotation(GraphicObject* obj, double angle, Coordinate* rotationVector) {
    double radians = (angle*M_PI)/180;
    Matrix rotationMatrix(Matrix::rotationVectorToMatrix(radians));
    Matrix translationMatrix1(Matrix::translationVectorToMatrix(rotationVector));
    Coordinate negativeObjCenter(-rotationVector->getX(), -rotationVector->getY());
    Matrix translationMatrix2(Matrix::translationVectorToMatrix(&negativeObjCenter));

    Matrix rotationOperation = translationMatrix1 * rotationMatrix * translationMatrix2;

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinateToMatrix(*it));

      Matrix scaledObject = rotationOperation * coord;

      (*it)->setX(scaledObject.getMatrix()[0][0]);
      (*it)->setY(scaledObject.getMatrix()[1][0]);
    }
  }

};

#endif
