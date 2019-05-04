#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

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

  static const vector<vector<double>> mbs() {
    double factor = (double) 1/6;
    return {{-1*factor,  3*factor,  -3*factor, 1*factor},
            { 3*factor,  -6*factor, 3*factor,  0.0},
            {-3*factor,  0.0,       3*factor,  0.0},
            { 1*factor,  4*factor,  1*factor,  0.0}};
  }

  static const vector<vector<double>> e(double delta, double delta2, double delta3) {
    return {{ 0.0,      0.0,      0.0,   1.0},
            { delta3,   delta2,   delta, 0.0},
            { 6*delta3, 2*delta2, 0.0,   0.0},
            { 6*delta3, 0.0,      0.0,   0.0}};
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

  Matrix operator* (Matrix& obj) {
    std::vector<std::vector<double> > newMatrix;
    std::vector<std::vector<double> > objVector = obj.getMatrix(); // Objeto

    newMatrix.resize(matrix.size()); // Linhas
    for(int i = 0; i < matrix.size(); i++) {
      newMatrix[i].resize(objVector[0].size()); // Colunas
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