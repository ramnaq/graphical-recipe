#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "window.hpp"

class ViewPort {
  private:
    double width;
    double height;
    Window *window;
    Coordenada* coordMin;
  public:
    ViewPort (double width, double height, Window *window) {
      this->width =  width;
      this->height = height;
      this->window = window;
      this->coordMin = window->getCoordMin();
    }

  	void transformation(Coordenada *coord) {
      double x = ((coord->getX() - coordMin->getX()) / window->getWidth()) * width;
  		double y = (1 - (coord->getY() - coordMin->getY())/ window->getHeight()) * height;

  		coord->setX(x);
      coord->setY(y);
  	}
};

#endif
