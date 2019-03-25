#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

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
    std::vector<std::vector<double> >::iterator row;
    std::vector<double>::iterator col;
    int i = 0;

    newMatrix.resize(matrix.size()); // Linhas
    for(row = matrix.begin(); row != matrix.end(); row++, i++) {
      newMatrix[i].resize(objVector[0].size()); // Colunas
      for (int k = 0; k < objVector[i].size(); k++) {
        int num = 0;
        int j = 0;
        for (col = row->begin(); col != row->end(); col++, j++) {
           num += *col * objVector[j][k];
        }
        newMatrix[i][k] = num;
      }
    }
    return Matrix(newMatrix);
  }

};

#endif
