#ifndef VIEW_HPP
#define VIEW_HPP

#include <gtk/gtk.h>
#include <string>

#include "logger.hpp"
#include "drawer.hpp"
#include "scn.hpp"
#include "window.hpp"
#include "viewport.hpp"
#include <stdio.h>

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
  GtkEntry *entryLineX1;
  GtkEntry *entryLineY1;
  GtkEntry *entryLineX2;
  GtkEntry *entryLineY2;
  GtkEntry *entryPolygonX;
  GtkEntry *entryPolygonY;
  GtkEntry *entryCurveX;
  GtkEntry *entryCurveY;
  GtkEntry *entryTranslationX;
  GtkEntry *entryTranslationY;
  GtkEntry *entryScalingX;
  GtkEntry *entryScalingY;
  GtkEntry *objectName;
  GtkEntry *entryStep;
  GtkEntry *entryAngle;
  GtkEntry *entryRotationX;
  GtkEntry *entryRotationY;
  GtkEntry *entryObjWorldFile;
  GtkEntry *entryAngleRotateWindow;
  GtkEntry *entryDelta;

  GtkListBox *objectsListBox;    //!< shows the name of the objects drawn
  GtkListBox *listCoordPolygon;  //!< shows the coordinates added when creating a polygon
  GtkListBox *listCoordCurve;   //!< shows the coordinates added when creating a curve

  GtkNotebook *notebookObjects;  //!< GtkNotebook to create different graphical objects (e.g Points, Polygons)
  GtkNotebook *notebookObjectOperations;

  Drawer* drawer;
  Window* window;
  ViewPort* viewPort;
  Scn* scn;
  Logger* logger;

  int rotationRadioButtonState;
  int clippingRadioButtonState;
  bool checkFillButtonState;
  bool checkIsSplineState;

public:
  View() {
    drawer = new Drawer();
    scn = new Scn();
    logger = new Logger();
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
    objectName = GTK_ENTRY(gtk_builder_get_object(builder, "entryNovoObjeto"));
    entryLineX1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineX"));
    entryLineY1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineY"));
    entryLineX2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineX1"));
    entryLineY2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryLineY1"));
    entryPolygonX = GTK_ENTRY(gtk_builder_get_object(builder, "entryPolygonX"));
    entryPolygonY = GTK_ENTRY(gtk_builder_get_object(builder, "entryPolygonY"));
    entryCurveX = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurveX"));
    entryCurveY = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurveY"));
    entryStep = GTK_ENTRY(gtk_builder_get_object(builder, "inputStep"));
    entryTranslationX = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslationX"));
    entryTranslationY = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslationY"));
    entryScalingX = GTK_ENTRY(gtk_builder_get_object(builder, "entryScalingX"));
    entryScalingY = GTK_ENTRY(gtk_builder_get_object(builder, "entryScalingY"));
    entryAngle = GTK_ENTRY(gtk_builder_get_object(builder, "entryAngle"));
    entryRotationX = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotationX"));
    entryRotationY = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotationY"));
    entryObjWorldFile = GTK_ENTRY(gtk_builder_get_object(builder, "entryObjWorldFile"));
    entryAngleRotateWindow = GTK_ENTRY(gtk_builder_get_object(builder, "entryAngleRotateWindow"));
    entryDelta = GTK_ENTRY(gtk_builder_get_object(builder, "entryDelta"));

    objectsListBox = GTK_LIST_BOX(gtk_builder_get_object(builder, "listaObjetos"));
    listCoordPolygon = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox2"));
    listCoordCurve = GTK_LIST_BOX(gtk_builder_get_object(builder, "listboxCurveCoords"));

    notebookObjects = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(builder), "notebookObjects"));
    notebookObjectOperations = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(builder), "notebookObjectOperations"));

    rotationRadioButtonState = 1;
    clippingRadioButtonState = 1;
    checkFillButtonState = false;
    checkIsSplineState = false;

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

    Coordinate* wCoordMin = new Coordinate(-xMax/2, -yMax/2);
    Coordinate* wCoordMax = new Coordinate(xMax/2, yMax/2);
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

  void clear_surface() {
    drawer->clear_surface();
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
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

  void drawNewPoint(GraphicObject* obj) {
    drawer->drawPoint(obj->getCoordinates().front());
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewLine(GraphicObject* obj) {
    Coordinate* c1 = obj->getCoordinates().front();
    Coordinate* c2 = obj->getCoordinates().back();
    drawer->drawLine(c1, c2);
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  //! Draws a Polygon and properly clears elements in the "New Polygon window"
  /*!
   * @param obj The object to be drawn.
   */
  void newPolygon(GraphicObject* obj, bool fill) {
    drawNewPolygon(obj, fill);
  }

  void drawNewPolygon(GraphicObject* obj, bool fill) {
    vector<Coordinate*> polygonPoints = obj->getWindowPoints();
    drawer->drawPolygon(polygonPoints, fill);
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
    removeAllPolygonCoordinates();
    clearPolygonCoordEntries();
  }

  void drawNewCurve(GraphicObject* obj) {
    vector<Coordinate*> points = obj->getWindowPoints(); //TODO getWindowPoints();
    drawer->drawCurve(points);
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
    removeAllCurveCoordinates();
    clearCurveCoordEntries();
  }

  void insertIntoListBox(GraphicObject& obj, string tipo) {
    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new((obj.getObjectName() + " (" + tipo + ")").c_str());

    gtk_container_add((GtkContainer*) objectsListBox, label);
    gtk_widget_show_all((GtkWidget*) objectsListBox);
  }

  void insertCoordPolygonList() {
    string coordX = gtk_entry_get_text(entryPolygonX);
    string coordY = gtk_entry_get_text(entryPolygonY);
    string name = "Coordenada: (" + coordX + " , " + coordY + ")";

    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new(name.c_str());

    gtk_container_add((GtkContainer*) listCoordPolygon, label);
    gtk_widget_show_all((GtkWidget*) listCoordPolygon);
  }

  void insertCoordCurveList() {
    string coordX = gtk_entry_get_text(entryCurveX);
    string coordY = gtk_entry_get_text(entryCurveY);
    string name = "Coordenada: (" + coordX + " , " + coordY + ")";

    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new(name.c_str());

    gtk_container_add((GtkContainer*) listCoordCurve, label);
    gtk_widget_show_all((GtkWidget*) listCoordCurve);
  }

  //! Removes the selected element in GtkListBox
  /*!
   * @return The index of the removed element
   */
  int removeSelectedObject() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(objectsListBox);
    int index = -1;
    if (row == NULL) {
      logger->logError("Nenhum objeto selecionado!\n");
    } else {
      index = gtk_list_box_row_get_index(row);
      gtk_container_remove((GtkContainer*) objectsListBox, (GtkWidget*) row);
    }
    return index;
  }

  int removeFromCoordPolygonList() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(listCoordPolygon);
    int index = -1;
    if (row == NULL) {
      logger->logError("Nenhuma coordenada selecionada!\n");
    } else {
      gtk_container_remove((GtkContainer*) listCoordPolygon, (GtkWidget*) row);
      index = getCurrentObjectIndex();
    }
    return index;
  }

  int removeFromCoordCurveList() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(listCoordCurve);
    int index = -1;
    if (row == NULL) {
      logger->logError("Nenhuma coordenada selecionada!\n");
    } else {
      gtk_container_remove((GtkContainer*) listCoordCurve, (GtkWidget*) row);
      index = getCurrentObjectIndex();
    }
    return index;
  }

  void removeAllPolygonCoordinates() {
  	do {
  	  GtkListBoxRow* row = gtk_list_box_get_row_at_index(listCoordPolygon, 0);
  	  gtk_list_box_select_row(listCoordPolygon, row);
  	  gtk_container_remove((GtkContainer*) listCoordPolygon, (GtkWidget*) row);
  	} while (gtk_list_box_get_row_at_index(listCoordPolygon, 0) != NULL);
  }

  void removeAllCurveCoordinates() {
  	do {
  	  GtkListBoxRow* row = gtk_list_box_get_row_at_index(listCoordCurve, 0);
  	  gtk_list_box_select_row(listCoordCurve, row);
  	  gtk_container_remove((GtkContainer*) listCoordCurve, (GtkWidget*) row);
  	} while (gtk_list_box_get_row_at_index(listCoordCurve, 0) != NULL);
  }

  void clearPolygonCoordEntries() {
  	gtk_entry_set_text(entryPolygonX, "");
  	gtk_entry_set_text(entryPolygonY, "");
  }

  void clearCurveCoordEntries() {
  	gtk_entry_set_text(entryCurveX, "");
  	gtk_entry_set_text(entryCurveY, "");
  }

  void updateRadioButtonState(int newState) {
    rotationRadioButtonState = newState;
  }

  void updateClippingRadioButtonState(int newState) {
    clippingRadioButtonState = newState;
  }

  void updateCheckBtnState () {
    checkFillButtonState = !checkFillButtonState;
  }

  void updateCheckBtnSpline() {
	checkIsSplineState = !checkIsSplineState;
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
        this->window->setAngle(-step);
        break;
      case 12:
        this->window->setAngle(step);
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
        viewPort->transformation(object->getCoordinates().front());
        break;
      case LINE:
        viewPort->transformation(object->getCoordinates().front());
        viewPort->transformation(object->getCoordinates().back());
        break;
      case POLYGON:
        multiPointsTransformation(object->getWindowPoints());
        break;
      case CURVE:
        multiPointsTransformation(object->getWindowPoints());
        break;
    }
  }

  void multiPointsTransformation(vector<Coordinate*> points) {
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

  void transformSCN(GraphicObject* elem, Coordinate* geometriCenter, Coordinate* factor, double angle) {
    scn->transformation(elem, geometriCenter, factor, angle);
  }

  void logWarning(string wrn) {
    logger->logWarning(wrn);
  }

  void logError(string err) {
    logger->logError(err);
  }

  void clearSaveWorldFile() {
  	gtk_entry_set_text(entryObjWorldFile, "");
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

  double getEntryLineX1() {
    return stod(gtk_entry_get_text(entryLineX1));
  }

  double getEntryLineY1() {
    return stod(gtk_entry_get_text(entryLineY1));
  }

  double getEntryLineX2() {
    return stod(gtk_entry_get_text(entryLineX2));
  }

  double getEntryLineY2() {
    return stod(gtk_entry_get_text(entryLineY2));
  }

  double getEntryPolygonX() {
    return stod(gtk_entry_get_text(entryPolygonX));
  }

  double getEntryPolygonY() {
    return stod(gtk_entry_get_text(entryPolygonY));
  }

  double getEntryCurveX() {
    return stod(gtk_entry_get_text(entryCurveX));
  }

  double getEntryCurveY() {
    return stod(gtk_entry_get_text(entryCurveY));
  }

  double getEntryTranslationX() {
    return stod(gtk_entry_get_text(entryTranslationX));
  }

  double getEntryTranslationY() {
    return stod(gtk_entry_get_text(entryTranslationY));
  }

  double getEntryScalingX() {
    return stod(gtk_entry_get_text(entryScalingX));
  }

  double getEntryScalingY() {
    return stod(gtk_entry_get_text(entryScalingY));
  }

  double getEntryRotationX() {
    return stod(gtk_entry_get_text(entryRotationX));
  }

  double getEntryRotationY() {
    return stod(gtk_entry_get_text(entryRotationY));
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

  Window* getWindow() {
    return window;
  }

  string getFileToSaveWorld() {
    return gtk_entry_get_text(entryObjWorldFile);
  }

  vector<Coordinate*> getViewPortCoord() {
    return viewPort->getCoordinates();
  }

};

#endif  //!< VIEW_HPP
