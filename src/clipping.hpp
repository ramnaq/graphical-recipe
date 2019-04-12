#ifndef CLIPPING_HPP
#define CLIPPING_HPP

/*! Clipping methods. */

#include <bitset>

#define LEFT 0
#define RIGHT 1
#define BOTTOM 2
#define TOP 3
#define IN 1
#define OUT 2
#define MINOUT 3
#define MAXOUT 4
#define BOTHOUT 5


class Clipping {
private:
  vector<Coordinate*> wCoord;

public:
  Clipping() {
    this->wCoord = {new Coordinate(-1,-1), new Coordinate(1,1)};
  }

  ~Clipping() {
    delete this->wCoord.front();
    delete this->wCoord.back();
  }

  void pointClipping(GraphicObject* point) {
    Coordinate* pc = point->getCoordinates().front();

    if (pc->getXns() < wCoord.front()->getX() || pc->getXns() > wCoord.back()->getX())
      point->setVisibility(false);
    else if (pc->getYns() < wCoord.front()->getY() || pc->getYns() > wCoord.back()->getY())
      point->setVisibility(false);
    else
      point->setVisibility(true);
  }

  void lineClipping(GraphicObject* line, int chosenAlgorithm) {
    if (chosenAlgorithm)
      csClipping(line); // Cohen-Sutherland Clipping
    else
      lbClipping(line); // Liang-Barsky Clipping
  }

  void csClipping(GraphicObject* line) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

    bitset<4> rgMin = generateRegionCode(coordMin);
    bitset<4> rgMax = generateRegionCode(coordMax);

    int op = verify(rgMin, rgMax);
    switch (op) {
      case IN:
        line->setVisibility(true);
        break;
      case OUT:
        line->setVisibility(false);
        break;
      default:
        line->setVisibility(true);

        // Coefficient
        double m = (coordMax->getYns() - coordMin->getYns()) / (coordMax->getXns() - coordMin->getXns());

        if (op == MINOUT) {
          computeNewCoordinates(coordMin, rgMin, m);
        } else if (op == MAXOUT) {
          computeNewCoordinates(coordMax, rgMax, m);
        } else {
          computeNewCoordinates(coordMin, rgMin, m);
          computeNewCoordinates(coordMax, rgMax, m);

          rgMin = generateRegionCode(coordMin);
          rgMax = generateRegionCode(coordMax);

          int op = verify(rgMin, rgMax);
          if (op == BOTHOUT)
            line->setVisibility(false);
          else
            line->setVisibility(true);
        }
    }
  }

  bitset<4> generateRegionCode(Coordinate* coord) {
    bitset<4> rg(0000);

    if (coord->getYns() > wCoord.back()->getY())
      rg[TOP] = 1;
    if (coord->getYns() < wCoord.front()->getY())
      rg[BOTTOM] = 1;
    if (coord->getXns() > wCoord.back()->getX())
      rg[RIGHT] = 1;
    if (coord->getXns() < wCoord.front()->getX())
      rg[LEFT] = 1;

    return rg;
  }

  int verify(bitset<4> rgMin, bitset<4> rgMax) {
    if ((rgMin|rgMax).none()) // Fully inside the window
      return IN;
    else if ((rgMin & rgMax).any()) // Fully out of the window
      return OUT;
    else {
      if (!rgMin.none() && rgMax.none()) // coordMin is out of the window
        return MINOUT;
      else if (rgMin.none() && !rgMax.none()) // coordMax is out of the window
        return MAXOUT;
      else
        return BOTHOUT; // Both are out of the window
    }
  }

  void computeNewCoordinates(Coordinate* coord, bitset<4> rg, double m) {
    if (rg[LEFT]) {
      double y_xe = m * (wCoord.front()->getX() - coord->getXns()) + coord->getYns();

      // Special case: Superior/inferior sides, when there are two active bits.
      // If change y is enough, stop. Otherwise go to the second active bit.
      if (y_xe >= wCoord.front()->getY() && y_xe <= wCoord.back()->getY()) {
        coord->setYns(y_xe);
        coord->setXns(wCoord.front()->getX());
        return;
      }
    }
    if (rg[RIGHT]) {
      double y_xd = m * (wCoord.back()->getX() - coord->getXns()) + coord->getYns();

      if (y_xd <= wCoord.back()->getY() && y_xd >= wCoord.front()->getY()) {
        coord->setYns(y_xd);
        coord->setXns(wCoord.back()->getX());
        return;
      }
    }
    if (rg[TOP]) {
      double x_yt =  coord->getXns() + (1/m) * (wCoord.back()->getY() - coord->getYns());

      if (x_yt <= wCoord.back()->getX() && x_yt >= wCoord.front()->getX()) {
        coord->setXns(x_yt);
        coord->setYns(wCoord.back()->getY());
        return;
      }
    }
    if (rg[BOTTOM]) {
      double x_yf = coord->getXns() + (1/m) * (wCoord.front()->getY() - coord->getYns());

      if (x_yf >= wCoord.front()->getX() && x_yf <= wCoord.back()->getX()) {
        coord->setXns(x_yf);
        coord->setYns(wCoord.front()->getY());
        return;
      }
    }
  }

  void lbClipping(GraphicObject* line) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

  }

};

#endif  //!< CLIPPING_HPP
