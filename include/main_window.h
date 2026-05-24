#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "types.h"


GtkWidget* create_main_window(void);

void open_client_window(void);
void open_admin_window();
int authenticate_user(const char* identifier, const char* passwort_input, AuthResult *output);
 


#endif