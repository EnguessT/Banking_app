#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <sqlite3.h>
#include <gtk-3.0/gtk/gtk.h>

typedef struct {
    GtkWidget *user_entry;
    GtkWidget *password_entry;
}LoginContext;

typedef struct {
    sqlite3_int64 id;
    char user_id[32];
    char role[16];
}AuthResult;


GtkWidget* create_main_window(void);

gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data);
void on_login_clicked(GtkWidget *button, gpointer user_data);
void open_client_window(void);
void  open_admin_window();
int authenticate_user(const char* identifier, const char* passwort_input, AuthResult *output);
 


#endif