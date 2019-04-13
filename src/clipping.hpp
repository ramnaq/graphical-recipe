#ifndef CLIPPING_HPP
#define CLIPPING_HPP

/*! Clipping methods. */

#include <bitset>
#include <algorithm>

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
    if (chosenAlgorithm == 1)
      cohenSutherland(line);
    else
      liangBarsky(line);
  }

  void cohenSutherland(GraphicObject* line) {
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
        double m = (coordMax->getYns() - coordMin->getYns())
                        / (coordMax->getXns() - coordMin->getXns());

        if (op == MINOUT) {
          computeNewCoordsCS(coordMin, rgMin, m);
        } else if (op == MAXOUT) {
          computeNewCoordsCS(coordMax, rgMax, m);
        } else {
          computeNewCoordsCS(coordMin, rgMin, m);
          computeNewCoordsCS(coordMax, rgMax, m);

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

  void computeNewCoordsCS(Coordinate* coord, bitset<4> rg, double m) {
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

  void liangBarsky(GraphicObject* line) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

    double x0 = coordMin->getXns();
    double y0 = coordMin->getYns();
    double x1 = coordMax->getXns();
    double y1 = coordMax->getYns();

    double dX = (x1 - x0);
    double dY = (y1 - y0);

    /* `p` or `q` = [left, right, bottom, top] */
    vector<double> p = {-dX, dX, -dY, dY};
    vector<double> q = {x0+1, 1-x0, y0+1, 1-y0};

    vector<double> negativeArr, positiveArr;
    negativeArr.push_back(0);
    positiveArr.push_back(1);

    /* line parallel to and out of the view */
    if ((p[0] == 0 && q[0] < 0) || (p[2] == 0 && q[2] < 0)) {
      line->setVisibility(false);
      return;
    }

    if (p[0] != 0) {
      double r0 = q[0] / p[0];
      double r1 = q[1] / p[1];
      if (p[0] < 0) {
        negativeArr.push_back(r0);
        positiveArr.push_back(r1);
      } else {
        negativeArr.push_back(r1);
        positiveArr.push_back(r0);
      }
    }
    if (p[2] != 0) {
      double r2 = q[2] / p[2];
      double r3 = q[3] / p[3];
      if (p[2] < 0) {
        negativeArr.push_back(r2);
        positiveArr.push_back(r3);
      } else {
        negativeArr.push_back(r3);
        positiveArr.push_back(r2);
      }
    }

    double rn0 = *std::max_element(std::begin(negativeArr), std::end(negativeArr));
    double rn1 = *std::min_element(std::begin(positiveArr), std::end(positiveArr));

    if (rn0 > rn1) {
      line->setVisibility(false);
      return;
    }

    coordMin->setXns(x0 + p[1]*rn0);
    coordMin->setYns(y0 + p[3]*rn0); // computing new points

    coordMax->setXns(x0 + p[1]*rn1);
    coordMax->setYns(y0 + p[3]*rn1);
    line->setVisibility(true);
  }

};

#endif  //!< CLIPPING_HPP
