#ifndef TYPES_H
#define TYPES_H

#include <gtk-3.0/gtk/gtk.h>
#include <sqlite3.h>

typedef enum {
    REGISTRATION,
    LOGIN,
    DEPOSIT,
    WITHDRAW,
    TRANSFERT,
    PROFILE_UPDATE,
    DATABASE_CHECKING,
    LOGOUT
} OperationType;

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

typedef struct {
    GtkWidget *user_entry;
    GtkWidget *password_entry;
}LoginContext;

typedef struct {
    sqlite3_int64 id;
    char user_id[32];
    char role[16];
}AuthResult;

#endif