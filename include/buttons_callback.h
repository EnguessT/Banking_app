#ifndef BUTTONS_CALLBACK_H
#define BUTTONS_CALLBACK_H

#include "types.h"

void on_login_clicked(GtkWidget *button, gpointer user_data);
gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data);
void on_create_clicked(GtkWidget *button, gpointer user_infos);
void on_logout_clicked(GtkWidget *button, gpointer user_data);


#endif