#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <sqlite3.h>
#include "types.h"


void open_registration_window(void);
void open_create_account(const gchar* name, const gchar* birth, const gchar* mail,
                const gchar* phone, const gchar* city, const gchar* street,
                const gchar* house, const gchar* zip, const gchar* password);


#endif