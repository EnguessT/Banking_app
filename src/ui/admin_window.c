#include "../../include/admin_window.h"

/**
 * This function opens a Admin window after 
 * login was successful and role Admin was proved
 */
void  open_admin_window(GtkWidget *button, gpointer data) {
    (void)button;
    GtkWindow *parent = GTK_WINDOW(data);
    GtkApplication *app =
        GTK_APPLICATION(gtk_window_get_application(parent));

    GtkWidget *admin_window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(admin_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(admin_window), FALSE);
    gtk_window_set_title(GTK_WINDOW(admin_window), "Bank Account");
    gtk_container_set_border_width(GTK_CONTAINER(admin_window), 10);

    gtk_window_set_default_size(GTK_WINDOW(admin_window), 800, 500);

    gtk_widget_show_all(admin_window);

	gtk_main();

}
