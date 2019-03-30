#ifndef WINDOW_HPP
#define WINDOW_HPP

//! Window is the visible area of a graphical world.
/*!
 * The graphical world moves (horizontally, vertically, diagonally) and the window
 * shows a limited area of it.
 */
// TODO Lembrar de transformar para radianos
class Window: public GraphicObject{
  private:
    double angle;
  public:
    Window(vector<Coordinate*> &windowCoordinates) :
      GraphicObject("Window", WINDOW, windowCoordinates) {
      this->angle = 0;
    }

    double getAngle() {
      return this->angle;
    }

    void setAngle(double angle) {
      this->angle = angle;
    }

    void zoomIn(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() + passo);
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setX( coordMax->getX() - passo);
      coordMax->setY( coordMax->getY() - passo);
    }

    void zoomOut(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() - passo);
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setX( coordMax->getX() + passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goRight(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() + passo);
      coordMax->setX( coordMax->getX() + passo);
    }

    void goLeft(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() - passo);
      coordMax->setX( coordMax->getX() - passo);
    }

    void goUp(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setY( coordMin->getY() + passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goDown(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setY( coordMin->getY() - passo);
      coordMax->setY( coordMax->getY() - passo);
    }

    void goUpLeft(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() - passo);
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setX( coordMax->getX() - passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goUpRight(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() + passo);
      coordMin->setY( coordMin->getY() + passo);
      coordMax->setX( coordMax->getX() + passo);
      coordMax->setY( coordMax->getY() + passo);
    }

    void goDownLeft(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() - passo);
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setX( coordMax->getX() - passo);
      coordMax->setY( coordMax->getY() - passo);
    }

    void goDownRight(double passo) {
      Coordinate* coordMin = getCoordinates().front();
      Coordinate* coordMax = getCoordinates().back();

      coordMin->setX( coordMin->getX() + passo);
      coordMin->setY( coordMin->getY() - passo);
      coordMax->setX( coordMax->getX() + passo);
      coordMax->setY( coordMax->getY() - passo);
    }
};

#endif
