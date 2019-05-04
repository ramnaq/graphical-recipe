#ifndef CLIPPING_HPP
#define CLIPPING_HPP

/*! Clipping methods. */

#include <bitset>
#include <algorithm>

#include "line.hpp"
#include "polygon.hpp"

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
  double savedXns;
  double savedYns;

  const vector<Coordinate> clp {
		  Coordinate(-1, -1),
		  Coordinate(1, -1),
		  Coordinate(1, 1),
		  Coordinate(-1, 1),
	  };

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

  void polygonClipping(GraphicObject* polygon, int chosenAlgorithm) {
    polygon->updateWindowPoints(polygon->getCoordinates());
    vector<Coordinate> clp = this->clp;
    for (int i = 0; i < clp.size(); i++) {
      int k = (i + 1) % clp.size();
      Coordinate c1(clp[i]), c2(clp[k]);
      clip(static_cast<Polygon&>(*polygon), c1, c2);
    }
  }

  void curveClipping(GraphicObject* curve) {
    curve->updateWindowPoints(curve->getCoordinates());
    vector<Coordinate*> points = curve->getWindowPoints();
    vector<Coordinate*> newPoints = {};
    for (int i = 0; i < points.size() - 1; ++i) {
      Coordinate* c1 = points[i];
      Coordinate* c2 = points[i+1];

      Coordinate* c1_copy = Coordinate::newWindowCoordinate(c1->getXns(), c1->getYns());
      Coordinate* c2_copy = Coordinate::newWindowCoordinate(c2->getXns(), c2->getYns());

      vector<Coordinate*> l = {c1_copy, c2_copy};
      bool result = cohenSutherland(new Line("", l));
      if (result) {
        newPoints.push_back(c1_copy);
        if (!equalPoints(*c2, *c2_copy)) {
          newPoints.push_back(c2_copy);
        }
      }

      curve->updateWindowPoints(newPoints);
    }
  }

  bool equalPoints(Coordinate& c1, Coordinate& c2) {
	return (c1.getXns() == c2.getXns()) && (c1.getYns() == c2.getYns());
  }

  //! Clips each edge of polygon over the window edge c1c2
  /**
   * @param polygon The polygon being cliped
   * @param c1 A point of a window edge
   * @param c2 A point of a window edge (same edge as c1)
   */
  void clip(Polygon& polygon, Coordinate& c1, Coordinate& c2) {
    const vector<Coordinate*> points = polygon.getWindowPoints();
    vector<Coordinate*> new_points;
    double x1 = c1.getX();
    double y1 = c1.getY();
    double x2 = c2.getX();
    double y2 = c2.getY();

    for (int i = 0; i < points.size(); i++) {
      int k = (i + 1) % points.size();
      Coordinate* a = points[i];
      Coordinate* b = points[k];

      double ax = a->getXns();
      double ay = a->getYns();
      double bx = b->getXns();
      double by = b->getYns();

      double a_pos = (x2-x1)*(ay-y1) - (y2-y1)*(ax-x1);
      double b_pos = (x2-x1)*(by-y1) - (y2-y1)*(bx-x1);

	  Coordinate* b_copy = new Coordinate(bx, by);
	  b_copy->setXns(b->getXns());
	  b_copy->setYns(b->getYns());

      /* Only second point is added */
      if (a_pos >= 0  && b_pos >= 0) {
        new_points.push_back(b);

        /* When only first point is outside the window */
      } else if (a_pos < 0  && b_pos >= 0) {
        /* Point of intersection and second point */
        new_points.push_back(intersection(c1, c2, a, b));
        new_points.push_back(b);

        /* When only second point is outside the window */
	  } else if (a_pos >= 0  && b_pos < 0) {
		/* Only point of intersection with edge is added */
		new_points.push_back(intersection(c1, c2, a, b));

		/* When both points are outside */
	  } else {
		//no points are added
	  }
	}

	/* Updating polygon points */
	if(new_points.size() == 0) {
	  /* Clear polygon window points */
	  for (int i = 0; i < points.size(); ++i) {
        points.at(i)->setXns(0);
        points.at(i)->setYns(0);
	  }
	  polygon.setVisibility(false);
	} else {
	  polygon.updateWindowPoints(new_points);
	  polygon.setVisibility(true);
	}
  }

  //! Calculates the intersection of the line segments p1p2 and p3p4.
  /**
   * p1p2 is an edge of the window. p2p3 is a line segment which it wants the
   * intersection between it and p1p2.
   * @param point Indicates which Coordinate (p3 or p4) is outside the window.
   * @return the point (Coordinate) of intersection.
   */
  Coordinate* intersection(Coordinate& p1, Coordinate& p2, Coordinate* p3,
	  Coordinate* p4) {
    double x1 = p1.getX();
    double x2 = p2.getX();
    double x3 = p3->getXns();
    double x4 = p4->getXns();

    double y1 = p1.getY();
    double y2 = p2.getY();
    double y3 = p3->getYns();
    double y4 = p4->getYns();

    /* Resulting point */
    double x = 0;
    double y = 0;

    x  = (x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4);
    x /= (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

    y  = (x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4);
    y /= (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

    return Coordinate::newWindowCoordinate(x, y);
  }

  bool cohenSutherland(GraphicObject* line) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

    bitset<4> rgMin = generateRegionCode(coordMin);
    bitset<4> rgMax = generateRegionCode(coordMax);

    int op = verify(rgMin, rgMax);
    switch (op) {
      case IN:
        line->setVisibility(true);
        return true;
      case OUT:
        line->setVisibility(false);
        return false;
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
          if (op == BOTHOUT) {
            line->setVisibility(false);
            return false;
          } else {
            line->setVisibility(true);
          }
        }
        return true;
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
