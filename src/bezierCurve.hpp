#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "curve.hpp"
#include "matrix.hpp"

class BezierCurve : public Curve {
public:
  BezierCurve(string name, vector<Coordinate*> &coordinateList)
    : Curve(name, CURVE, coordinateList) {
        this->t = 0.05;
        this->blending_function(coordinateList);
  }

  void setT(double newt) {
    t = newt;
  }

private:
  double t;

  void blending_function(const std::vector<Coordinate*> &v) {
    Matrix mb = Matrix::mb();
    double temp_t = t;
    this->coordinateList.clear();

    for (int i = 0; i < v.size() - 1; i += 3) {
      // Get points
      Coordinate* p0 = v[i];
      Coordinate* p1 = v[i + 1];
      Coordinate* p2 = v[i + 2];
      Coordinate* p3 = v[i + 3];

      // Column matrixes
      Matrix x_vector({{p0->getX()}, {p1->getX()}, {p2->getX()}, {p3->getX()}});
      Matrix y_vector({{p0->getY()}, {p1->getY()}, {p2->getY()}, {p3->getY()}});

      while (temp_t <= 1) {
        Matrix t_vec({Matrix::t_vector(temp_t)});  // Line matrix
        Matrix t_mb = t_vec * mb;    // M(1,4) x M(4,4) = t_mb(1,4)

        // M(1,4) x M(4,1) = M(1,1), so get line 0, column 0 to obtain the double value
        double x = (t_mb * x_vector).getMatrix().at(0).at(0);
        double y = (t_mb * y_vector).getMatrix().at(0).at(0);
        //const double z = t_mb * z_vector;

        this->coordinateList.push_back(new Coordinate(x, y));
        temp_t += t;
      }

      temp_t = t;
    }

  }
};

#endif  // BEZIER_CURVE_H
