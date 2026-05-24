#include <string.h>
#include "../../include/main_window.h"
#include "../../include/widgets.h"
#include "../../include/registration.h"
#include "../../include/buttons_callback.h"


/**
 * This function create the Main window 
 */
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

    //create an image for bank image
    GtkWidget *bank_image = set_image("images/banking.png", 70, 70);
    //set the label
    const gchar *markup = "<span foreground='white' size='28000'>Hello,\n<b>Welcome!</b></span>";
    GtkWidget *hello_label = create_label(markup, GTK_JUSTIFY_LEFT);

    gtk_box_pack_start(GTK_BOX(left_box), bank_image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), hello_label, FALSE, FALSE, 0);

    //vertical right box container for user inputs
    GtkWidget *right_box = gtk_box_new(1, 5);
    gtk_widget_set_name(right_box, "right-box");

    //set a backgroung color using css
    set_background_color(right_box);

    //create an image for profile image
    GtkWidget *profile_image = set_image("images/profile.png", 90, 90);

    //set uername title label 
    const gchar *u_label = "<b><span foreground=\"black\" size=\'x-large\'>USER  LOGIN</span></b>";
    GtkWidget *user_label = set_label(u_label);

    // Username entry
    GtkWidget *user_entry = create_entry("User_ID or Email");

    // Password entry
    GtkWidget *password_entry = create_entry("Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    //connect the signal
    LoginContext *ctx = g_new(LoginContext, 1);
    ctx->user_entry = user_entry;
    ctx->password_entry = password_entry;

    //create login button
    GtkWidget *login_button = create_button("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), ctx);
    
    // Remember me checkbox
    GtkWidget *remember = gtk_check_button_new_with_label("Remember me");

    //create link button passwort forgot
    GtkWidget *forgot_passwort = create_link_button("Forgot passwort");
    g_signal_connect(forgot_passwort, "activate-link", G_CALLBACK(on_link_clicked), NULL);

    // Create account prompt
    GtkWidget *create = create_button("Create Account"); 
    g_signal_connect(create, "clicked", G_CALLBACK(open_registration_window), NULL);

    //no account yet label
    const gchar *label2 = "<span foreground=\"black\" size=\'x-large\'>No account yet?</span>";
    GtkWidget *no_label = set_label(label2);
    
    gtk_box_pack_start(GTK_BOX(right_box), profile_image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), user_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), user_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), password_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), login_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), remember, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), forgot_passwort, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(right_box), create, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(right_box), no_label, FALSE, FALSE, 0);

    //line separator for the bleft and right boxes
    GtkWidget *box_separator = gtk_separator_new(0);
    gtk_widget_set_size_request(box_separator, 2, -1);  

	gtk_box_pack_start(GTK_BOX(parent_box), left_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(parent_box), box_separator, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(parent_box), right_box, TRUE, TRUE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}