#include"../../include/widgets.h"

/**
 * @brief This function set an image as background color 
 * for container with css context
*/
void set_background_image(GtkWidget* lbox){
    GtkStyleContext *lprovider = gtk_widget_get_style_context(lbox);
    gtk_style_context_add_class(lprovider, "left-box");
    
}

/**
 * @brief This function set a background color for container
 * with css context
*/
void set_background_color(GtkWidget* rbox){
    GtkStyleContext *rprovider = gtk_widget_get_style_context(rbox);
    gtk_style_context_add_class(rprovider, "left-box");
}

/**
 * @brief This function creates a simple button
 * without css context
*/
GtkWidget* set_label(const gchar *label_markup) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_widget_set_margin_top(label, 5);

    gtk_label_set_markup(GTK_LABEL(label), label_markup);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE); 

    return label;
}

/**
 * @brief This function set an image in container
 * 
*/
GtkWidget* set_image(const char* filename, int width, int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, width, height, TRUE, NULL);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    gtk_widget_set_margin_top(image, 10);

    g_object_unref(pixbuf); 

    return image;
}

/**
 * @brief This function creates a label
 * with css context
*/
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

/**
 * @brief This function creates a entry box
 * with css context
*/
GtkWidget* create_entry(const gchar *entry_label) {
    GtkWidget *entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), entry_label);

    GtkStyleContext *entry_provider = gtk_widget_get_style_context(entry_name);
    gtk_style_context_add_class(entry_provider, "entry");

    return entry_name;
}


/**
 * @brief This function creates a simple button
 * with css context
*/
GtkWidget* create_button(const gchar *button_label) {
    GtkWidget *button = gtk_button_new_with_label(button_label);
        
    GtkStyleContext *button_provider = gtk_widget_get_style_context(button);
    gtk_style_context_add_class(button_provider, "button");

    return button;
}

/**
 * @brief This function creates a link button
 * 
*/
GtkWidget* create_link_button(const gchar *li_label){
    GtkWidget *link_button = gtk_link_button_new_with_label("about:blank", li_label);
            
    GtkStyleContext *link_provider = gtk_widget_get_style_context(link_button);
    gtk_style_context_add_class(link_provider, "passwort-style");

    return link_button;
}

/**
 * @brief This function open a dialog window with a 
 * define message.
*/
void show_warning_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
        "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/**
 * @brief This function create a header icon button
 */
GtkWidget* create_header_icon_button(const char *path, int size) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, size, size, TRUE, NULL);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

    GtkWidget *btn = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(btn), image);

    return btn;
}


/**
 * @brief This function create a button with label and image
 */
GtkWidget* create_button_with_icon(const char *path, const char* label) {
    GtkWidget *button = gtk_button_new_with_label(label);

    GtkWidget *icon = gtk_image_new_from_file(path);
    gtk_button_set_image(GTK_BUTTON(button), icon);

    // Ensure image + label both appear
    gtk_button_set_always_show_image(GTK_BUTTON(button), TRUE);
    return button;
}

/**
 * @brief This function create a stack page
 */
GtkWidget* create_stack_page(const char* img_path, const char* label) {
    GtkWidget *operation = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget *op_img = gtk_image_new_from_file(img_path);
    GtkWidget *op_title = gtk_label_new(NULL);
    char *markup = g_strdup_printf(
        "<span size='xx-large' weight='bold'>%s</span>",
        label
    );
    gtk_label_set_markup(GTK_LABEL(op_title), markup);
    g_free(markup);

    gtk_box_pack_start(GTK_BOX(operation), op_img, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(operation), op_title, FALSE, FALSE, 0);
    return operation;
}

/**
 * @brief This function creates a row widget with icon and label
 */
GtkWidget* create_sidebar_row(const char *icon_path, const char *text) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);

    GtkWidget *icon = gtk_image_new_from_file(icon_path);
    gtk_image_set_pixel_size(GTK_IMAGE(icon), 20);

    GtkWidget *label = gtk_label_new(text);
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    gtk_box_pack_start(GTK_BOX(box), icon, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    return box;
}
