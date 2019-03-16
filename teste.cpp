#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "windows.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);
    gtk_main();

    return 0;
}
