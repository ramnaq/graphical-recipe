#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
  private:
    Coordenada *coordMin;
    double width;
    double height;
  public:
  	Window(double xMin, double yMin, double width, double height) {
      coordMin = new Coordenada(xMin, yMin);
      this->width = width;
      this->height = height;
    }

    Coordenada* getCoordMin() {
      return coordMin;
    }

    double getWidth() {
      return width;
    }

    double getHeight() {
      return height;
    }

    void zoomIn(double passo) {
      width = width - width*passo;
      height = height - height*passo;
    }

    void zoomOut(double passo) {
      width = width + width*passo;
      height = height + height*passo;
    }
};

#endif
