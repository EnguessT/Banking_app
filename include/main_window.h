#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *user_entry;
    GtkWidget *password_entry;
}LoginContext;




GtkWidget* create_main_window(void);

gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data);
void on_login_clicked(GtkWidget *button, gpointer user_data);
void open_connect_window(const gchar* name, const gchar* pass);
int authenticate_user(const char* identifier, const char* passwort_input);
 


#endif