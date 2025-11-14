#include"graphical_widgets.h"
#include <gtk/gtk.h>


GtkWidget* create_main_window(void){

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //set window default position
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //set the window not resizable
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    //set window title
	gtk_window_set_title(GTK_WINDOW(window), "Bank Account");
    //set window default border width
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    //set window default size
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}