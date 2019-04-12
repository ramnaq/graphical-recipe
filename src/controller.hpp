#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdexcept>
#include <iostream>

#include "enum.hpp"
#include "view.hpp"
#include "clipping.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "displayFile.hpp"
#include "ObjectTransformation.hpp"

#define WINDOW_ORIGINAL_POSITION 10

/*! Representation of the Controller (or Control) module of the MVC (Model, View, Control) architecture */

class Controller {

private:
  View view;
  DisplayFile display;
  Clipping clipping;
  vector<Coordinate*> pointsForPolygon;

public:
  Controller() {
  }

  ~Controller() {
  }

  void run(int argc, char* argv[]) {
    view.initializeGtkWindow(argc, argv);
  }

  //! Creates an instance of a Graphical Object and asks 'view' to draw it.
  /*!
   * Uses information from 'view' to create Coordinates, instantiate a type of
   * GraphicalObject and then sends this instance to 'view' to be drawn.
   */
  void createObject() {
    int currentPage = view.getCurrentPage();
    double x1, y1, x2, y2;
    string name = view.getObjectName();;
    switch (currentPage) {
     case POINT: {
        x1 = view.getEntryPointX();
        y1 = view.getEntryPointY();

        vector<Coordinate*> pointCoordinate = {new Coordinate(x1, y1)};
        Point* p = new Point(name, pointCoordinate);

        display.insert(p);
        view.insertIntoListBox(*p, "PONTO");

        break;
     }
     case LINE: {
        x1 = view.getEntryLineX1();
        y1 = view.getEntryLineY1();

        x2 = view.getEntryLineX2();
        y2 = view.getEntryLineY2();

        vector<Coordinate*> linesCoordinate = {new Coordinate(x1, y1), new Coordinate(x2, y2)};
        Line* line = new Line(name, linesCoordinate);

        display.insert(line);
        view.insertIntoListBox(*line, "LINHA");

        break;
      }
      case POLYGON: {
        Polygon* polygon;
        try {
          if (pointsForPolygon.size() < 3) {
            throw std::runtime_error("Cannot create polygon without at least three points!");
          }
          polygon = new Polygon(name, pointsForPolygon, view.getCheckBtnState());

          display.insert(polygon);
          view.insertIntoListBox(*polygon, "POLIGONO");
          view.removeAllPolygonCoordinates();
          view.clearPolygonCoordEntries();

          pointsForPolygon.clear();
        } catch(const std::runtime_error& e) {
          std::cout << "[ERROR] " << e.what() << std::endl;
          view.logError("Pontos insuficientes para criação de polígono.\n");
        }
        break;
      }
    }
    updateDrawScreen();
  }

  //! Changes an object position through translation, scaling or rotation.
  /*!
   * Takes the selected object in the object list and applies a transformation.
   */
  void executeObjectTransformation() {
    int currentPage = view.getCurrentPageTransformation();
    int currentObjectIndex = view.getCurrentObjectIndex();
    GraphicObject* obj = display.getElementoNoIndice(currentObjectIndex);

    switch (currentPage) {
      case TRANSLATION: {
        Coordinate translationVector(view.getEntryTranslationX(), view.getEntryTranslationY());
        ObjectTransformation::translation(obj, &translationVector);
        break;
      }
      case SCALING: {
        Coordinate scalingVector(view.getEntryScalingX(), view.getEntryScalingY());
        ObjectTransformation::scaling(obj, &scalingVector);
        break;
      }
      case ROTATION: {
        int radioBtnChosen = view.getRotationRadioButtonState();
        double angle = view.getAngle();
        Coordinate* reference;
        if (radioBtnChosen == 1) {
          reference = new Coordinate(0,0);
        } else if (radioBtnChosen == 2) {
          Coordinate tmp = obj->getGeometricCenter();
          reference = new Coordinate(tmp.getX(), tmp.getY());
        } else {
          reference = new Coordinate(view.getEntryRotationX(), view.getEntryRotationY());
        }
        ObjectTransformation::rotation(obj, angle, reference);

        delete reference;
        break;
      }
    }

    updateDrawScreen();
  }

  void openAddObjectWindow() {
    view.openAddObjectWindow();
  }

  void openEditObjectWindow() {
    view.openEditObjectWindow();
  }

  void create_surface(GtkWidget *widget) {
    view.create_surface(widget);
  }

  void draw(cairo_t *cr) {
    view.draw(cr);
  }

  void initializeWindowViewPort() {
    view.initializeWindowViewPort();
  }

  //! Calls View::removeSelectedObject() and updates the screen with updateDrawScreen().
  void removeSelectedObject() {
    int index = view.removeSelectedObject();
    display.remove(index);
    updateDrawScreen();
  }

  void removeFromCoordPolygonList() {
    int index = view.removeFromCoordPolygonList();
    if (index > -1) {
      pointsForPolygon.erase(pointsForPolygon.begin() + index);
    }
  }

  /*!
   * Gets (x, y) from view to create a new Coordinate and then add a new line
   * to a Polygon which is being created.
   */
  void addNewLineForPolygon() {
    Coordinate* c = new Coordinate(view.getEntryPolygonX(), view.getEntryPolygonY());
    pointsForPolygon.push_back(c);
    view.insertCoordPolygonList();
  }

  //! Changes the visualization window (of type Window) according the op code.
  /*!
   * @param op The operation to be done on the Window (@see View::updateWindow()).
   */
  void changeWindow(int op) {
    double changeFactor;
    if (op != WINDOW_ORIGINAL_POSITION)
      changeFactor =  (op < 10) ? view.getStep() : view.getAngleRotateWindow();
    try {
      view.updateWindow(changeFactor, op);
    } catch (int e) {
      view.logWarning("Passo do zoom acima do limite!\n");
    }
    updateDrawScreen();
  }

  void updateRadioButtonState(int newState) {
    view.updateRadioButtonState(newState);
  }

  void updateClippingRadioButtonState(int newState) {
    view.updateClippingRadioButtonState(newState);
  }

  void updateCheckBtnState() {
    view.updateCheckBtnState();
  }

  //! Calls 'view' to (re)drawn all elements in 'displayFile'.
  void updateDrawScreen() {
    view.clear_surface();
    int chosenAlgorithm = view.getLineClippingAlgorithm();

    // Update window coordinates
    Window* window = view.getWindow();
    Coordinate* windowCoord = window->getCoordinates().back();
    Coordinate geometriCenter = window->getGeometricCenter();
    double currentAngle = window->getAngle();
    Coordinate windowScalingFactor(1,1);
    Coordinate scalingFactor(1/windowCoord->getX(), 1/windowCoord->getY());

    view.transformSCN(window, &geometriCenter, &windowScalingFactor, currentAngle);

    Elemento<GraphicObject*>* nextElement = display.getHead();
    while (nextElement != NULL) {
      GraphicObject* element = nextElement->getInfo();
      view.transformSCN(element, &geometriCenter, &scalingFactor, currentAngle);
      switch (element->getType()) {
        case POINT:
          clipping.pointClipping(element);
          if (element->isVisible()) {
            view.transform(element);
            view.drawNewPoint(element);
          }
          break;
        case LINE:
            clipping.lineClipping(element, chosenAlgorithm);
            if (element->isVisible()) {
              view.transform(element);
              view.drawNewLine(element);
            }
            break;
        case POLYGON: {
            bool fill = static_cast<Polygon*>(element)->fill();
            view.transform(element);
            view.drawNewPolygon(element, fill);
          break;
        }
      }
      nextElement = nextElement->getProximo();
    }
    view.drawViewPortArea();
  }

};

#endif
