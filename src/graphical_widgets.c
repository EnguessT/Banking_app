#include"graphical_widgets.h"
#include <gtk/gtk.h>

void set_background_image(GtkWidget* lbox){
    GtkCssProvider *lprovider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(lprovider,
        "#left-box { background-image: url(\"images/background.png\");background-size: cover;"
        " padding: 20px;"
        " border-radius: 15px;"
        "}", 
        -1, NULL);

    GtkStyleContext *lcontext = gtk_widget_get_style_context(lbox);
    gtk_style_context_add_provider(lcontext, GTK_STYLE_PROVIDER(lprovider),
                                    GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void set_background_color(GtkWidget* rbox){
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "#right-box { background-color: #0165BD;"
        " padding: 20px;"
        " border-radius: 15px;"
        "}",
        -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(rbox);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                    GTK_STYLE_PROVIDER_PRIORITY_USER);

}

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

    //create parent box container
    GtkWidget *parent_box = gtk_box_new(0, 5);
	gtk_container_add(GTK_CONTAINER(window), parent_box);

    //vertical left box container for  title and logo
    GtkWidget *left_box = gtk_box_new(1, 10);
    gtk_widget_set_size_request(left_box, 300, -1); 
    gtk_widget_set_name(left_box, "left-box");

    //add an image as background
    set_background_image(left_box);

    //vertical right box container for user inputs
    GtkWidget *right_box = gtk_box_new(1, 5);
    gtk_widget_set_name(right_box, "right-box");

    //set a backgroung color using css
    set_background_color(right_box);

    //line separator for the bleft and right boxes
    GtkWidget *box_separator = gtk_separator_new(0);
    gtk_widget_set_size_request(box_separator, 2, -1);  

	gtk_box_pack_start(GTK_BOX(parent_box), left_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(parent_box), box_separator, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(parent_box), right_box, TRUE, TRUE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}