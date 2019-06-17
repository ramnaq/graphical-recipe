#ifndef BEZIERSURFACE_HPP
#define BEZIERSURFACE_HPP

#include "surface.hpp"

class BezierSurface : public Surface {
public:
  BezierSurface(string name, vector<vector<Coordinate*>> &v) :
      Surface(name) {
    this->t = 0.02;
    this->blending_function(v);
    setAllCoordinates();
    computeGeometricCenter();
  }

private:
  double t;

  void blending_function(vector<vector<Coordinate*>> &v) {
    Matrix mb = Matrix::mb();
    for (int i = 0; i < v.size() - 1; i += 3) {
      for (int j = 0; j < v[i].size() - 1; j += 3) {
        Matrix x_matrix = Matrix::g(i, j, v, 0);
        Matrix y_matrix = Matrix::g(i, j, v, 1);
        Matrix z_matrix = Matrix::g(i, j, v, 2);

        for (double temp_s = t; temp_s <= 1; temp_s += t) {
          Matrix s_vec({Matrix::t_vector(temp_s)});
          Matrix s_mb = s_vec * mb;
          BezierCurve* c = new BezierCurve("B_CURVE");

          for (double temp_t = t; temp_t <= 1; temp_t += t) {
            Matrix t_vec(Matrix::t_vectort(temp_t));
            Matrix t_mb = mb * t_vec;

            double x = (s_mb * x_matrix * t_mb).getMatrix()[0][0];
            double y = (s_mb * y_matrix * t_mb).getMatrix()[0][0];
            double z = (s_mb * z_matrix * t_mb).getMatrix()[0][0];

            c->addCoordinate(new Coordinate(x, y, z));
          }
          this->curves.push_back(c);
        }

        Matrix::transpose(x_matrix);
        Matrix::transpose(y_matrix);
        Matrix::transpose(z_matrix);

        for (double temp_s = t; temp_s <= 1; temp_s += t) {
          Matrix s_vec({Matrix::t_vector(temp_s)});
          Matrix s_mb = s_vec * mb;
          BezierCurve* c = new BezierCurve("B_CURVE");

          for (double temp_t = t; temp_t <= 1; temp_t += t) {
            Matrix t_vec(Matrix::t_vectort(temp_t));
            Matrix t_mb = mb * t_vec;

            double x = (s_mb * x_matrix * t_mb).getMatrix()[0][0];
            double y = (s_mb * y_matrix * t_mb).getMatrix()[0][0];
            double z = (s_mb * z_matrix * t_mb).getMatrix()[0][0];

            c->addCoordinate(new Coordinate(x, y, z));
          }
          this->curves.push_back(c);
        }

      }
    }
  }

};

#endif  //!< BEZIERSURFACE_HPP

