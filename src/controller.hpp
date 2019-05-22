#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdexcept>
#include <iostream>

#include "bezierCurve.hpp"
#include "bspline.hpp"
#include "clipping.hpp"
#include "displayFile.hpp"
#include "enum.hpp"
#include "line.hpp"
#include "objectTransformation.hpp"
#include "objDescriptor.hpp"
#include "object3D.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include "view.hpp"

/*! Representation of the Controller (or Control) module of the MVC (Model, View, Control) architecture */

class Controller {
private:
  View view;
  DisplayFile display;
  Clipping clipping;
  vector<Coordinate*> pointsForPolygon;
  vector<Coordinate*> pointsForCurve;
  vector<Segment*> segmentsForObject3D;
  Coordinate cop = Coordinate(0, 0, 100);

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
   * GraphicObject and then sends this instance to 'view' to be drawn.
   */
  void createObject() {
    int currentPage = view.getCurrentPage();
    string name = view.getObjectName();
    string objType;
    GraphicObject* obj;

    switch (currentPage) {
     case POINT: {
        vector<Coordinate*> pointCoordinate = {new Coordinate(view.getEntryPointX(), view.getEntryPointY(), view.getEntryPointZ())};
        obj = new Point(name, pointCoordinate);
        objType = "PONTO";

        break;
     }
     case LINE: {
        vector<Coordinate*> lineCoordinate = {new Coordinate(view.getEntryLineX1(), view.getEntryLineY1(), view.getEntryLineZ1()),
                                               new Coordinate(view.getEntryLineX2(), view.getEntryLineY2(), view.getEntryLineZ2())};
        obj = new Line(name, lineCoordinate);
        objType = "LINHA";

        break;
      }
      case POLYGON: {
        try {
          if (pointsForPolygon.size() < 3) {
            throw std::runtime_error("Cannot create polygon without at least three points!");
          }
          obj = new Polygon(name, pointsForPolygon, view.getCheckBtnState());
          objType = "POLIGONO";

          pointsForPolygon.clear();
          view.clearPolygonEntry();
        } catch(const std::runtime_error& e) {
          std::cout << "[ERROR] " << e.what() << std::endl;
          view.logError("Pontos insuficientes para criação de polígono.\n");
        }
        break;
      }
      case CURVE: {
        try {
          if (pointsForCurve.size() < 4) {
            throw std::runtime_error("Cannot create a curve without at least 4 points!");
          }
          if (view.isCheckBtnSplineChecked()) {
            obj = new BSpline(name, pointsForCurve, view.getDelta());
          } else {
            obj = new BezierCurve(name, pointsForCurve);
          }
          objType = "CURVA";

          pointsForCurve.clear();
          view.clearCurveEntry();
        } catch(const std::runtime_error& e) {
          std::cout << "[ERROR] " << e.what() << std::endl;
          view.logError("Pontos insuficientes para criação de curva.\n");
        }
        break;
      }
      case OBJECT3D: {
          obj = new Object3D(name, segmentsForObject3D);
          objType = "OBJETO 3D";

          segmentsForObject3D.clear();
          view.clearObjet3DEntry();
        break;
      }
    }

    display.insert(obj);
    view.insertIntoListBox(*obj, objType);
    updateDrawScreen();
  }

  void createObjectsFromFile() {
    string fileName = view.chooseFile();
    ObjDescriptor od;

    vector<GraphicObject*> objs = od.read(fileName);
    for (int i = 0; i < objs.size(); ++i) {
      display.insert(objs[i]);
      showObjectIntoView(objs[i]);
    }

    updateDrawScreen();
  }

  void saveWorldToFile() {
    string fileName = view.getFileToSaveWorld();

    ObjDescriptor od;
    od.write(display.getObjs(), fileName);

    view.clearSaveWorldFile();
  }

  void showObjectIntoView(GraphicObject* gobj) {
    switch (gobj->getType()) {
      case POINT:
        view.insertIntoListBox(*gobj, "PONTO");
        break;
      case LINE:
        view.insertIntoListBox(*gobj, "LINHA");
        break;
      case POLYGON:
        view.insertIntoListBox(*gobj, "POLIGONO");
        pointsForPolygon.clear();
        break;
    }
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
        Coordinate translationVector(view.getEntryTranslationX(), view.getEntryTranslationY(), view.getEntryTranslationZ());

        if (obj->getType() != OBJECT3D) {
          ObjectTransformation::translation(static_cast<GraphicObject2D*>(obj)->getCoordinates(), &translationVector);
        } else {
          ObjectTransformation::translation(static_cast<Object3D*>(obj)->getAllCoord(), &translationVector);
        }
        break;
      }
      case SCALING: {
        Coordinate scalingVector(view.getEntryScalingX(), view.getEntryScalingY(), view.getEntryScalingZ());
        Coordinate objCenter = obj->getGeometricCenter();

        if (obj->getType() != OBJECT3D) {
          ObjectTransformation::scaling(static_cast<GraphicObject2D*>(obj)->getCoordinates(), &objCenter, &scalingVector);
        } else {
          ObjectTransformation::scaling(static_cast<Object3D*>(obj)->getAllCoord(), &objCenter, &scalingVector);
        }
        break;
      }
      case ROTATION: {
        int radioBtnChosen = view.getRotationRadioButtonState();
        int whichAxis = view.getObjRotateBtnState();
        double angle = view.getAngle();
        Coordinate* reference;

        if (radioBtnChosen == 1) {
          reference = new Coordinate(0,0,0);
        } else if (radioBtnChosen == 2) {
          Coordinate tmp = obj->getGeometricCenter();
          reference = new Coordinate(tmp.getX(), tmp.getY(), tmp.getZ());
        } else {
          reference = new Coordinate(view.getEntryRotationX(), view.getEntryRotationY(), view.getEntryRotationZ());
        }

        if (obj->getType() != OBJECT3D) {
          ObjectTransformation::rotation(static_cast<GraphicObject2D*>(obj)->getCoordinates(), angle, reference, whichAxis);
        } else {
          ObjectTransformation::rotation(static_cast<Object3D*>(obj)->getAllCoord(), angle, reference, whichAxis);
        }

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
    int index = view.removeFromList(view.getListObj());

    display.remove(index);
    updateDrawScreen();
  }

  void removeFromCoordPolygonList() {
    int index = view.removeFromList(view.getListCoordPolygon());

    if (index > -1) {
      pointsForPolygon.erase(pointsForPolygon.begin() + index);
    }
  }

  void removeFromCoordCurveList() {
    int index = view.removeFromList(view.getListCoordCurve());

    if (index > -1) {
      pointsForCurve.erase(pointsForCurve.begin() + index);
    }
  }

  void removeFromCoordObject3DList() {
    int index = view.removeFromList(view.getListSegment());

    if (index > -1) {
        segmentsForObject3D.erase(segmentsForObject3D.begin() + index);
    }
  }

  /*!
   * Gets (x, y) from view to create a new Coordinate and then add a new line
   * to a Polygon which is being created.
   */
  void addNewLineForPolygon() {
    double x = view.getEntryPolygonX();
    double y = view.getEntryPolygonY();
    double z = view.getEntryPolygonZ();
    Coordinate* c = new Coordinate(x, y, z);

    pointsForPolygon.push_back(c);
    view.insertCoordList(view.getListCoordPolygon(), x, y, z);
  }

  /*!
   * Gets (x, y) from view to create a new Coordinate and then add it
   * to a Curve which is being created.
   */
  void addNewPointForCurve() {
    double x = view.getEntryCurveX();
    double y = view.getEntryCurveY();
    double z = view.getEntryCurveZ();
    Coordinate* c = new Coordinate(x, y, z);

    pointsForCurve.push_back(c);
    view.insertCoordList(view.getListCoordCurve(), x, y, z);
  }

  void addNewSegmentForObject3D() {
    // double x1 = view.getEntry3DX1();
    // double y1 = view.getEntry3DY1();
    // double z1 = view.getEntry3DZ1();
    // double x2 = view.getEntry3DX2();
    // double y2 = view.getEntry3DY2();
    // double z2 = view.getEntry3DZ2();
    //
    // Coordinate* a = new Coordinate(x1, y1, z1);
    // Coordinate* b = new Coordinate(x2, y2, z2);
    // Segment* s = new Segment(a, b);

    Coordinate* a = new Coordinate(0, 0, -10);
    Coordinate* a1 = new Coordinate(0, 0, -10);
    Coordinate* a2 = new Coordinate(0, 0, -10);

    Coordinate* b = new Coordinate(0, 100, -10);
    Coordinate* b1 = new Coordinate(0, 100, -10);
    Coordinate* b2 = new Coordinate(0, 100, -10);

    Coordinate* c = new Coordinate(100, 100, -10);
    Coordinate* c1 = new Coordinate(100, 100, -10);
    Coordinate* c2 = new Coordinate(100, 100, -10);

    Coordinate* d = new Coordinate(100, 0, -10);
    Coordinate* d1 = new Coordinate(100, 0, -10);
    Coordinate* d2 = new Coordinate(100, 0, -10);

    Coordinate* e = new Coordinate(50, 50, -50);
    Coordinate* e1 = new Coordinate(50, 50, -50);
    Coordinate* e2 = new Coordinate(50, 50, -50);

    Coordinate* f = new Coordinate(150, 50, -50);
    Coordinate* f1 = new Coordinate(150, 50, -50);
    Coordinate* f2 = new Coordinate(150, 50, -50);

    Coordinate* g = new Coordinate(50, 150, -50);
    Coordinate* g1 = new Coordinate(50, 150, -50);
    Coordinate* g2 = new Coordinate(50, 150, -50);

    Coordinate* h = new Coordinate(150, 150, -50);
    Coordinate* h1 = new Coordinate(150, 150, -50);
    Coordinate* h2 = new Coordinate(150, 150, -50);

    Segment* s = new Segment(a, b);
    Segment* s1 = new Segment(a1, d1);
    Segment* s2 = new Segment(a2, e);
    Segment* s3 = new Segment(g, b1);
    Segment* s4 = new Segment(g1, h1);
    Segment* s5 = new Segment(g2, e1);
    Segment* s6 = new Segment(c, b2);
    Segment* s7 = new Segment(c1, d2);
    Segment* s8 = new Segment(c2, h2);
    Segment* s9 = new Segment(f, h);
    Segment* s10 = new Segment(f1, d);
    Segment* s11 = new Segment(f2, e2);

    segmentsForObject3D.push_back(s);
    segmentsForObject3D.push_back(s1);
    segmentsForObject3D.push_back(s2);
    segmentsForObject3D.push_back(s3);
    segmentsForObject3D.push_back(s4);
    segmentsForObject3D.push_back(s5);
    segmentsForObject3D.push_back(s6);
    segmentsForObject3D.push_back(s7);
    segmentsForObject3D.push_back(s8);
    segmentsForObject3D.push_back(s9);
    segmentsForObject3D.push_back(s10);
    segmentsForObject3D.push_back(s11);


    //view.insertCoordList(view.getListSegment(), x1, y1, z1, x2, y2, z2);
  }

  //! Changes the visualization window (of type Window) according the op code.
  /*!
   * @param op The operation to be done on the Window (@see View::updateWindow()).
   */
  void changeWindow(int op) {
    try {
      view.updateWindow(view.getStep(), op);
    } catch (int e) {
      view.logWarning("Passo do zoom acima do limite!\n");
    }
    updateDrawScreen();
  }

  void rotateCamera(GraphicObject* element) {
      Window* window = view.getWindow();

      double angleX = window->getAngleX();
      double angleY = window->getAngleY();
      double angleZ = window->getAngleZ();

      if (element->getType() != OBJECT3D) {
        ObjectTransformation::cameraRotation(static_cast<GraphicObject2D*>(element)->getCoordinates(), angleX, angleY, angleZ);
      } else {
        ObjectTransformation::cameraRotation(static_cast<Object3D*>(element)->getAllCoord(),  angleX, angleY, angleZ);
      }
  }

  void updateObjRotateBtnState(int newState) {
    view.updateObjRotateBtnState(newState);
  }

  void updateRadioBtnState(int newState) {
    view.updateRadioBtnState(newState);
  }

  void updateClippingRadioBtnState(int newState) {
    view.updateClippingRadioBtnState(newState);
  }

  void updateCheckBtnState() {
    view.updateCheckBtnState();
  }

  void updateCheckBtnSpline() {
    view.updateCheckBtnSpline();
  }

  void updateProjectionState(int newState) {
    view.updateProjectionBtnState(newState);
    updateDrawScreen();
  }

  void updateCOP() {
    double newValue = view.getNewCOP();

    cop.setZ(100 - newValue);
    updateDrawScreen();
  }

  void updateWindowAngle(int whichAxis) {
    double angle = view.getAngleRotateWindow();

    view.updateWindow(angle, whichAxis);
    updateDrawScreen();
  }

  //! Calls 'view' to (re)drawn all elements in 'displayFile'.
  void updateDrawScreen() {
    view.clear_surface();

    // Step 1 and 2 (Both projections) - Translate COP and compute θx e θy
    view.computeAngleForProjection(&cop);

    Elemento<GraphicObject*>* nextElement = display.getHead();
    while (nextElement != NULL) {
      GraphicObject* element = nextElement->getInfo();

      rotateCamera(element);

      view.transformProjection(element, &cop);
      view.transformSCN(element);

      switch (element->getType()) {
        case POINT: {
          Point* point = static_cast<Point*>(element);

          if (clipping.pointClipping(point->getCoordinates()[0])) {
            view.transform(point);
            view.drawNewPoint(point);
          }
          break;
        }
        case LINE: {
          Line* line = static_cast<Line*>(element);

          if (clipping.lineClipping(line->getCoordinates(), view.getLineClippingAlgorithm())) {
            view.transform(line);
            view.drawNewLine(line);
          }
          break;
        }
        case POLYGON: { // TODO Fix visibility
          Polygon* polygon = static_cast<Polygon*>(element);

          clipping.polygonClipping(polygon);
          if (polygon->isVisible()) {
            view.transform(polygon);
            view.drawNewPolygon(polygon, polygon->fill());
          }
          break;
        }
        case CURVE: { // TODO Fix visibility
          Curve* curve = static_cast<Curve*>(element);

          clipping.curveClipping(curve);
          if (curve->isVisible()) {
            view.transform(curve);
            view.drawNewCurve(curve);
          }
          break;
        }
        case OBJECT3D: { // TODO Fix visibility
          Object3D* obj3D = static_cast<Object3D*>(element);

          vector<Segment*> segments = obj3D->getSegmentList();
          vector<Segment*>::iterator segment;
          for(segment = segments.begin(); segment != segments.end(); segment++) {
              vector<Coordinate*> tmp = (*segment)->getCoordinates();
              (*segment)->setVisibility(clipping.lineClipping(tmp, 1));
          }

          view.transform(obj3D);
          view.drawNewObject3D(obj3D);
          break;
        }
      }
      nextElement = nextElement->getProximo();
    }
    view.drawViewPortArea();
  }

};

#endif
