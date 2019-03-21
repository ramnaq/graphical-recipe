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
    controller->openNewObjectWindow();
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

//! Connected to signal "clicked" of element "btnAddCoordenada".
extern "C" G_MODULE_EXPORT void on_btnAddCoordenada_addCoordenada() {
  try {
    controller->addNewLineForPolygon();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnRemoveObject".
extern "C" G_MODULE_EXPORT void on_btn_clicked_remove_object() {
  try {
    controller->removeFromList();
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnRemoverCoordenada".
extern "C" G_MODULE_EXPORT void on_btnRemoverCoordenada_clicked() {
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

//! Connected to signal "clicked" of element "btnDireita".
extern "C" G_MODULE_EXPORT void on_btn_clicked_dir(){
  try {
    controller->changeWindow(2);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnEsquerda".
extern "C" G_MODULE_EXPORT void on_btn_clicked_esq(){
  try {
    controller->changeWindow(3);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnCime".
extern "C" G_MODULE_EXPORT void on_btn_clicked_cima(){
  try {
    controller->changeWindow(4);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnBaixo".
extern "C" G_MODULE_EXPORT void on_btn_clicked_baixo(){
  try {
    controller->changeWindow(5);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnSupEsq".
extern "C" G_MODULE_EXPORT void on_btn_clicked_supEsq(){
  try {
    controller->changeWindow(6);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnSupDir".
extern "C" G_MODULE_EXPORT void on_btn_clicked_supDir(){
  try {
    controller->changeWindow(7);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnInfEsq".
extern "C" G_MODULE_EXPORT void on_btn_clicked_infEsq(){
  try {
    controller->changeWindow(8);
  } catch (...) {

  }
}

//! Connected to signal "clicked" of element "btnInfDir".
extern "C" G_MODULE_EXPORT void on_btn_clicked_infDir(){
  try {
    controller->changeWindow(9);
  } catch (...) {

  }
}
