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

extern "C" G_MODULE_EXPORT void on_btn_clicked_dir(){
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_esq(){
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_cima(){
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_baixo(){
}
