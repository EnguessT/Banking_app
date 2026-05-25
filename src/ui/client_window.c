#include "../../include/client_window.h"
#include "widgets.h"
#include "buttons_callback.h"

/**
 * This function opens Client window after 
 * login was successful
 */
void open_client_window(GtkWidget *button, gpointer user_data) {
    // Get the parent window from the button
    (void)user_data;
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_toplevel(button));
    GtkApplication *app =
        GTK_APPLICATION(gtk_window_get_application(parent));

    GtkWidget *user_window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(user_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(user_window), FALSE);
    gtk_window_set_title(GTK_WINDOW(user_window), "Bank Account");
    gtk_container_set_border_width(GTK_CONTAINER(user_window), 10);
    gtk_window_set_default_size(GTK_WINDOW(user_window), 800, 500);

    //Create a Header
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Bank Account");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(user_window), header);

    // Add elemens to header
    GtkWidget *logout_button = create_header_icon_button("images/logout.png", 20);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), logout_button);

    GtkWidget *msg_button = create_header_icon_button("images/message.png", 20);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), msg_button);

    GtkWidget *filter_button = create_header_icon_button("images/filter.png", 20);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), filter_button);

    g_signal_connect(G_OBJECT(logout_button), "clicked", 
        G_CALLBACK(on_logout_clicked), NULL);


    //Create a main box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_style_context_add_class(gtk_widget_get_style_context(main_box), "main-box");
    gtk_container_add(GTK_CONTAINER(user_window), main_box);

    // create a box container
    GtkWidget* side_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(side_box, 220, -1); 
    gtk_box_pack_start(GTK_BOX(main_box), side_box, FALSE, FALSE, 0);
        

    // create a box container
    GtkWidget* head_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *profile_image = set_image("images/profile.png", 50, 50);
    const gchar *n_label = "<b><span foreground=\"black\" size=\'x-large\'>User Name</span></b>";
    GtkWidget *name_label = set_label(n_label);

    gtk_box_pack_start(GTK_BOX(head_box), profile_image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(head_box), name_label, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(side_box), head_box, FALSE, FALSE, 0);
    // Separator
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(side_box), separator, FALSE, FALSE, 5);

    // Create sidebar
    GtkWidget* sidebar = gtk_stack_sidebar_new();

    //Create a stack sidebar
    GtkWidget* stack = user_stack();

    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));
    gtk_box_pack_start(GTK_BOX(side_box), sidebar, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(main_box), stack, TRUE, TRUE, 0);

    gtk_widget_show_all(user_window);

}

GtkWidget* user_stack() {
    GtkWidget *stack = g_object_new(
        GTK_TYPE_STACK,
        "visible", TRUE,
        "transition-type", GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT,
        NULL
    );

     // DASHBOARD PAGE
    GtkWidget *dashboard = create_stack_page("images/wallet.png", "Dashboard");
    gtk_stack_add_titled(GTK_STACK(stack), dashboard, "Dashboard", "Dashboard");

    // PAYMENTS PAGE
    GtkWidget *payments = create_stack_page("images/transfert.png", "Payments");
    gtk_stack_add_titled(GTK_STACK(stack), payments, "Payments", "Payments");

    // TRANSACTIONS PAGE
    GtkWidget *transactions = create_stack_page("images/payhistory.png", "Transactions");
    gtk_stack_add_titled(GTK_STACK(stack), transactions, "Transactions", "Transactions");

    // Card page
    GtkWidget *cards = create_stack_page("images/cards.png", "Cards");;
    gtk_stack_add_titled(GTK_STACK(stack), cards, "Cards", "Cards");

    // SETTINGS PAGE
    GtkWidget *settings = create_stack_page("images/settings.png", "Settings");;
    gtk_stack_add_titled(GTK_STACK(stack), settings, "Settings", "Settings");

    return stack;
}
