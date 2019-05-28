#ifndef WINDOW_HPP
#define WINDOW_HPP

//! Window is the visible area of a graphical world.
/*!
 * The graphical world moves (horizontally, vertically, diagonally) and the window
 * shows a limited area of it.
 */
class Window: public GraphicObject{
private:
  double angle;
  Coordinate const *defaultCoordMin;
  Coordinate const *defaultCoordMax;
  
public:
  Window(vector<Coordinate*> &windowCoordinates) :
    GraphicObject("Window", WINDOW, windowCoordinates) {
    this->angle = 0;

    Coordinate* coordMin = windowCoordinates.front();
    Coordinate* coordMax = windowCoordinates.back();
    this->defaultCoordMin = new Coordinate(coordMin->getX(), coordMin->getY());
    this->defaultCoordMax = new Coordinate(coordMax->getX(), coordMax->getY());
  }

  ~Window() {
    delete this->defaultCoordMax;
    delete this->defaultCoordMin;
  }

  double getAngle() {
    return this->angle;
  }

  void setAngle(double angle) {
    this->angle += angle;
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

  void goCenter() {
    Coordinate* coordMin = getCoordinates().front();
    Coordinate* coordMax = getCoordinates().back();

    coordMin->setX(defaultCoordMin->getX());
    coordMin->setY(defaultCoordMin->getY());
    coordMax->setX(defaultCoordMax->getX());
    coordMax->setY(defaultCoordMax->getY());

    this->angle = 0;
  }

  //! Checks if 'step' for a zoom-in ist within the limits.
  /**
   * If 'step' is too big, the zoom-in operation would be inverted (doing
   * zoom-out), in that case it is considered an invalid value for 'step'.
   *
   * @param step The step of a zoom operation (@see zoomIn()).
   * @return true if 'step' doesn't exceeds the limits or false otherwise.
   */
  bool validZoomStep(double step) {
    double newXMin = getCoordinates().front()->getX() + step;
    double newXMax = getCoordinates().back()->getX() - step;
    return (newXMin < newXMax);
  }

};

#endif
