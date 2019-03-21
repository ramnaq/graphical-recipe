#ifndef COORDENADA_HPP
#define COORDENADA_HPP


/*! The cartesian coordinate. The number of parameters in the constructor indicates the dimention */

class Coordenada{
private:
  double x;
  double y;

public:
	Coordenada(double x, double y) {
    this->x = x;
    this->y = y;
  }

	~Coordenada() {}

  void setX(double x) {
    this->x = x;
  }

  void setY(double y) {
    this->y = y;
  }

  double getX() {
    return x;
  }

  double getY() {
    return y;
  }

};

#endif
