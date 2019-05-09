#ifndef OPP_HPP
#define OPP_HPP

#include "matrix.hpp"
#include <iostream>
/*! Transform world coordinates to normalized system coordinates. */

class Opp {
private:
  double angleX, angleY;
public:
  Opp () {}
  ~Opp () {}

  static std::vector<std::vector<double> > translationVectorToMatrix(Coordinate* coord) {
   return {{1, 0,  0, coord->getX()},
           {0, 1,  0, coord->getY()},
           {0, 0,  1, coord->getZ()},
           {0, 0 , 0, 1}};
  }

  static std::vector<std::vector<double> > rotationXVectorToMatrix(double angle) {
   return {{1,    0      ,     0      , 0},
           {0, cos(angle), -sin(angle), 0},
           {0, sin(angle), cos(angle) , 0},
           {0,    0      ,     0      , 1}};
  }

  static std::vector<std::vector<double> > rotationYVectorToMatrix(double angle) {
   return {{cos(angle) , 0, sin(angle), 0},
           {    0      , 1,      0    , 0},
           {-sin(angle), 0, cos(angle), 0},
           {    0      , 0,      0    , 1}};
  }

  static std::vector<std::vector<double> > coordinateToMatrix(Coordinate* coord) {
   return {{coord->getX()},
           {coord->getY()},
           {coord->getZ()},
           {1}};
  }

  void computeAngle(GraphicObject* window, Coordinate* vrp) {
    Coordinate negCoord(-vrp->getX(), -vrp->getY(), -vrp->getZ());
    Matrix trans = Opp::translationVectorToMatrix(&negCoord);

    vector<Coordinate*> coordinates = window->getCoordinates();
    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Opp::coordinateToMatrix(*it));

      Matrix translatedObject = trans * coord;

      (*it)->setXop(-translatedObject.getMatrix()[0][0]);
      (*it)->setYop(-translatedObject.getMatrix()[1][0]);
      (*it)->setZop(-translatedObject.getMatrix()[2][0]);
    }

    Coordinate* w1t = window->getCoordinates()[0];
    Coordinate* w2t = window->getCoordinates()[1];

    // Produto vetorial
    double x = w1t->getYop()*w2t->getZop() - w2t->getYop()*w1t->getZop();
    double y = w1t->getZop()*w2t->getXop() - w1t->getXop()*w2t->getZop();
    double z = w1t->getXop()*w2t->getYop() - w2t->getXop()*w1t->getYop();

    // angles
    this->angleX = (y == 0 || z == 0) ? 0 : (atan(y/z)*M_PI)/180;
    this->angleY = (x == 0 || z == 0) ? 0 : (atan(x/z)*M_PI)/180;
  }

  void transformation(vector<Coordinate*> coord, Coordinate* geometriCenter) {
    Coordinate negCoord(-geometriCenter->getX(), -geometriCenter->getY(), -geometriCenter->getZ());

    Matrix trans = Opp::translationVectorToMatrix(&negCoord);
    Matrix rotx  = Opp::rotationXVectorToMatrix(this->angleX);
    Matrix roty  = Opp::rotationYVectorToMatrix(this->angleY);

    Matrix transform = trans * rotx * roty;

    vector<Coordinate*>::iterator it;
    for(it = coord.begin(); it != coord.end(); it++) {
        Matrix coord(Opp::coordinateToMatrix((*it)));

        Matrix translatedObject = transform * coord;

        (*it)->setXop(translatedObject.getMatrix()[0][0]);
        (*it)->setYop(translatedObject.getMatrix()[1][0]);
        (*it)->setZop(translatedObject.getMatrix()[2][0]);
    }
  }

};

#endif
