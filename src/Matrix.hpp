#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#include <iostream>

using namespace std;

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
