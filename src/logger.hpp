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

    void logWarning(string war) {
	  gtk_text_buffer_insert(buffer, &iter, war.c_str(), -1);
	}

  private:
    GtkTextView* textView;
	GtkTextBuffer* buffer;

	GtkTextIter iter;
};

#endif  //!< LOGGER_HPP

