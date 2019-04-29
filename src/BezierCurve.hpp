#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H


class BezierCurve : public GraphicObject {
public:
	BezierCurve(string name, vector<Coordinate*> &points)
      : GraphicObject(name, CURVE, points) {}

	void setT(double newt) {
      t = newt;
	}

protected:
	double t = 0.05;

	const vector<vector<double>> magic() {
      return {{-1.0,  3.0, -3.0, 1.0},
	  { 3.0, -6.0,  3.0, 0.0},
	  {-3.0,  3.0,  0.0, 0.0},
	  { 1.0,  0.0,  0.0, 0.0}};
	}

	const vector<double> t_vector(const double tee) {
		return {
			tee * tee * tee,
			tee * tee,
			tee,
			1
		};
	}

	void blending_function(const std::vector<Coordinate> v) {
		Matrix magic(this->magic());
		double temp_t = t;
		this->coordinateList.clear();

		for (int i = 0; i < v.size() - 1; i += 3) {
			// Get points
			const Coordinate& p0 = v[i];
			const Coordinate& p1 = v[i + 1];
			const Coordinate& p2 = v[i + 2];
			const Coordinate& p3 = v[i + 3];

			// Vectors
		    Matrix x_vector({{p0.getX(), p1.getX(), p2.getX(), p3.getX()}});
			Matrix y_vector({{p0.getY(), p1.getY(), p2.getY(), p3.getY()}});

			while (temp_t <= 1) {
				Matrix t_vec({t_vector(temp_t)});  // vector
				Matrix t_magic = t_vec * magic;

				double x = (t_magic * x_vector).getMatrix().at(0).at(0);
				double y = (t_magic * y_vector).getMatrix().at(0).at(0);
				//const double z = t_magic * z_vector;

				this->coordinateList.push_back(new Coordinate(x, y));
				temp_t += t;
			}

			temp_t = t;
		}

	}
};

#endif  // BEZIER_CURVE_H

