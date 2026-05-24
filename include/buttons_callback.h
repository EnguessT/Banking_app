#ifndef BUTTONS_CALLBACK_H
#define BUTTONS_CALLBACK_H

#include "types.h"
#include "verifications.h"
#include "admin_window.h"
#include "client_window.h"
#include "database_context.h"
#include "registration.h"

void on_login_clicked(GtkWidget *button, gpointer user_data);
gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data);
void on_create_clicked(GtkWidget *button, gpointer user_infos);


#endif