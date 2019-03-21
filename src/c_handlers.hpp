/**
 * The c_handlers functions connected to signals related to elements from the
 * graphical interface (GTK). The link between signals and its functions are
 * defined with Glade (@see windows.glade).
 *
 * @see g_signal_connect (GTK)
 */

extern "C" G_MODULE_EXPORT void draw(GtkWidget *widget, cairo_t *cr,  gpointer   data){
  try {
    controller->draw(cr);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void create_surface(GtkWidget *widget){
  try {
    controller->create_surface(widget);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_open_window() {
  try {
    controller->openNewObjectWindow();
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_create_object() {
  try {
    controller->createObject();
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btnAddCoordenada_addCoordenada() {
  try {
    controller->addNewLineForPolygon();
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_remove_object() {
  try {
    controller->removeFromList();
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btnRemoverCoordenada_clicked() {
  try {
    controller->removeFromCoordPolygonList();
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_mainWindow_configure_event(){
  try {
    controller->initializeWindowViewPort();
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_in(){
  try {
    controller->changeWindow(0);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_out(){
  try {
    controller->changeWindow(1);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_dir(){
  try {
    controller->changeWindow(2);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_esq(){
  try {
    controller->changeWindow(3);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_cima(){
  try {
    controller->changeWindow(4);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_baixo(){
  try {
    controller->changeWindow(5);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_supEsq(){
  try {
    controller->changeWindow(6);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_supDir(){
  try {
    controller->changeWindow(7);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_infEsq(){
  try {
    controller->changeWindow(8);
  } catch (...) {

  }
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_infDir(){
  try {
    controller->changeWindow(9);
  } catch (...) {

  }
}
