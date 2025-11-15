#ifndef REGISTRATION_H
#define REGISTRATION_H
//#include <gtk/gtk.h>
#include <stdbool.h>
#include "widgets.h"

typedef struct{
    GtkWidget *name_entry;
    GtkWidget *birth_entry;
    GtkWidget *email_entry;
    GtkWidget *phone_entry;
    GtkWidget *city_entry;
    GtkWidget *street_entry;
    GtkWidget *house_entry;
    GtkWidget *zip_entry;
    GtkWidget *password_entry;
    GtkWidget *re_password_entry;
}RegistrationContext;

void is_valid_operation(const gchar* input, const char *re_expression, const char *dialog_message);
void show_warning_dialog(const char *message);
void open_signup_window(void);
void on_create_clicked(GtkWidget *button, gpointer user_infos);
void open_create_account(const gchar* name, const gchar* birth, const gchar* mail,
                const gchar* phone, const gchar* city, const gchar* street,
                const gchar* house, const gchar* zip, const gchar* password);

int create_user_table();
char* encrypt_passwort(const char* passwort);

#endif