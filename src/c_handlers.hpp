/**
 * The c_handlers functions connected to signals related to elements from the
 * graphical interface (GTK). The link between signals and its functions are
 * defined with Glade (@see windows.glade).
 *
 * @see g_signal_connect (GTK)
 */

//! Connected to signal "draw" of element "drawAreaViewPort".
extern "C" G_MODULE_EXPORT void draw(GtkWidget *widget, cairo_t *cr,  gpointer   data){
  try {
    controller->draw(cr);
  } catch (...) {

  }
}

//! Connected to signal "create_surface" of element "drawAreaViewPort".
extern "C" G_MODULE_EXPORT void create_surface(GtkWidget *widget){
  try {
    controller->create_surface(widget);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnAddObject".
extern "C" G_MODULE_EXPORT void on_btn_clicked_open_window() {
  try {
    controller->openAddObjectWindow();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnOk".
extern "C" G_MODULE_EXPORT void on_btn_clicked_create_object() {
  try {
    controller->createObject();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnAddCoordinate".
extern "C" G_MODULE_EXPORT void on_btnAddCoordinate_addCoordinate() {
  try {
    controller->addNewLineForPolygon();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnRemoveObject".
extern "C" G_MODULE_EXPORT void on_btn_clicked_remove_object() {
  try {
    controller->removeSelectedObject();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnRemoveCoordinate".
extern "C" G_MODULE_EXPORT void on_btnRemoveCoordinate_clicked() {
  try {
    controller->removeFromCoordPolygonList();
  } catch (...) {

  }
}

//! Connected to signal "configure-event" of element "mainWindow".
extern "C" G_MODULE_EXPORT void on_mainWindow_configure_event(){
  try {
    controller->initializeWindowViewPort();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnZoomIn".
extern "C" G_MODULE_EXPORT void on_btn_clicked_in(){
  try {
    controller->changeWindow(0);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnZoomOut".
extern "C" G_MODULE_EXPORT void on_btn_clicked_out(){
  try {
    controller->changeWindow(1);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnRight".
extern "C" G_MODULE_EXPORT void on_btn_clicked_right(){
  try {
    controller->changeWindow(2);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnLeft".
extern "C" G_MODULE_EXPORT void on_btn_clicked_left(){
  try {
    controller->changeWindow(3);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnUp".
extern "C" G_MODULE_EXPORT void on_btn_clicked_up(){
  try {
    controller->changeWindow(4);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnDown".
extern "C" G_MODULE_EXPORT void on_btn_clicked_down(){
  try {
    controller->changeWindow(5);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnUpLeft".
extern "C" G_MODULE_EXPORT void on_btn_clicked_upLeft(){
  try {
    controller->changeWindow(6);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnUpRight".
extern "C" G_MODULE_EXPORT void on_btn_clicked_upRight(){
  try {
    controller->changeWindow(7);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnDownLeft".
extern "C" G_MODULE_EXPORT void on_btn_clicked_downLeft(){
  try {
    controller->changeWindow(8);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnDownRight".
extern "C" G_MODULE_EXPORT void on_btn_clicked_downRight(){
  try {
    controller->changeWindow(9);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnCentralize".
extern "C" G_MODULE_EXPORT void on_btn_clicked_centralize(){
  try {
    controller->changeWindow(10);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnEditObject".
extern "C" G_MODULE_EXPORT void on_btnEditObject_clicked(){
  try {
    controller->openEditObjectWindow();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnConfirmEditObject".
extern "C" G_MODULE_EXPORT void on_btnConfirmEditObject_clicked(){
  try {
    controller->executeObjectTransformation();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "radiobtnOrigin".
extern "C" G_MODULE_EXPORT void on_radiobtnOrigin_clicked(){
  try {
    controller->updateRadioButtonState(1);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "radiobtnCenter".
extern "C" G_MODULE_EXPORT void on_radiobtnCenter_clicked(){
  try {
    controller->updateRadioButtonState(2);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "radiobtnPoint".
extern "C" G_MODULE_EXPORT void on_radiobtnPoint_clicked(){
  try {
    controller->updateRadioButtonState(3);
  } catch (...) {

  }
}
