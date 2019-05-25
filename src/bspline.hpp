#ifndef BSPLINE_H
#define BSPLINE_H

#include "curve.hpp"
#include "matrix.hpp"

class BSpline : public Curve {
public:
  BSpline(string name, vector<Coordinate*> &coordinateList, double delta)
    : Curve(name, CURVE, coordinateList) {
        this->create_points(coordinateList, delta);
  }

protected:
  void create_points(vector<Coordinate*> &points, double delta) {
    vector<Coordinate*> tmp;

    // 0 - Define delta, delta2, delta3 and n values
    double delta2 = delta * delta;
    double delta3 = delta2 * delta;
    double n = 1/delta;

    // 1 - Compute coefficients
    Matrix mbs = Matrix::mbs();
    Matrix e = Matrix::e(delta, delta2, delta3);

    for (int i = 0; i <= points.size()-4; i++ ) {
      vector<Coordinate*> control_points = {points[i], points[i+1], points[i+2], points[i+3]};
      Matrix gx = Matrix::gx(control_points);
      Matrix gy = Matrix::gy(control_points);
      Matrix gz = Matrix::gz(control_points);

      Matrix c_x = mbs * gx;
      Matrix c_y = mbs * gy;
      Matrix c_z = mbs * gz;

      // 2 - Compute f0, df0, d2f0 and d3f0 for P1
      Matrix d_x = e * c_x;
      Matrix d_y = e * c_y;
      Matrix d_z = e * c_z;

      // 3 - Call drawCurveFwdDiff
      this->coordinateList = this->drawCurveFwdDiff(n, d_x.getMatrix()[0][0], d_x.getMatrix()[1][0], d_x.getMatrix()[2][0], d_x.getMatrix()[3][0]
                                                     , d_y.getMatrix()[0][0], d_y.getMatrix()[1][0], d_y.getMatrix()[2][0], d_y.getMatrix()[3][0]
                                                     , d_z.getMatrix()[0][0], d_z.getMatrix()[1][0], d_z.getMatrix()[2][0], d_z.getMatrix()[3][0]);
    }
  }

  vector<Coordinate*> drawCurveFwdDiff(double n, double x, double dx, double d2x, double d3x, double y, double dy, double d2y, double d3y, double z, double dz, double d2z, double d3z) {
    vector<Coordinate*> tmp;
    int i = 0;
    double x_old, y_old, z_old;
    x_old = x;
    y_old = y;
    z_old = z;

    tmp.push_back(new Coordinate(x_old, y_old, z_old));
    while (i < n) {
      x = x + dx; dx = dx + d2x; d2x = d2x + d3x;
      y = y + dy; dy = dy + d2y; d2y = d2y + d3y;
      z = z + dz; dz = dz + d2z; d2z = d2z + d3z;
      x_old = x; y_old = y; z_old = z;

      tmp.push_back(new Coordinate(x_old, y_old, z_old));
      i++;
    }

    return tmp;
  }

};

#endif  // BSPLINE_H
