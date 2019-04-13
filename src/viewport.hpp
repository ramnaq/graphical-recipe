#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "window.hpp"


class ViewPort {
  private:
    Window *window;
    vector<Coordinate*> vpCoord;

  public:
    ViewPort (vector<Coordinate*> vpCoord, Window *window) {
      this->vpCoord = vpCoord;
      this->window = window;
    }

    ~ViewPort () {
      delete this->vpCoord.front();
      delete this->vpCoord.back();
    }

    vector<Coordinate*> getCoordinates () {
      return vpCoord;
    }

	//! The viewport (coordinates system) transformation
	/*!
	 * Transforms coord into a Coordinate referred to the viewport.
	 * @param coord The window coordinate to be transformed into a viewport coordinate.
	 */
   void transformation(Coordinate *coord) {
      // Normalized coordinate system
      double xnsMax = 1;
      double ynsMax = 1;
      double xnsMin = -1;
      double ynsMin = -1;

      double xvpMax = vpCoord.back()->getX();
      double yvpMax = vpCoord.back()->getY();
      double xvpMin = vpCoord.front()->getX();
      double yvpMin = vpCoord.front()->getY();

      double x = (( (coord->getXns() - xnsMin) / (xnsMax - xnsMin) ) * (xvpMax - xvpMin)) + xvpMin;
      double y = ((1 - (coord->getYns() - ynsMin)/ (ynsMax - ynsMin) ) * (yvpMax - yvpMin)) + yvpMin;
      
      coord->setXvp(x);
      coord->setYvp(y);
    }
};

#endif
