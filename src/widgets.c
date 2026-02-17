#include"widgets.h"
#include <gtk-3.0/gtk/gtk.h>

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

GtkWidget* set_image(const char* filename, int width, int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, width, height, TRUE, NULL);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    gtk_widget_set_margin_top(image, 10);

    g_object_unref(pixbuf); 

    return image;
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


GtkWidget* create_entry(const gchar *entry_label) {
    GtkWidget *entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), entry_label);
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

GtkWidget* create_link_button(const gchar *li_label){
    GtkWidget *link_button = gtk_link_button_new_with_label("about:blank", li_label);
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


