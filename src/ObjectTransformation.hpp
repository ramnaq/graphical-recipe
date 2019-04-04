#ifndef OBJECTTRANSFORMATION_HPP
#define OBJECTTRANSFORMATION_HPP

#include <math.h>

#include "Matrix.hpp"

/*! Applies translation, scaling or rotation transformations to an object. */

class ObjectTransformation {

public:
  static std::vector<std::vector<double> > coordinateToMatrix(Coordinate* coord) {
   return {{coord->getX()},
           {coord->getY()},
           {1}};
  }

  static std::vector<std::vector<double> > translationVectorToMatrix(Coordinate* coord) {
   return {{1, 0, coord->getX()},
           {0, 1, coord->getY()},
           {0, 0 , 1}};
  }

  static std::vector<std::vector<double> > scalingVectorToMatrix(Coordinate* coord) {
   return {{coord->getX(), 0, 0},
           {0, coord->getY(), 0},
           {0, 0 , 1}};
  }

  static std::vector<std::vector<double> > rotationVectorToMatrix(double angle) {
   return {{cos(angle), -sin(angle), 0},
           {sin(angle), cos(angle), 0},
           {0, 0 , 1}};
  }

  static void translation(GraphicObject* obj, Coordinate* translationVector) {
    Matrix translationMatrix(ObjectTransformation::translationVectorToMatrix(translationVector));

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(ObjectTransformation::coordinateToMatrix(*it));

      Matrix translatedObject = translationMatrix * coord;

      (*it)->setX(translatedObject.getMatrix()[0][0]);
      (*it)->setY(translatedObject.getMatrix()[1][0]);
    }
  }

  static void scaling(GraphicObject* obj, Coordinate* scalingVector) {
    Coordinate objCenter = obj->getGeometricCenter();
    Coordinate negativeObjCenter(-objCenter.getX(), -objCenter.getY());

    Matrix scalingMatrix(ObjectTransformation::scalingVectorToMatrix(scalingVector));
    Matrix translationMatrix1(ObjectTransformation::translationVectorToMatrix(&objCenter));
    Matrix translationMatrix2(ObjectTransformation::translationVectorToMatrix(&negativeObjCenter));

    Matrix scalingOperation = translationMatrix1 * scalingMatrix * translationMatrix2;

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(ObjectTransformation::coordinateToMatrix(*it));

      Matrix scaledObject = scalingOperation * coord;

      (*it)->setX(scaledObject.getMatrix()[0][0]);
      (*it)->setY(scaledObject.getMatrix()[1][0]);
    }
  }

  static void rotation(GraphicObject* obj, double angle, Coordinate* rotationVector) {
    double radians = (angle*M_PI)/180;
    Matrix rotationMatrix(ObjectTransformation::rotationVectorToMatrix(radians));
    Matrix translationMatrix1(ObjectTransformation::translationVectorToMatrix(rotationVector));
    Coordinate negativeObjCenter(-rotationVector->getX(), -rotationVector->getY());
    Matrix translationMatrix2(ObjectTransformation::translationVectorToMatrix(&negativeObjCenter));

    Matrix rotationOperation = translationMatrix1 * rotationMatrix * translationMatrix2;

    vector<Coordinate*> coordinates = obj->getCoordinates();
    vector<Coordinate*>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(ObjectTransformation::coordinateToMatrix(*it));

      Matrix scaledObject = rotationOperation * coord;

      (*it)->setX(scaledObject.getMatrix()[0][0]);
      (*it)->setY(scaledObject.getMatrix()[1][0]);
    }
  }

};

#endif
