#include <gtk/gtk.h>
#include "c_handlers.h"


int main(int argc, char *argv[]) {
    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *btnIn;
    GtkWidget       *btnOut;
    GtkWidget       *btnDir;
    GtkWidget       *btnEsq;
    GtkWidget       *btnCima;
    GtkWidget       *btnBaixo;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/view/windows.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    drawAreaViewPort = GTK_WIDGET(gtk_builder_get_object(builder, "drawAreaViewPort"));
    g_signal_connect(drawAreaViewPort, "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(drawAreaViewPort, "configure-event", G_CALLBACK(create_surface), NULL);

    btnIn = GTK_WIDGET(gtk_builder_get_object(builder, "btnZooIn"));
    btnOut = GTK_WIDGET(gtk_builder_get_object(builder, "btnZoomOut"));
    btnDir = GTK_WIDGET(gtk_builder_get_object(builder, "btnDireita"));
    btnEsq = GTK_WIDGET(gtk_builder_get_object(builder, "btnEsquerda"));
    btnCima = GTK_WIDGET(gtk_builder_get_object(builder, "btnBaixo"));
    btnBaixo = GTK_WIDGET(gtk_builder_get_object(builder, "btnCima"));

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

