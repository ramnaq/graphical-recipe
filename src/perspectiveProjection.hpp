#ifndef PERSPECTIVE_HPP
#define PERSPECTIVE_HPP

#include "matrix.hpp"
#include "window.hpp"

// TODO REMOVE
#include <iostream>

/*! Transform world coordinates to normalized system coordinates. */

class Perspective {
private:
  double angleX, angleY;

public:
  Perspective () {}
  ~Perspective () {}

  Coordinate intersection(Coordinate* obj, double d) {
    double xp, yp;

    xp = obj->getXop() / (obj->getZop() / d);
    yp = obj->getYop() / (obj->getZop() / d);

    return Coordinate(xp, yp, d);
  }

  void computeAngle(Window* window, Coordinate* cop) {
    Coordinate negCop(-cop->getX(), -cop->getY(), -cop->getZ());
    Matrix translation(Matrix::translation3DVectorToMatrix(&negCop));

    // Step 1 - Translade COP para a origem e o mundo
    // COP
    Matrix coordCOP(Matrix::coordinate3DToMatrix(cop));
    Matrix resultante = translation * coordCOP;
    cop->setXop(resultante.getMatrix()[0][0]);
    cop->setYop(resultante.getMatrix()[1][0]);
    cop->setZop(resultante.getMatrix()[2][0]);

    // WINDOW
    vector<Coordinate*> coordinates = window->getCoordinates();
    vector<Coordinate*>::iterator it;
    for(it = coordinates.begin(); it != coordinates.end(); it++) {
      Matrix coord(Matrix::coordinate3DToMatrix(*it));

      Matrix translatedObject = translation * coord;

      (*it)->setXop(translatedObject.getMatrix()[0][0]);
      (*it)->setYop(translatedObject.getMatrix()[1][0]);
      (*it)->setZop(translatedObject.getMatrix()[2][0]);
    }

    // Step 2 - Determine VPN, angulos X e Y
    Coordinate* w1t = window->getCoordinates()[0];
    Coordinate* w2t = window->getCoordinates()[1];

    // Cross product
    double x = (-w1t->getYop())*w2t->getZop() - w2t->getYop()*(-w1t->getZop());
    double y = (-w1t->getZop())*w2t->getXop() - (-w1t->getXop())*w2t->getZop();
    double z = (-w1t->getXop())*w2t->getYop() - w2t->getXop()*(-w1t->getYop());

    // Angles
    this->angleX = (y == 0 || z == 0) ? 0 : (atan(y/z)*M_PI)/180;
    this->angleY = (x == 0 || z == 0) ? 0 : (atan(x/z)*M_PI)/180;

    // AGORA ROTACIONO A WINDOW POR ESSES ANGULOS?
  }

  void transformation(vector<Coordinate*> coord, Coordinate* geometriCenter, Coordinate* cop) {
    // 3 - Rotacione o mundo em torno de X e Y de forma a alinhar VPN com o eixo Z
    Coordinate negCoord(-cop->getX(), -cop->getY(), -cop->getZ()); // USO ESSE VETOR DE TRANSLACAO?

    Matrix trans = Matrix::translation3DVectorToMatrix(&negCoord);
    Matrix rotx  = Matrix::rotationXVectorToMatrix(this->angleX);
    Matrix roty  = Matrix::rotationYVectorToMatrix(this->angleY);

    Matrix transform = trans * rotx * roty;

    vector<Coordinate*>::iterator it;
    for(it = coord.begin(); it != coord.end(); it++) {
        Matrix coord(Matrix::coordinate3DToMatrix((*it)));

        Matrix translatedObject = transform * coord;

        (*it)->setXop(translatedObject.getMatrix()[0][0]);
        (*it)->setYop(translatedObject.getMatrix()[1][0]);
        (*it)->setZop(translatedObject.getMatrix()[2][0]);

        // Compute intersection
        Coordinate x = intersection(*it, cop->getZ());
        (*it)->setXop(x.getX());
        (*it)->setYop(x.getY());
        (*it)->setZop(x.getZ());
    }

  }
};

#endif
