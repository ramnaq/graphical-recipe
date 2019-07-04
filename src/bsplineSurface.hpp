#ifndef BSPLINESURFACE_HPP
#define BSPLINESURFACE_HPP

#include "surface.hpp"
#include "bspline.hpp"

class BSplineSurface : public Surface {
public:
  BSplineSurface(string name, vector<vector<Coordinate*>> &v) :
      Surface(name) {
    this->t = 0.03;
    this->blending_function(v);
    setAllCoordinates();
    computeGeometricCenter();
  }

private:
  double t;

  vector<Coordinate*> fwd_diff(double x, double dx, double d2x,
                  double d3x, double y, double dy, double d2y,
                  double d3y, double z, double dz, double d2z,
                  double d3z) {
    int n = 1/t;
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

      Coordinate* c = new Coordinate(x_old, y_old, z_old);
      tmp.push_back(c);
      i++;
    }

    return tmp;
  }

  void blending_function(vector<vector<Coordinate*>> &v) {
    Matrix mbs = Matrix::mbs();
    int n = 1/t;
    for (int i = 0; i + 3 < v.size(); i++) {
      for (int j = 0; j + 3 < v[i].size(); j++) {
        // Matrix
        Matrix x_matrix = Matrix::g(i, j, v, 0);
        Matrix y_matrix = Matrix::g(i, j, v, 1);
        Matrix z_matrix = Matrix::g(i, j, v, 2);

        Matrix c_x = mbs * x_matrix * mbs;
        Matrix c_y = mbs * y_matrix * mbs;
        Matrix c_z = mbs * z_matrix * mbs;

        Matrix es = Matrix::t_matrix(t);
        Matrix et = Matrix::t_matrixt(t);

        // Forward differences matrices
        Matrix d_x = es * c_x * et;
        Matrix d_y = es * c_y * et;
        Matrix d_z = es * c_z * et;

        for (int s = 0; s < n; s++) {
          BSpline* c = new BSpline("BS_SURFACE");
          c->updateCoordinateList(fwd_diff(d_x.getMatrix()[0][0], d_x.getMatrix()[0][1], d_x.getMatrix()[0][2], d_x.getMatrix()[0][3]
                  , d_y.getMatrix()[0][0], d_y.getMatrix()[0][1], d_y.getMatrix()[0][2], d_y.getMatrix()[0][3]
                  , d_z.getMatrix()[0][0], d_z.getMatrix()[0][1], d_z.getMatrix()[0][2], d_z.getMatrix()[0][3]));
          this->curves.push_back(c);
          updateFwdDiffMatrices(d_x);
          updateFwdDiffMatrices(d_y);
          updateFwdDiffMatrices(d_z);
        }

        // creating forward diff matrices (dd)
        d_x = es * c_x * et;
        d_y = es * c_y * et;
        d_z = es * c_z * et;

        Matrix::transpose(d_x);
        Matrix::transpose(d_y);
        Matrix::transpose(d_z);

        for (int s = 0; s < n; s++) {
          BSpline* c = new BSpline("BS_SURFACE");
          c->updateCoordinateList(fwd_diff(d_x.getMatrix()[0][0], d_x.getMatrix()[0][1], d_x.getMatrix()[0][2], d_x.getMatrix()[0][3]
                  , d_y.getMatrix()[0][0], d_y.getMatrix()[0][1], d_y.getMatrix()[0][2], d_y.getMatrix()[0][3]
                  , d_z.getMatrix()[0][0], d_z.getMatrix()[0][1], d_z.getMatrix()[0][2], d_z.getMatrix()[0][3]));
          this->curves.push_back(c), 
          updateFwdDiffMatrices(d_x);
          updateFwdDiffMatrices(d_y);
          updateFwdDiffMatrices(d_z);
        }

        /*
        int n = 1 / t;
        for (double s = t; s < 1; s += t) {
          Matrix tm = Matrix::t_matrixt(t);
          Matrix sm = Matrix::t_matrix(s);
        	Matrix cx = sm * x_matrix * tm;
        	Matrix cy = sm * y_matrix * tm;
         	Matrix cz = sm * z_matrix * tm;
          BSpline* c = new BSpline("BS_SURFACE");
          c->updateCoordinateList(fwd_diff(n, c_x.getMatrix()[0][0], c_x.getMatrix()[1][0], c_x.getMatrix()[2][0], c_x.getMatrix()[3][0]
                  , c_y.getMatrix()[0][0], c_y.getMatrix()[1][0], c_y.getMatrix()[2][0], c_y.getMatrix()[3][0]
                  , c_z.getMatrix()[0][0], c_z.getMatrix()[1][0], c_z.getMatrix()[2][0], c_z.getMatrix()[3][0]));
          this->curves.push_back(c); 
        }
        */

			}
    }
  }

  void updateFwdDiffMatrices(Matrix& ddw) {
    for(int i = 0; i < 3; i++) {
      ddw.getMatrixRef()->at(i) = this->sumVectors(ddw.getMatrix().at(i), ddw.getMatrix().at(i+1));
    }
  }

  vector<double> sumVectors(vector<double> v1, vector<double> v2) {
    vector<double> v;  
    for (int i = 0; i < v1.size(); i++) {
      v.push_back(v1[i] + v2[i]);
    }
    return v;
  }


};

#endif  //!< BSPLINESURFACE_HPP 


