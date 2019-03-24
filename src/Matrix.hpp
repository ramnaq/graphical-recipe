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
    vector<vector<double> > newMatrix;
    vector<vector<double> > objVector = obj.getMatrix(); // Objeto
    vector<vector<double> >::iterator row;
    vector<double>::iterator col;
    int i = 0, j = 0;

    newMatrix.resize(matrix.size()); // Linhas
    for(row = matrix.begin(); row != matrix.end(); row++, i++) {
      newMatrix[i].resize(objVector[0].size()); // Colunas
      newMatrix[i][0] = 0;
      for (col = row->begin(); col != row->end(); col++, j++) {      
        newMatrix[i][0] += *col * objVector[j][0];
      }
      j = 0;
    }
    return Matrix(newMatrix);
  }

};

#endif
