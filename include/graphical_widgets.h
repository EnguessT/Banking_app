#ifndef GRAPHICAL_WIDGETS_H
#define GRAPHICAL_WIDGETS_H
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *username_entry;
    GtkWidget *password_entry;
}LoginContext;

typedef struct{
    GtkWidget *name_entry;
    GtkWidget *birth_entry;
    GtkWidget *email_entry;
    GtkWidget *phone_entry;
    GtkWidget *city_entry;
    GtkWidget *street_entry;
    GtkWidget *house_entry;
    GtkWidget *zip_entry;
    GtkWidget *id_entry;
    GtkWidget *password_entry;
}RegistrationContext;



GtkWidget* create_main_window(void);
void set_background_color(GtkWidget* rbox);
void set_background_image(GtkWidget* lbox);
GtkWidget* create_label(const gchar *label_markup, GtkJustification justification);
GtkWidget* set_image(const char* filename, int width, int height);
GtkWidget* set_label(const gchar *label_markup);
GtkWidget* create_entry(const gchar *entry_label);
GtkWidget* create_button(const gchar *button_label);
GtkWidget* create_link_button(const gchar *link_label);
gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data);
void on_login_clicked(GtkWidget *button, gpointer user_data);
#endif