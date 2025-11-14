#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
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
void open_signup_window(void);
gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data);
void on_login_clicked(GtkWidget *button, gpointer user_data);
void open_connect_window(const gchar* name, const gchar* pass);
void on_create_clicked(GtkWidget *button, gpointer user_infos);
void open_create_account(const gchar* name, const gchar* birth, const gchar* mail,
                const gchar* phone, const gchar* city, const gchar* street,
                const gchar* house, const gchar* zip,
                const gchar* ID, const gchar* password); 


#endif