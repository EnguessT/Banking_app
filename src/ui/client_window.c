#include "../../include/client_window.h"

/**
 * This function opens Client window after 
 * login was successful
 */
void open_client_window(GtkWidget* button, gpointer data) {
    (void)button;
    GtkWindow *parent = GTK_WINDOW(data);
    GtkApplication *app =
        GTK_APPLICATION(gtk_window_get_application(parent));

    GtkWidget *user_window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(user_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(user_window), FALSE);
    gtk_window_set_title(GTK_WINDOW(user_window), "Bank Account");
    gtk_container_set_border_width(GTK_CONTAINER(user_window), 10);

    gtk_window_set_default_size(GTK_WINDOW(user_window), 800, 500);

    //create parent box container
    GtkWidget *parent_box = gtk_box_new(0, 5);
	gtk_container_add(GTK_CONTAINER(user_window), parent_box);


    //Create a stack sidebar
    //GtkWidget* side_bar = gtk_stack_sidebar_new();
    GtkWidget* stack = user_stack();

    // Create sidebar
    GtkWidget* sidebar = g_object_new(
        GTK_TYPE_STACK_SIDEBAR,
        "visible", TRUE,
        "stack", stack,
        "halign", GTK_ALIGN_CENTER,
        NULL
    );

    // create a box container
    GtkWidget* box = g_object_new(
        GTK_TYPE_BOX,
        "visible", TRUE,
        "orientation", GTK_ORIENTATION_HORIZONTAL,
        "spacing", 10,
        "homogeneous", FALSE,
        NULL
    );

    gtk_box_pack_start(GTK_BOX(box), sidebar, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), stack, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(user_window), box);
    //gtk_window_set_titlebar(GTK_WINDOW(win), header);

    gtk_widget_show_all(user_window);

	gtk_main();
}


GtkWidget* user_stack() {
  GtkWidget *stack = g_object_new(
            GTK_TYPE_STACK,
            "visible", TRUE,
            "transition-type", GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT,
            NULL
  );

  const char* user_stack_label[4] = {"Dashboard", "Payments", "TRansactions", "settings"};

  for (int i = 0; i < 4; i++) {
    char label[56], title[7], name[6];

    sprintf(label, "<span size='xx-large' font_weight='bold'>%s</span>", user_stack_label[i]);
    sprintf(title, "%s", user_stack_label[i]);
    sprintf(name, "%s", user_stack_label[i]);

    gtk_stack_add_titled(
      GTK_STACK(stack),
      g_object_new(
        GTK_TYPE_LABEL,
        "visible", TRUE,
        "label", label,
        "use-markup", TRUE,
        NULL
      ),
      name,
      title
    );
  }

  return stack;
}