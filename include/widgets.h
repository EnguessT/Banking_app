#ifndef WIDGETS_H
#define WIDGETS_H
#include <gtk-3.0/gtk/gtk.h>

void set_background_color(GtkWidget* rbox);
void set_background_image(GtkWidget* lbox);
GtkWidget* create_label(const gchar *label_markup, GtkJustification justification);
GtkWidget* set_image(const char* filename, int width, int height);
GtkWidget* set_label(const gchar *label_markup);
GtkWidget* create_entry(const gchar *entry_label);
GtkWidget* create_button(const gchar *button_label);
GtkWidget* create_link_button(const gchar *link_label);
void show_warning_dialog(const char *message);
GtkWidget* create_header_icon_button(const char *path, int size);
GtkWidget* create_button_with_icon(const char *path, const char* label);
GtkWidget* create_sidebar_row(const char *icon_path, const char *text);
GtkWidget* create_stack_page(const char* img_path, const char* label);

#endif