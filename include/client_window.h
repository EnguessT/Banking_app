#ifndef CLIENT_WINDOW
#define CLIENT_WINDOW

#include <gtk-3.0/gtk/gtk.h>

void open_client_window(GtkWidget *button, gpointer data);
void app_activate(GtkApplication *self, gpointer data);
GtkWidget* user_stack();

#endif
