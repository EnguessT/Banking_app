#ifndef GRAPHICAL_WIDGETS_H
#define GRAPHICAL_WIDGETS_H
#include <gtk/gtk.h>

GtkWidget* create_main_window(void);
void set_background_color(GtkWidget* rbox);
void set_background_image(GtkWidget* lbox);
GtkWidget* create_label(const gchar *label_markup);
GtkWidget* set_image(const char* filename, int width, int height);
#endif