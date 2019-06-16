#ifndef VIEW_HPP
#define VIEW_HPP

#include <gtk/gtk.h>
#include <sstream>
#include <stdio.h>
#include <string>

#include "drawer.hpp"
#include "logger.hpp"
#include "orthogonalParallelProjection.hpp"
#include "perspectiveProjection.hpp"
#include "scn.hpp"
#include "viewport.hpp"
#include "window.hpp"

using namespace std;

#define VIEWPORT_MARGIN 20

class View {

private:
  GtkBuilder *builder;

  GtkWidget *gtkWindow;
  GtkWidget *addObjectWindow;
  GtkWidget *editObjectWindow;
  GtkWidget *drawAreaViewPort;
  GtkWidget *gtkTextView;

  /*! Entries for parameters of GraphicalObjects to be futher created */
  GtkEntry *entryPointX;
  GtkEntry *entryPointY;
  GtkEntry *entryPointZ;
  GtkEntry *entryLineX1;
  GtkEntry *entryLineY1;
  GtkEntry *entryLineZ1;
  GtkEntry *entryLineX2;
  GtkEntry *entryLineY2;
  GtkEntry *entryLineZ2;
  GtkEntry *entryPolygonX;
  GtkEntry *entryPolygonY;
  GtkEntry *entryPolygonZ;
  GtkEntry *entryCurveX;
  GtkEntry *entryCurveY;
  GtkEntry *entryCurveZ;
  GtkEntry *entryTranslationX;
  GtkEntry *entryTranslationY;
  GtkEntry *entryTranslationZ;
  GtkEntry *entryScalingX;
  GtkEntry *entryScalingY;
  GtkEntry *entryScalingZ;
  GtkEntry *objectName;
  GtkEntry *entryStep;
  GtkEntry *entryAngle;
  GtkEntry *entryRotationX;
  GtkEntry *entryRotationY;
  GtkEntry *entryRotationZ;
  GtkEntry *entryObjWorldFile;
  GtkEntry *entryAngleRotateWindow;
  GtkEntry *entryDelta;
  GtkEntry *entry3DX1;
  GtkEntry *entry3DY1;
  GtkEntry *entry3DZ1;
  GtkEntry *entry3DX2;
  GtkEntry *entry3DY2;
  GtkEntry *entry3DZ2;
  GtkEntry *entrySurfaceX;
  GtkEntry *entrySurfaceY;
  GtkEntry *entrySurfaceZ;

  GtkListBox *objectsListBox;      //!< shows the name of the objects drawn
  GtkListBox *listCoordPolygon;    //!< shows the coordinates added when creating a polygon
  GtkListBox *listCoordCurve;      //!< shows the coordinates added when creating a curve
  GtkListBox *listCoordSurface;    //!< shows the coordinates added when creating a surface
  GtkListBox *listSegment;

  GtkNotebook *notebookObjects;  //!< GtkNotebook to create different graphical objects (e.g Points, Polygons)
  GtkNotebook *notebookObjectOperations;

  GtkScale *scalePerspective;
  GtkAdjustment *scaleValues;

  Drawer* drawer;
  Window* window;
  ViewPort* viewPort;
  Scn* scn;
  Logger* logger;
  Opp* opp;
  Perspective* pers;

  int rotationRadioButtonState;
  int clippingRadioButtonState;
  int projectionRadioButtonState;
  int objRotateRadioButtonState;
  bool checkFillButtonState;
  bool checkIsSplineState;
  bool checkIsSplineSurfaceState;

public:
  View() {
    drawer = new Drawer();
    scn = new Scn();
    logger = new Logger();
    opp = new Opp();
    pers = new Perspective();
  }

  //! Startup the user interface: initiates GTK, creates all graphical elements and runs gtk_main();
  void initializeGtkWindow(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "windows.glade", NULL);

    gtkWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    addObjectWindow = GTK_WIDGET(gtk_builder_get_object(builder, "windowInserirCoord"));
    editObjectWindow = GTK_WIDGET(gtk_builder_get_object(builder, "windowEditObject"));
    drawAreaViewPort = GTK_WIDGET(gtk_builder_get_object(builder, "drawAreaViewPort"));
    gtkTextView = GTK_WIDGET(gtk_builder_get_object(builder, "textView"));
    logger->setTextView(gtkTextView);

    entryPointX = GTK_ENTRY(gtk_builder_get_object(builder, "entryPointX"));
    entryPointY = GTK_ENTRY(gtk_builder_get_object(builder, "entryPointY"));
    entryPointZ = GTK_ENTRY(gtk_builder_get_object(builder, "entryPointZ"));
    objectName = GTK_ENTRY(gtk_builder_get_object(builder, "entryNovoObjeto"));
    entryLineX1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineX"));
    entryLineY1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineY"));
    entryLineZ1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineZ"));
    entryLineX2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineX1"));
    entryLineY2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineY1"));
    entryLineZ2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineZ1"));
    entryPolygonX = GTK_ENTRY(gtk_builder_get_object(builder, "entryPolygonX"));
    entryPolygonY = GTK_ENTRY(gtk_builder_get_object(builder, "entryPolygonY"));
    entryPolygonZ = GTK_ENTRY(gtk_builder_get_object(builder, "entryPolygonZ"));
    entryCurveX = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurveX"));
    entryCurveY = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurveY"));
    entryCurveZ = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurveZ"));
    entryStep = GTK_ENTRY(gtk_builder_get_object(builder, "inputStep"));
    entryTranslationX = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslationX"));
    entryTranslationY = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslationY"));
    entryTranslationZ = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslationZ"));
    entryScalingX = GTK_ENTRY(gtk_builder_get_object(builder, "entryScalingX"));
    entryScalingY = GTK_ENTRY(gtk_builder_get_object(builder, "entryScalingY"));
    entryScalingZ = GTK_ENTRY(gtk_builder_get_object(builder, "entryScalingZ"));
    entryAngle = GTK_ENTRY(gtk_builder_get_object(builder, "entryAngle"));
    entryRotationX = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotationX"));
    entryRotationY = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotationY"));
    entryRotationZ = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotationZ"));
    entryObjWorldFile = GTK_ENTRY(gtk_builder_get_object(builder, "entryObjWorldFile"));
    entryAngleRotateWindow = GTK_ENTRY(gtk_builder_get_object(builder, "entryAngleRotateWindow"));
    entryDelta = GTK_ENTRY(gtk_builder_get_object(builder, "entryDelta"));
    entry3DX1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3DX1"));
    entry3DY1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3DY1"));
    entry3DZ1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3DZ1"));
    entry3DX2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3DX2"));
    entry3DY2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3DY2"));
    entry3DZ2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3DZ2"));
    entrySurfaceX = GTK_ENTRY(gtk_builder_get_object(builder, "entrySurfaceX"));
    entrySurfaceY = GTK_ENTRY(gtk_builder_get_object(builder, "entrySurfaceY"));
    entrySurfaceZ = GTK_ENTRY(gtk_builder_get_object(builder, "entrySurfaceZ"));

    objectsListBox = GTK_LIST_BOX(gtk_builder_get_object(builder, "listaObjetos"));
    listCoordPolygon = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox2"));
    listCoordCurve = GTK_LIST_BOX(gtk_builder_get_object(builder, "listboxCurveCoords"));
    listCoordSurface = GTK_LIST_BOX(gtk_builder_get_object(builder, "coordSurfaceListBox"));
    listSegment = GTK_LIST_BOX(gtk_builder_get_object(builder, "listSegment"));

    notebookObjects = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(builder), "notebookObjects"));
    notebookObjectOperations = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(builder), "notebookObjectOperations"));

    scalePerspective = GTK_SCALE(gtk_builder_get_object(GTK_BUILDER(builder), "scaleValues"));
    scaleValues = GTK_ADJUSTMENT(gtk_builder_get_object(GTK_BUILDER(builder), "adjustment2"));

    rotationRadioButtonState = 1;
    clippingRadioButtonState = 1;
    projectionRadioButtonState = 1;
    objRotateRadioButtonState = 1;
    checkFillButtonState = false;
    checkIsSplineState = false;
    checkIsSplineSurfaceState = false;

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(gtkWindow);
    gtk_main();
  }

  ~View() {}

  /**
   * Creates the two main structures responsible for drawing elements in the screen:
   * Window (window) and ViewPort (viewPort). Their sizes are based on
   * 'drawAreaViewPort' GtkWidget.
   */
  void initializeWindowViewPort() {
    double xMin = 0;
    double yMin = 0;
    double xMax = (double) gtk_widget_get_allocated_width(drawAreaViewPort);
    double yMax = (double) gtk_widget_get_allocated_height(drawAreaViewPort);

    Coordinate* coordMin = new Coordinate(xMin+VIEWPORT_MARGIN, yMin+VIEWPORT_MARGIN);
    Coordinate* coordMax = new Coordinate(xMax-VIEWPORT_MARGIN, yMax-VIEWPORT_MARGIN);
    vector<Coordinate*> vpCoord = {coordMin, coordMax};

    Coordinate* wCoordMin = new Coordinate(-xMax/2, -yMax/2, 0);
    Coordinate* wCoordMax = new Coordinate(xMax/2, yMax/2, 0);
    vector<Coordinate*> windowCoord = {wCoordMin, wCoordMax};

    window = new Window(windowCoord);
    viewPort = new ViewPort(vpCoord, window);

    drawViewPortArea();
  }

  void openAddObjectWindow() {
    gtk_widget_show(addObjectWindow);
  }

  void openEditObjectWindow() {
    gtk_widget_show(editObjectWindow);
  }

  void create_surface(GtkWidget *widget) {
    drawer->create_surface(widget);
  }

  void draw(cairo_t *cr) {
    drawer->draw(cr);
  }

  void drawViewPortArea() {
    drawer->drawViewPortArea(getViewPortCoord().back(), VIEWPORT_MARGIN);
  }

  void drawNewPoint(Point* obj) {
    drawer->drawPoint(obj->getCoordinates().front());
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewLine(Line* obj) {
    drawer->drawLine(obj->getCoordinates().front(), obj->getCoordinates().back());
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewPolygon(Polygon* obj, bool fill) {
    vector<Coordinate*> polygonPoints = obj->getWindowPoints();

    drawer->drawPolygon(polygonPoints, fill);
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewCurve(Curve* obj) {
    vector<Coordinate*> points = obj->getWindowPoints();

    drawer->drawCurve(points);
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewSurface(Surface* obj) {
    vector<Curve*> curves = obj->getCurves();
    vector<Curve*>::iterator curve;
    for(curve = curves.begin(); curve != curves.end(); curve++) {
      drawNewCurve(*curve);
    }
  }

  void drawNewObject3D(Object3D* obj) {
    vector<Segment*> segments = static_cast<Object3D*>(obj)->getSegmentList();
    vector<Segment*>::iterator segment;
    for(segment = segments.begin(); segment != segments.end(); segment++) {
      if ((*segment)->isVisible()) {
        vector<Coordinate*> tmp = (*segment)->getCoordinates();
        drawer->drawLine(tmp[0], tmp[1]);
      }
    }
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void clearPolygonEntry() {
    removeAllCoordinates(listCoordPolygon);
    clearCoordEntries(entryPolygonX, entryPolygonY, entryPolygonZ);
  }

  void clearCurveEntry() {
    removeAllCoordinates(listCoordCurve);
    clearCoordEntries(entryCurveX, entryCurveY, entryCurveZ);
  }

  void clearSurfaceEntry() {
    removeAllCoordinates(listCoordSurface);
    clearCoordEntries(entrySurfaceX, entrySurfaceY, entrySurfaceZ);
  }

  void clearObjet3DEntry() {
    removeAllCoordinates(listSegment);
    clearCoordEntries(entry3DX1, entry3DY1, entry3DZ1);
    clearCoordEntries(entry3DX2, entry3DY2, entry3DZ2);
  }

  void insertIntoListBox(GraphicObject& obj, string tipo) {
    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new((obj.getObjectName() + " (" + tipo + ")").c_str());

    gtk_container_add((GtkContainer*) objectsListBox, label);
    gtk_widget_show_all((GtkWidget*) objectsListBox);
  }

  void insertCoordList(GtkListBox* list, double x, double y, double z) {
    string coordX = to_string_with_precision(x);
    string coordY = to_string_with_precision(y);
    string coordZ = to_string_with_precision(z);

    string name = "Coordenada: (" + coordX + " , " + coordY + " , " + coordZ + ")";

    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new(name.c_str());

    gtk_container_add((GtkContainer*) list, label);
    gtk_widget_show_all((GtkWidget*) list);
  }

  // Try to find a way to create a generic method from this method and the above
  void insertCoordList(GtkListBox* list, double x, double y, double z, double x1, double y1, double z1) {
    string coordX = to_string_with_precision(x);
    string coordY = to_string_with_precision(y);
    string coordZ = to_string_with_precision(z);
    string coordX1 = to_string_with_precision(x1);
    string coordY1 = to_string_with_precision(y1);
    string coordZ1 = to_string_with_precision(z1);

    string name = "Coordenada: (" + coordX + " , " + coordY + " , " + coordZ + ")";
    name += " -> ";
    name += "Coordenada: (" + coordX1 + " , " + coordY1 + " , " + coordZ1 + ")";

    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new(name.c_str());

    gtk_container_add((GtkContainer*) list, label);
    gtk_widget_show_all((GtkWidget*) list);
  }

  string to_string_with_precision(double number) {
    ostringstream out;

    out.precision(2);
    out << fixed << number;

    return out.str();
  }

  //! Removes the selected element in GtkListBox
  /*!
   * @return The index of the removed element
   */
  int removeFromList(GtkListBox* list) {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(list);
    int index = -1;

    if (row == NULL) {
      string errorType = (list == objectsListBox) ?
			  "Nenhum objeto selecionado!\n"
			  : "Nenhuma coordenada selecionada!\n";
      logger->logError(errorType);
    } else {
      index = gtk_list_box_row_get_index(row);
      gtk_container_remove((GtkContainer*) list, (GtkWidget*) row);
    }

    return index;
  }

  void removeAllCoordinates(GtkListBox* listCoord) {
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(listCoord));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
      gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
  }

  void updateRadioBtnState(int newState) {
    rotationRadioButtonState = newState;
  }

  void updateClippingRadioBtnState(int newState) {
    clippingRadioButtonState = newState;
  }

  void updateCheckBtnState () {
    checkFillButtonState = !checkFillButtonState;
  }

  void updateProjectionBtnState (int newState) {
    projectionRadioButtonState = newState;
  }

  void updateObjRotateBtnState(int newState) {
    objRotateRadioButtonState = newState;
  }

  void updateCheckBtnSpline() {
    checkIsSplineState = !checkIsSplineState;
  }

  void updateCheckBtnSplineSurface() {
    checkIsSplineSurfaceState = !checkIsSplineSurfaceState;
  }

  void updateWindow(double step, int op) {
    switch (op) {
      case 0:
        this->window->zoomIn(step);
        break;
      case 1:
        this->window->zoomOut(step);
        break;
      case 2:
        this->window->goRight(step/100);
        break;
      case 3:
        this->window->goLeft(step/100);
        break;
      case 4:
        this->window->goUp(step/100);
        break;
      case 5:
        this->window->goDown(step/100);
        break;
      case 6:
        this->window->goUpLeft(step/100);
        break;
      case 7:
        this->window->goUpRight(step/100);
        break;
      case 8:
        this->window->goDownLeft(step/100);
        break;
      case 9:
        this->window->goDownRight(step/100);
        break;
      case 10:
        this->window->goCenter();
        break;
      case 11:
        this->window->setAngleX(step);
        break;
      case 12:
        this->window->setAngleY(step);
        break;
      case 13:
        this->window->setAngleZ(step);
        break;
    }
  }

  //! Calls ViewPort::transformation() for each point of 'object'
  /*!
   * @param object The GraphicObject that its coordinates will be transformed to
   * 	corresponding ViewPort coordinates.
   */
  void transform(GraphicObject* object) {
    switch (object->getType()) {
      case POINT:
        this->worldToViewPort(static_cast<GraphicObject2D*>(object)->getCoordinates());
        break;
      case LINE:
        this->worldToViewPort(static_cast<GraphicObject2D*>(object)->getCoordinates());
        break;
      case POLYGON:
        this->worldToViewPort(static_cast<Polygon*>(object)->getWindowPoints());
        break;
      case CURVE:
        this->worldToViewPort(static_cast<Curve*>(object)->getWindowPoints());
        break;
      case OBJECT3D:
        this->worldToViewPort(static_cast<Object3D*>(object)->getAllCoord());
        break;
      case SURFACE:
        vector<Curve*> curves = static_cast<Surface*>(object)->getCurves();
        vector<Curve*>::iterator curve;
        for (curve = curves.begin(); curve != curves.end(); curve++) {
          this->worldToViewPort(static_cast<Curve*>(*curve)->getWindowPoints());
        }
        break;
    }
  }

  void worldToViewPort(vector<Coordinate*> points) {
    vector<Coordinate*>::iterator it;
    for(it = points.begin(); it != points.end(); it++) {
      viewPort->transformation(*it);
    }
  }

  string chooseFile() {
    string fileName;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File",
        GTK_WINDOW (gtkWindow),
        action,
        "_Cancel",
        GTK_RESPONSE_CANCEL,
        "_Open",
        GTK_RESPONSE_ACCEPT,
        NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      fileName = gtk_file_chooser_get_filename(chooser);
    }

    gtk_widget_destroy(dialog);
    return fileName;
  }

  void computeAngleForProjection(Coordinate* cop) {
    Coordinate vrp = window->getGeometricCenter();
    if (getProjectionBtnState()) {
      paralellAngle(window, &vrp);
    } else {
      perspectiveAngle(window, &vrp, cop);
    }
  }

  void paralellAngle(Window* window, Coordinate* vrp) {
    opp->computeAngle(window, vrp);
    opp->transformation(window->getCoordinates(), vrp);
  }

  void perspectiveAngle(Window* window, Coordinate* vrp, Coordinate* cop) {
    pers->computeAngle(vrp, cop);
    // TODO Quick fix - rewrite that (see orthogonalParallelProjection.hpp)
    Coordinate* w1t = window->getCoordinates()[0];
    Coordinate* w2t = window->getCoordinates()[1];

    w1t->setXop(w1t->getX()); w1t->setYop(w1t->getY()); w1t->setZop(w1t->getZ());
    w2t->setXop(w2t->getX()); w2t->setYop(w2t->getY()); w2t->setZop(w2t->getZ());

    Coordinate xa = window->getGeometricCenter();
    pers->transformation(window->getCoordinates(), &xa , cop);
  }

  void transformProjection(GraphicObject* obj, Coordinate* cop) {
    Coordinate geometriCenter = window->getGeometricCenter();
    if (getProjectionBtnState())
      transformOPP(obj, &geometriCenter);
    else
      transformPerspective(obj, cop);
  }

  void transformOPP(GraphicObject* elem, Coordinate* vrp) {
    if (elem->getType() != OBJECT3D && elem->getType() != SURFACE) {
      opp->transformation(
                  static_cast<GraphicObject2D*>(elem)->getCoordinates(), vrp);
    } else {
      opp->transformation(static_cast<Object3D*>(elem)->getAllCoord(), vrp);
    }
  }

  void transformPerspective(GraphicObject* elem, Coordinate* cop) {
    Coordinate xa = window->getGeometricCenter();
    if (elem->getType() != OBJECT3D && elem->getType() != SURFACE) {
      pers->transformation(
              static_cast<GraphicObject2D*>(elem)->getCoordinates(), &xa, cop);
    } else {
      pers->transformation(static_cast<Object3D*>(elem)->getAllCoord(), &xa, cop);
    }
  }

  void transformSCN(GraphicObject* elem) {
    window->computePersGeometricCenter();

    Coordinate* windowCoord = window->getCoordinates().back();
    Coordinate geometriCenter = window->getGeometricCenter();
    Coordinate scalingFactor(1/windowCoord->getXop(), 1/windowCoord->getYop());

    if (elem->getType() != OBJECT3D && elem->getType() != SURFACE) {
      scn->transformation(
                      static_cast<GraphicObject2D*>(elem)->getCoordinates(),
                      &geometriCenter,
                      &scalingFactor);
    } else {
      scn->transformation(static_cast<Object3D*>(elem)->getAllCoord(), &geometriCenter, &scalingFactor);
    }
  }

  void logWarning(string wrn) {
    logger->logWarning(wrn);
  }

  void logError(string err) {
    logger->logError(err);
  }

  void clear_surface() {
    drawer->clear_surface();
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void clearSaveWorldFile() {
  	gtk_entry_set_text(entryObjWorldFile, "");
  }

  void clearCoordEntries(GtkEntry* entry1, GtkEntry* entry2, GtkEntry* entry3) {
    gtk_entry_set_text(entry1, "");
    gtk_entry_set_text(entry2, "");
    gtk_entry_set_text(entry3, "");
  }

  ///
  /// Get methods
  ///

  double getEntryPointX() {
    return stod(gtk_entry_get_text(entryPointX));
  }

  double getEntryPointY() {
    return stod(gtk_entry_get_text(entryPointY));
  }

  double getEntryPointZ() {
    return stod(gtk_entry_get_text(entryPointZ));
  }

  double getEntryLineX1() {
    return stod(gtk_entry_get_text(entryLineX1));
  }

  double getEntryLineY1() {
    return stod(gtk_entry_get_text(entryLineY1));
  }

  double getEntryLineZ1() {
    return stod(gtk_entry_get_text(entryLineZ1));
  }

  double getEntryLineX2() {
    return stod(gtk_entry_get_text(entryLineX2));
  }

  double getEntryLineY2() {
    return stod(gtk_entry_get_text(entryLineY2));
  }

  double getEntryLineZ2() {
    return stod(gtk_entry_get_text(entryLineZ2));
  }

  double getEntryPolygonX() {
    return stod(gtk_entry_get_text(entryPolygonX));
  }

  double getEntryPolygonY() {
    return stod(gtk_entry_get_text(entryPolygonY));
  }

  double getEntryPolygonZ() {
    return stod(gtk_entry_get_text(entryPolygonZ));
  }

  double getEntryCurveX() {
    return stod(gtk_entry_get_text(entryCurveX));
  }

  double getEntryCurveY() {
    return stod(gtk_entry_get_text(entryCurveY));
  }

  double getEntryCurveZ() {
    return stod(gtk_entry_get_text(entryCurveZ));
  }

  double getEntrySurfaceX() {
    return stod(gtk_entry_get_text(entrySurfaceX));
  }

  double getEntrySurfaceY() {
    return stod(gtk_entry_get_text(entrySurfaceY));
  }

  double getEntrySurfaceZ() {
    return stod(gtk_entry_get_text(entrySurfaceZ));
  }

  double getEntryTranslationX() {
    return stod(gtk_entry_get_text(entryTranslationX));
  }

  double getEntryTranslationY() {
    return stod(gtk_entry_get_text(entryTranslationY));
  }

  double getEntryTranslationZ() {
    return stod(gtk_entry_get_text(entryTranslationZ));
  }

  double getEntryScalingX() {
    return stod(gtk_entry_get_text(entryScalingX));
  }

  double getEntryScalingY() {
    return stod(gtk_entry_get_text(entryScalingY));
  }

  double getEntryScalingZ() {
    return stod(gtk_entry_get_text(entryScalingZ));
  }

  double getEntryRotationX() {
    return stod(gtk_entry_get_text(entryRotationX));
  }

  double getEntryRotationY() {
    return stod(gtk_entry_get_text(entryRotationY));
  }

  double getEntryRotationZ() {
    return stod(gtk_entry_get_text(entryRotationZ));
  }

  double getEntry3DX1() {
    return stod(gtk_entry_get_text(entry3DX1));
  }

  double getEntry3DY1() {
    return stod(gtk_entry_get_text(entry3DY1));
  }

  double getEntry3DZ1() {
    return stod(gtk_entry_get_text(entry3DZ1));
  }

  double getEntry3DX2() {
    return stod(gtk_entry_get_text(entry3DX2));
  }

  double getEntry3DY2() {
    return stod(gtk_entry_get_text(entry3DY2));
  }

  double getEntry3DZ2() {
    return stod(gtk_entry_get_text(entry3DZ2));
  }

  double getAngleRotateWindow() {
    return stod(gtk_entry_get_text(entryAngleRotateWindow));
  }

  double getStep() {
    return stod(gtk_entry_get_text(entryStep));
  }

  double getAngle() {
    return stod(gtk_entry_get_text(entryAngle));
  }

  double getDelta() {
    return stod(gtk_entry_get_text(entryDelta));
  }

  string getObjectName() {
    return gtk_entry_get_text(objectName);
  }

  int getCurrentPage () {
    return gtk_notebook_get_current_page(notebookObjects);
  }

  int getCurrentPageTransformation () {
    return gtk_notebook_get_current_page(notebookObjectOperations);
  }

  double getNewCOP() {
    return gtk_adjustment_get_value(scaleValues);
  }

  int getCurrentObjectIndex() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(objectsListBox);
    if (row == NULL) {
      return -1;
    } else {
      return gtk_list_box_row_get_index(row);
    }
  }

  int getRotationRadioButtonState() {
    return rotationRadioButtonState;
  }

  int getLineClippingAlgorithm() {
    return clippingRadioButtonState;
  }

  bool getCheckBtnState () {
    return checkFillButtonState;
  }

  bool isCheckBtnSplineChecked() {
    return checkIsSplineState;
  }

  bool isCheckBtnSplineSurfaceChecked() {
    return checkIsSplineSurfaceState;
  }

  int getProjectionBtnState() {
    return projectionRadioButtonState;
  }

  int getObjRotateBtnState() {
    return objRotateRadioButtonState;
  }

  Window* getWindow() {
    return window;
  }

  string getFileToSaveWorld() {
    return gtk_entry_get_text(entryObjWorldFile);
  }

  vector<Coordinate*> getViewPortCoord() {
    return viewPort->getCoordinates();
  }

  GtkListBox* getListCoordCurve() {
    return listCoordCurve;
  }

  GtkListBox* getListCoordPolygon() {
    return listCoordPolygon;
  }

  GtkListBox* getListCoordSurface() {
    return listCoordSurface;
  }

  GtkListBox* getListObj() {
    return objectsListBox;
  }

  GtkListBox* getListSegment () {
    return listSegment;
  }

};

#endif  //!< VIEW_HPP
