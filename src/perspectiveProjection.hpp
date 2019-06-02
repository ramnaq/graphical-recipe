#ifndef PERSPECTIVE_HPP
#define PERSPECTIVE_HPP

#include "matrix.hpp"
#include "window.hpp"

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

  void computeAngle(Coordinate* geo, Coordinate* cop) {
    // Step 1 - Translade COP para a origem e o mundo
    // COP
    Coordinate negCop(-cop->getX(), -cop->getY(), -cop->getZ());
    Matrix translation(Matrix::translation3DVectorToMatrix(&negCop));

    Matrix coordCOP(Matrix::coordinate3DToMatrix(cop));
    Matrix resultante = translation * coordCOP;
    cop->setXop(resultante.getMatrix()[0][0]);
    cop->setYop(resultante.getMatrix()[1][0]);
    cop->setZop(resultante.getMatrix()[2][0]);

    // VPR
    Coordinate negGeo(-geo->getX(), -geo->getY(), -geo->getZ());
    Matrix translation2(Matrix::translation3DVectorToMatrix(&negGeo));

    Matrix coordGeo(Matrix::coordinate3DToMatrix(geo));
    Matrix resultante2 = translation * translation2 * coordGeo;
    geo->setXop(resultante2.getMatrix()[0][0]);
    geo->setYop(resultante2.getMatrix()[1][0]);
    geo->setZop(resultante2.getMatrix()[2][0]);

    // Step 2 - Determine VPN, angulos X e Y
    // Cross product
    double x = (-cop->getYop())*geo->getZop() - geo->getYop()*(-cop->getZop());
    double y = (-cop->getZop())*geo->getXop() - (-cop->getXop())*geo->getZop();
    double z = (-cop->getXop())*geo->getYop() - geo->getXop()*(-cop->getYop());

    // Angles
    this->angleX = (y == 0 || z == 0) ? 0 : (atan(y/z)*M_PI)/180;
    this->angleY = (x == 0 || z == 0) ? 0 : (atan(x/z)*M_PI)/180;
  }

  void transformation(vector<Coordinate*> coord, Coordinate* vrp, Coordinate* cop) {
    // 3 - Rotacione o mundo em torno de X e Y de forma a alinhar VPN com o eixo Z
    Coordinate negCoord(-vrp->getX(), -vrp->getY(), -vrp->getZ());
    Coordinate negCop(-cop->getX(), -cop->getY(), -cop->getZ());

    Matrix copDistance = Matrix::translation3DVectorToMatrix(&negCop);
    Matrix rotx  = Matrix::rotationXVectorToMatrix(-this->angleX);
    Matrix roty  = Matrix::rotationYVectorToMatrix(-this->angleY);
    Matrix trans = Matrix::translation3DVectorToMatrix(&negCoord);

    Matrix transform = trans * rotx * roty * copDistance;

    vector<Coordinate*>::iterator it;
    for(it = coord.begin(); it != coord.end(); it++) {
        Matrix coord(Matrix::coordinate3DToMatrixOp((*it)));
        Matrix translatedObject = transform * coord;

        (*it)->setXop(translatedObject.getMatrix()[0][0]);
        (*it)->setYop(translatedObject.getMatrix()[1][0]);
        (*it)->setZop(translatedObject.getMatrix()[2][0]);

        // Compute intersection
        Coordinate x = intersection(*it, cop->getZ());
        //cout << coord.getMatrix()[0][0] << " " << coord.getMatrix()[1][0] << " " << coord.getMatrix()[2][0] << " ---> " << x.getX() << " " << x.getY() << " "<< x.getZ() << endl;
        (*it)->setXop(x.getX());
        (*it)->setYop(x.getY());
        (*it)->setZop(x.getZ());
    }
  }
};

#endif
