#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <gtk/gtk.h>
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
    GtkWidget *id_entry;
    GtkWidget *password_entry;
}RegistrationContext;

bool is_valid_name(const gchar* username);
bool is_valid_birthdate(const gchar* birth_date);
bool is_valid_email_address(const gchar* email);
bool is_valid_phone_number(const gchar* phone);
bool is_valid_city(const gchar* city);
bool is_valid_street(const gchar* street);
bool is_valid_house_number(const gchar* house_number);
bool is_valid_zipcode(const gchar* zipcode);
bool is_valid_user_id(const gchar* user_id);
bool is_valid_passwort(const gchar* password);

void open_signup_window(void);
void on_create_clicked(GtkWidget *button, gpointer user_infos);
void open_create_account(const gchar* name, const gchar* birth, const gchar* mail,
                const gchar* phone, const gchar* city, const gchar* street,
                const gchar* house, const gchar* zip,
                const gchar* ID, const gchar* password);



#endif