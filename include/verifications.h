#ifndef CHECKING_H
#define CHECKING_H

#include <gtk-3.0/gtk/gtk.h>
#include <regex.h>
#include <stdbool.h>
#include "types.h"


void is_valid_operation(const gchar* input, const char *re_expression, const char *dialog_message);
bool is_valid_birthdate(const gchar* input);
int authenticate_user(const char* identifier, const char* passwort_input, AuthResult *output);

#endif