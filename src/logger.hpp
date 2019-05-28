#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <gtk/gtk.h>
#include <string>

using namespace std;

class Logger {
public:
  void setTextView(GtkWidget* textView) {
    this->textView = GTK_TEXT_VIEW (textView);
    this->buffer = gtk_text_view_get_buffer(this->textView);
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
  }

  void logWarning(string wrn) {
    logMessage("[AVISO] " + wrn);
  }

  void logError(string err) {
    logMessage("[ERRO] " + err);
  }

private:
    GtkTextView* textView;
    GtkTextBuffer* buffer;

    GtkTextIter iter;

    void logMessage(string msg) {
      gtk_text_buffer_insert(buffer, &iter, msg.c_str(), -1);
      gtk_text_view_scroll_to_iter(textView, &iter, 0.0, false, 0.0, 0.0);
    }

};

#endif  //!< LOGGER_HPP
