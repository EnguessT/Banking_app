#include "../../include/client_window.h"

/**
 * This function opens Client window after 
 * login was successful
 */
void open_client_window(void) {
    GtkWidget *user_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(user_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(user_window), FALSE);
    gtk_window_set_title(GTK_WINDOW(user_window), "Bank Account");
    gtk_container_set_border_width(GTK_CONTAINER(user_window), 10);

    gtk_window_set_default_size(GTK_WINDOW(user_window), 800, 500);
    g_signal_connect(user_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(user_window);

	gtk_main();
}