#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "window.hpp"


class ViewPort {
  private:
    Window *window;
    Coordinate* coordMin;
    Coordinate* coordMax;

  public:
    ViewPort (double x, double y, Window *window) {
      this->coordMin = new Coordinate(1, 1);
      this->coordMax = new Coordinate(x, y);
      this->window = window;
    }

    ~ViewPort () {
      delete this->coordMin;
      delete this->coordMax;
    }

	//! The viewport (coordinates system) transformation
	/*!
	 * Transforms coord into a Coordinate referred to the viewport.
	 * @param coord The window coordinate to be transformed into a viewport coordinate.
	 */
  	void transformation(Coordinate* coord) {
      double xwMax = window->getCoordMax()->getX();
      double ywMax = window->getCoordMax()->getY();
      double xwMin = window->getCoordMin()->getX();
      double ywMin = window->getCoordMin()->getY();

      double xvpMax = coordMax->getX();
      double yvpMax = coordMax->getY();
      double xvpMin = coordMin->getX();
      double yvpMin = coordMin->getY();

      double x = ((coord->getX() - xwMin) / (xwMax - xwMin)) * (xvpMax - xvpMin);
	  double y = (1 - (coord->getY() - ywMin) / (ywMax - ywMin)) * (yvpMax - yvpMin);

	  coord->setXvp(x);
      coord->setYvp(y);
  	}
};

#endif
