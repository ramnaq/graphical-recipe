#ifndef COORDENADA_HPP
#define COORDENADA_HPP


/*! The cartesian coordinate. The number of parameters in the constructor indicates the dimention */

class Coordenada{
private:
  double x;
  double y;
  double xvp;
  double yvp;

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
    return this->x;
  }

  double getY() {
    return this->y;
  }

  void setXvp(double x) {
    this->xvp = x;
  }

  void setYvp(double y) {
    this->yvp = y;
  }

  double getXvp() {
    return this->xvp;
  }

  double getYvp() {
    return this->yvp;
  }

};

#endif
