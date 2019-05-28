#ifndef BSPLINE_H
#define BSPLINE_H

#include <iostream>

class BSpline : public GraphicObject {
private:
  vector<Coordinate*> curveCoordinate;
public:
  BSpline(string name, vector<Coordinate*> &points, double delta)
    : GraphicObject(name, CURVE, points) {
        this->create_points(points, delta);
  }

protected:
  const vector<vector<double>> mbs() {
    double factor = (double) 1/6;
    return {{-1*factor,  3*factor,  -3*factor, 1*factor},
            { 3*factor,  -6*factor, 3*factor,  0.0},
            {-3*factor,  0.0,       3*factor,  0.0},
            { 1*factor,  4*factor,  1*factor,  0.0}};
  }

  const vector<vector<double>> e(double delta, double delta2, double delta3) {
    return {{ 0.0,      0.0,      0.0,   1.0},
            { delta3,   delta2,   delta, 0.0},
            { 6*delta3, 2*delta2, 0.0,   0.0},
            { 6*delta3, 0.0,      0.0,   0.0}};
  }

  const vector<vector<double>> gx(vector<Coordinate*> &v) {
    return {{v[0]->getX()},
            {v[1]->getX()},
            {v[2]->getX()},
            {v[3]->getX()}};
  }

  const vector<vector<double>> gy(vector<Coordinate*> &v) {
    return {{v[0]->getY()},
            {v[1]->getY()},
            {v[2]->getY()},
            {v[3]->getY()}};
  }

  void create_points(vector<Coordinate*> &points, double delta) {
    // 0 - Define delta, delta2, delta3 and n values
    double delta2 = delta * delta;
    double delta3 = delta2 * delta;
    double n = 1/delta;

    // 1 - Compute coefficients
    Matrix mbs = BSpline::mbs();
    Matrix e = BSpline::e(delta, delta2, delta3);

    for (int i = 0; i <= points.size()-4; i++ ) {
      vector<Coordinate*> control_points = {points[i], points[i+1], points[i+2], points[i+3]};
      Matrix gx = BSpline::gx(control_points);
      Matrix gy = BSpline::gy(control_points);

      Matrix c_x = mbs * gx;
      Matrix c_y = mbs * gy;

      // 2 - Compute f0, df0, d2f0 and d3f0 for P1
      Matrix d_x = e * c_x;
      Matrix d_y = e * c_y;

      // 3 - Call drawCurveFwdDiff
      this->drawCurveFwdDiff(n, d_x.getMatrix()[0][0], d_x.getMatrix()[1][0], d_x.getMatrix()[2][0], d_x.getMatrix()[3][0]
                              , d_y.getMatrix()[0][0], d_y.getMatrix()[1][0], d_y.getMatrix()[2][0], d_y.getMatrix()[3][0]);
    }

    this->coordinateList = this->curveCoordinate;
  }

  void drawCurveFwdDiff(double n, double x, double dx, double d2x, double d3x, double y, double dy, double d2y, double d3y) {
    int i = 0;
    double x_old, y_old;
    x_old = x;
    y_old = y;

    this->curveCoordinate.push_back(new Coordinate(x_old, y_old));
    while (i < n) {
      x = x + dx; dx = dx + d2x; d2x = d2x + d3x;
      y = y + dy; dy = dy + d2y; d2y = d2y + d3y;
      x_old = x; y_old = y;

      this->curveCoordinate.push_back(new Coordinate(x_old, y_old));
      i++;
    }
  }

};

#endif  // BSPLINE_H
