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

//to create simple label without css style
GtkWidget* set_label(const gchar *label_markup) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_widget_set_margin_top(label, 5);

    gtk_label_set_markup(GTK_LABEL(label), label_markup);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE); 
    return label;
}

GtkWidget* create_label(const gchar *label_markup, GtkJustification justification) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), label_markup);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_justify(GTK_LABEL(label), justification);
    
    gtk_widget_set_name(label, "label");
    gtk_widget_set_margin_top(label, 60);
    gtk_widget_set_margin_start(label, 40); 
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    //gtk_widget_set_halign(label, GTK_ALIGN_CENTER);   

    GtkCssProvider *label_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(label_provider,
        "#label { color: white; font-size: 24px; font-weight: bold; }",
        -1, NULL);

    GtkStyleContext *label_context = gtk_widget_get_style_context(label);
    gtk_style_context_add_provider(label_context,
        GTK_STYLE_PROVIDER(label_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    return label;
}

GtkWidget* set_image(const char* filename, int width, int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, width, height, TRUE, NULL);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    gtk_widget_set_margin_top(image, 10);
    return image;
}

GtkWidget* create_entry(const gchar *entry_label) {
    GtkWidget *entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), entry_label);
    gtk_widget_set_name(entry_name, "entry");
    GtkCssProvider *user_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(user_provider,
         "#entry {"
        " background-color: white;"
        " border-radius: 10px;"
        " padding: 8px;"
        " border: 1px solid #ccc;"
        " }",
        -1, NULL);

    return entry_name;
}

GtkWidget* create_button(const gchar *button_label) {
    GtkWidget *button = gtk_button_new_with_label(button_label);
    gtk_widget_set_name(button, "button");
    GtkCssProvider *login_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(login_provider,
        "#button {"
        " background-color: #ffffff;"
        " color: #ff6f61;"
        " font-weight: bold;"
        " border-radius: 20px;"
        " padding: 10px 20px;"
        " border: none;"
        " }"
        "#login-button:hover {"
        " background-color: #0165BD;"
        " color: white;"
        " }",
        -1, NULL);

    return button;
}

GtkWidget* create_link_button(const gchar *link_label){
    const gchar *link_label = link_label;
    GtkWidget *link_button = gtk_link_button_new_with_label("about:blank", link_label);
    gtk_widget_set_name(link_button, "passwort-style");

    // CSS provider
    GtkCssProvider *link_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(link_provider,
        "#passwort-style.link, "
        "#passwort-style.link:link, "
        "#passwort-style.link:visited, "
        "#passwort-style.link:hover {"
        "  font-family: 'Sans';"  
        "  font-size: 12pt;"
        "  font-weight: bold;"
        "  color: gray;"
        "  text-decoration: underline;"
        "  background-color: transparent;"
        "  border: none;"
        "}", -1, NULL);

    // Apply provider
    GtkStyleContext *pass_context = gtk_widget_get_style_context(link_button);
    gtk_style_context_add_provider(pass_context,
                                GTK_STYLE_PROVIDER(link_provider),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);

    return link_button;
}

//when link button is clicked
gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data) {
    (void)button;
    (void) user_data;
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Password recovery coming soon!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return TRUE;  // Prevent default URI opening
}

//extract the text and call your open_connect_window():
void on_login_clicked(GtkWidget *button, gpointer user_data) {
    LoginContext *ctx = (LoginContext *)user_data;

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(ctx->username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(ctx->password_entry));

    if (g_strcmp0(username, "") == 0 || g_strcmp0(password, "") == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
            "Please enter both username and password.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        return;
    }

    open_connect_window(username, password);  // Your custom function
    //g_free(ctx);  // Only if you're done with it and not using it again
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
    GtkWidget *username_entry = create_entry("Username");

    // Password entry
    GtkWidget *passwort_entry = create_entry("Password");

    //connect the signal
    LoginContext *ctx = g_new(LoginContext, 1);
    ctx->username_entry = username_entry;
    ctx->password_entry = password_entry;

    //create login button
    login_button = create_button("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), ctx);
    
    // Remember me checkbox
    GtkWidget *remember = gtk_check_button_new_with_label("Remember me");

    //create link button passwort forgot
    GtkWidget *forgot_passwort = create_link_button("Forgot passwort");
    g_signal_connect(forgot_passwort, "activate-link", G_CALLBACK(on_link_clicked), NULL);

    // Create account prompt
    GtkWidget *create = create_button("Create Account"); 
    g_signal_connect(create, "clicked", G_CALLBACK(open_signup_window), NULL);

    //no account yet label
    const gchar *label2 = "<span foreground=\"black\" size=\'x-large\'>No account yet?</span>";
    GtkWidget *no_label = set_label(label2);
    
    gtk_box_pack_start(GTK_BOX(right_box), profile_image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), user_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), username_name, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), passwort_name, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), remember, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_box), login_button, FALSE, FALSE, 0);
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