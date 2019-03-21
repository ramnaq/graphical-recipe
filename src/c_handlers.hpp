/**
 * The c_handlers functions connected to signals related to elements from the
 * graphical interface (GTK). The link between signals and its functions are
 * defined with Glade (@see windows.glade).
 *
 * @see g_signal_connect (GTK)
 */

extern "C" G_MODULE_EXPORT void draw(GtkWidget *widget, cairo_t *cr,  gpointer   data){
  controller->draw(cr);
}

extern "C" G_MODULE_EXPORT void create_surface(GtkWidget *widget){
  controller->create_surface(widget);
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_open_window() {
  controller->openNewObjectWindow();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_create_object() {
  controller->createObject();
}

extern "C" G_MODULE_EXPORT void on_btnAddCoordenada_addCoordenada() {
  controller->addNewLineForPolygon();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_remove_object() {
  controller->removeFromList();
}

extern "C" G_MODULE_EXPORT void on_btnRemoverCoordenada_clicked() {
  controller->removeFromCoordPolygonList();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_in(){
  controller->zoomIn();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_out(){
  controller->zoomOut();
}

extern "C" G_MODULE_EXPORT void on_mainWindow_configure_event(){
  controller->initializeWindowViewPort();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_dir(){
  controller->goRight();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_esq(){
  controller->goLeft();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_cima(){
  controller->goUp();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_baixo(){
  controller->goDown();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_supEsq(){
  controller->goUpLeft();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_supDir(){
  controller->goUpRight();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_infEsq(){
  controller->goDownLeft();
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_infDir(){
  controller->goDownRight();
}
