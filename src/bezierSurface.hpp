
class BezierSurface : public Curve3D {
public:
  BezierSurface(string name, vector<Coordinate*> &v) :
      Curve3D(name) {
    this->t = 0.05;
    this->blending_function(v);
  }

private:
  void blending_function(vector<vector<Coordinate*>> &v) {
    Matrix mb = Matrix::mb();
    for (int i = 0; i < v.size() - 1; i += 3) {
			for (int j = 0; j < v[i].size() - 1; j += 3) {
				// Matrix
				Matrix x_matrix = Matrix::g(i, j, v, 0);
				Matrix y_matrix = Matrix::g(i, j, v, 1);
				Matrix z_matrix = Matrix::g(i, j, v, 2);

				// S
				for (double temp_s = t; temp_s <= 1; temp_s += t) {
          Matrix t_vec({Matrix::t_vector(temp_s)});
					Matrix mb_s = t_vec * mb;
					vector<Coordinate*> bCoords;
					// T
					for (double temp_t = t; temp_t <= 1; temp_t += t) {
						const Vector t_magic = magic * t_vector(temp_t);

						const double x = s_magic * x_matrix * t_magic;
						const double y = s_magic * y_matrix * t_magic;
						const double z = s_magic * z_matrix * t_magic;

						bCoords.push_back(new Coordinate(x, y, z));
					}	
					this->curves.push_back(new BezierCurve("B_CURVE", bCoords));
				}

        Matrix::transpose(x_matrix);
        Matrix::transpose(y_matrix);
        Matrix::transpose(z_matrix);

				for (double temp_s = t; temp_s <= 1; temp_s += t) {
          Matrix t_vec({Matrix::t_vector(temp_s)});
					Matrix mb_s = t_vec * mb;
					vector<Coordinate*> bCoords;
					// T
					for (double temp_t = t; temp_t <= 1; temp_t += t) {
						const Vector t_magic = magic * t_vector(temp_t);

						const double x = s_magic * x_matrix * t_magic;
						const double y = s_magic * y_matrix * t_magic;
						const double z = s_magic * z_matrix * t_magic;

						bCoords.push_back(new Coordinate(x, y, z));
					}	
					this->curves.push_back(new BezierCurve("B_CURVE", bCoords));
				}
			}
    }
  }
}
