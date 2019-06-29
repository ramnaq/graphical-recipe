#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <math.h>

#include "coordinate.hpp"

using namespace std;

/*! Structures a representation and operations of a Matrix */

class Matrix {
private:
  vector<vector<double> > matrix;
public:

  Matrix(vector<vector<double> > matrix) {
    this->matrix = matrix;
  }

  vector<vector<double> > getMatrix() {
    return matrix;
  }

  vector<vector<double> >* getMatrixRef() {
    return &matrix;
  }
  static std::vector<std::vector<double> > coordinateToMatrix(Coordinate* coord) {
   return {{coord->getX()},
           {coord->getY()},
           {1}};
  }

  static std::vector<std::vector<double> > coordinateOppToMatrix(Coordinate* coord) {
   return {{coord->getXop()},
           {coord->getYop()},
           {1}};
  }

  static std::vector<std::vector<double> > translationVectorToMatrix(Coordinate* coord) {
   return {{1, 0, coord->getX()},
           {0, 1, coord->getY()},
           {0, 0,      1       }};
  }

  static std::vector<std::vector<double> > scalingVectorToMatrix(Coordinate* coord) {
   return {{coord->getX(),      0       , 0},
           {     0       , coord->getY(), 0},
           {     0       ,      0       , 1}};
  }

  static std::vector<std::vector<double> > rotationVectorToMatrix(double angle) {
   return {{cos(angle), -sin(angle), 0},
           {sin(angle),  cos(angle), 0},
           {   0      ,      0     , 1}};
  }

  static const vector<vector<double>> mb() {
    return {{-1.0,  3.0, -3.0, 1.0},
            { 3.0, -6.0,  3.0, 0.0},
            {-3.0,  3.0,  0.0, 0.0},
            { 1.0,  0.0,  0.0, 0.0}};
  }

  static const vector<double> t_vector(const double tee) {
    return {
      tee * tee * tee,
      tee * tee,
      tee,
      1
    };
  }

  static const vector<vector<double>> t_vectort(const double tee) {
    return {
      {tee * tee * tee},
      {tee * tee},
      {tee},
      {1}
    };
  }

  static const vector<vector<double>> t_matrix(const double tee) {
    const double t1 = tee;
    const double t2 = tee * tee;
    const double t3 = tee * tee * tee;
    return {
      {   0,    0,  0, 1},
      {  t3,   t2, t1, 0},
      {6*t3, 2*t2,  0, 0},
      {6*t3,    0,  0, 0}
    };
  }

  static const vector<vector<double>> t_matrixt(const double tee) {
    const double t1 = tee;
    const double t2 = tee * tee;
    const double t3 = tee * tee * tee;
    return {
      {0, t3, 6*t3, 6*t3},
      {0, t2, 2*t2,    0},
      {0, t1,    0,    0},
      {1,  0,    0,    0}
    };
  }

  static const vector<vector<double>> mbs() {
    double factor = (double) 1/6;
    return {{-1*factor,   3*factor, -3*factor, 1*factor},
            { 3*factor,  -6*factor,  3*factor,   0.0   },
            {-3*factor,     0.0   ,  3*factor,   0.0   },
            { 1*factor,   4*factor,  1*factor,   0.0   }};
  }

  static const vector<vector<double>> e(double delta, double delta2, double delta3) {
    return {{   0.0   ,     0.0   ,  0.0 , 1.0},
            {  delta3 ,    delta2 , delta, 0.0},
            { 6*delta3,   2*delta2,  0.0 , 0.0},
            { 6*delta3,     0.0   ,  0.0 , 0.0}};
  }

  static const vector<vector<double>> gx(vector<Coordinate*> &v) {
    return {{v[0]->getX()},
            {v[1]->getX()},
            {v[2]->getX()},
            {v[3]->getX()}};
  }

  static const vector<vector<double>> gy(vector<Coordinate*> &v) {
    return {{v[0]->getY()},
            {v[1]->getY()},
            {v[2]->getY()},
            {v[3]->getY()}};
  }

  static const vector<vector<double>> gz(vector<Coordinate*> &v) {
    return {{v[0]->getZ()},
            {v[1]->getZ()},
            {v[2]->getZ()},
            {v[3]->getZ()}};
  }

  static const vector<vector<double>> g(const int i, const int j,
                  const vector<vector<Coordinate*>> &v, const int axis) {
    vector<vector<double>> m = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
    };
    for (int k = i; k <= i + 3; ++k) {
      for (int l = i; l <= i + 3; ++l) {
        m[k][l] = v[k][l]->get(axis);
      }
    }
    return m;
  }

  static std::vector<std::vector<double> > translation3DVectorToMatrix(Coordinate* coord) {
   return {{1, 0,  0, coord->getX()},
           {0, 1,  0, coord->getY()},
           {0, 0,  1, coord->getZ()},
           {0, 0,  0,      1       }};
  }

  static std::vector<std::vector<double> > rotationXVectorToMatrix(double angle) {
   return {{1,    0      ,     0      , 0},
           {0, cos(angle), -sin(angle), 0},
           {0, sin(angle),  cos(angle), 0},
           {0,    0      ,     0      , 1}};
  }

  static std::vector<std::vector<double> > rotationYVectorToMatrix(double angle) {
   return {{ cos(angle), 0, sin(angle), 0},
           {    0      , 1,      0    , 0},
           {-sin(angle), 0, cos(angle), 0},
           {    0      , 0,      0    , 1}};
  }

  static std::vector<std::vector<double> > rotationZVectorToMatrix(double angle) {
   return {{cos(angle), -sin(angle), 0 , 0},
           {sin(angle),  cos(angle), 0 , 0},
           {    0     ,     0      , 1 , 0},
           {    0     ,     0      , 0 , 1}};
  }

  static std::vector<std::vector<double> > coordinate3DToMatrix(Coordinate* coord) {
   return {{coord->getX()},
           {coord->getY()},
           {coord->getZ()},
           {1}};
  }

  static std::vector<std::vector<double> > coordinate3DToMatrixOp(Coordinate* coord) {
   return {{coord->getXop()},
           {coord->getYop()},
           {coord->getZop()},
           {1}};
  }

  static std::vector<std::vector<double> > scaling3DVectorToMatrix(Coordinate* coord) {
   return {{coord->getX(),       0      ,      0       , 0},
           {    0        , coord->getY(),      0       , 0},
           {    0        ,       0      , coord->getZ(), 0},
           {    0        ,       0      ,      0       , 1}};
        printf("transpose \n");
  }

  static std::vector<std::vector<double> > genericRotationAlpha(double cy, double cz, double d) {
   return {{1,   0  ,   0  , 0},
           {0,  cz/d, -cy/d, 0},
           {0,  cy/d,  cz/d, 0},
           {0,   0  ,   0  , 1}};
  }

  static std::vector<std::vector<double> > genericRotationBeta(double cx, double d) {
   return {{  d, -cx, 0, 0},
           { cx,  d , 0, 0},
           {  0,  0 , 1, 0},
           {  0,  0 , 0, 1}};
  }

  static void transpose(Matrix& matr) {
    Matrix result({
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    });
    for (int i = 0; i<4; i++) {
      for (int j=0; j<4; j++) {
        result.getMatrixRef()->at(i)[j] = matr.getMatrixRef()->at(j)[i];
      }
    }
    for (int i = 0; i<4; i++) {
      for (int j=0; j<4; j++) {
        matr.getMatrixRef()->at(i)[j] = result.getMatrixRef()->at(i)[j];
      }
    }
  }

  Matrix operator* (Matrix& obj) {
    std::vector<std::vector<double> > newMatrix;
    std::vector<std::vector<double> > objVector = obj.getMatrix();

    newMatrix.resize(matrix.size());
    for(int i = 0; i < matrix.size(); i++) {
      newMatrix[i].resize(objVector[0].size());
      for (int k = 0; k < objVector[i].size(); k++) {
        double num = 0;
        for (int j = 0; j < matrix[i].size(); j++) {
           num += matrix[i][j] * objVector[j][k];
        }
        newMatrix[i][k] = num;
      }
    }
    return Matrix(newMatrix);
  }

};

#endif
