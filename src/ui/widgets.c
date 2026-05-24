#include"../../include/widgets.h"

void set_background_image(GtkWidget* lbox){
    GtkStyleContext *lprovider = gtk_widget_get_style_context(lbox);
    gtk_style_context_add_class(lprovider, "left-box");
    
}

void set_background_color(GtkWidget* rbox){
    GtkStyleContext *rprovider = gtk_widget_get_style_context(rbox);
    gtk_style_context_add_class(rprovider, "left-box");
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
    
    gtk_widget_set_margin_top(label, 60);
    gtk_widget_set_margin_start(label, 40); 
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    GtkStyleContext *label_provider = gtk_widget_get_style_context(label);
    gtk_style_context_add_class(label_provider, "big-label");

    return label;
}


GtkWidget* create_entry(const gchar *entry_label) {
    GtkWidget *entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), entry_label);

    GtkStyleContext *entry_provider = gtk_widget_get_style_context(entry_name);
    gtk_style_context_add_class(entry_provider, "entry");

    return entry_name;
}

GtkWidget* create_button(const gchar *button_label) {
    GtkWidget *button = gtk_button_new_with_label(button_label);
        
    GtkStyleContext *button_provider = gtk_widget_get_style_context(button);
    gtk_style_context_add_class(button_provider, "button");

    return button;
}

GtkWidget* create_link_button(const gchar *li_label){
    GtkWidget *link_button = gtk_link_button_new_with_label("about:blank", li_label);
            
    GtkStyleContext *link_provider = gtk_widget_get_style_context(link_button);
    gtk_style_context_add_class(link_provider, "passwort-style");

    return link_button;
}

/**
 * This function open a dialog window with a 
 * define message.
*/
void show_warning_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
        "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
