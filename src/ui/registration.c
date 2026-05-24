#include "../../include/registration.h"
#include "../../include/buttons_callback.h"
#include "widgets.h"

/**
 * This function is called to create the user account
 * after the inputs validation are all correct
 */
void open_create_account(const gchar* name, const gchar* birth, const gchar* mail,
                const gchar* phone, const gchar* city, const gchar* street,
                const gchar* house, const gchar* zip, const gchar* password) 
{
    char buffer[200];
    printf("Account create\n");
    printf("name: %s\n", name);
    printf("birthday: %s\n", birth);
    printf("email: %s\n", mail);
    printf("phone number: %s\n", phone);
    sprintf(buffer, "%s %s, %s %s", street,house,zip, city);
    printf("Address is: %s\n", buffer);
    printf("Passwort: %s\n", password);
}


/**
 * This function is called to create the registration window
 */
void open_registration_window(GtkWidget *button, gpointer data) {
    (void)button;
    GtkApplication *app = GTK_APPLICATION(data);
    GtkWidget *register_window = gtk_application_window_new(app);
	gtk_window_set_position(GTK_WINDOW(register_window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(register_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(register_window), "Registration");
	gtk_container_set_border_width(GTK_CONTAINER(register_window), 10);
	gtk_window_set_default_size(GTK_WINDOW(register_window), 400, 700);

    // Main vertical box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_style_context_add_class(gtk_widget_get_style_context(main_box), "main-box");
    gtk_container_add(GTK_CONTAINER(register_window), main_box);

    // User icon
    GtkWidget *user_icon = set_image("images/profile.png", 80, 80);
    gtk_box_pack_start(GTK_BOX(main_box), user_icon, FALSE, FALSE, 0);

    // Title label
    GtkWidget *title = set_label("MEMBER REGISTRATION");
    gtk_style_context_add_class(gtk_widget_get_style_context(title), "title");
    gtk_box_pack_start(GTK_BOX(main_box), title, FALSE, FALSE, 0);

    // Username entry
    GtkWidget *name_entry  = create_entry("Username");
    gtk_style_context_add_class(gtk_widget_get_style_context(name_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), name_entry, FALSE, FALSE, 0);

    // date of birth entry
    GtkWidget *birth_entry  = create_entry( "date of birth  dd/MM/YYYY");
    gtk_style_context_add_class(gtk_widget_get_style_context(birth_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), birth_entry, FALSE, FALSE, 0);

    // mail entry
    GtkWidget *mail_entry = create_entry("Email");
    gtk_style_context_add_class(gtk_widget_get_style_context(mail_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), mail_entry, FALSE, FALSE, 0);

    // phone number entry
    GtkWidget *number_entry = create_entry("Phone number");
    gtk_style_context_add_class(gtk_widget_get_style_context(number_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), number_entry, FALSE, FALSE, 0);

    // city entry
    GtkWidget *city_entry = create_entry("City");
    gtk_style_context_add_class(gtk_widget_get_style_context(city_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), city_entry, FALSE, FALSE, 0);

    // street entry
    GtkWidget *street_entry = create_entry("Street");
    gtk_style_context_add_class(gtk_widget_get_style_context(street_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), street_entry, FALSE, FALSE, 0);

    // house number entry
    GtkWidget *house_entry = create_entry("House number");
    gtk_style_context_add_class(gtk_widget_get_style_context(house_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), house_entry, FALSE, FALSE, 0);

    // Zipcode entry
    GtkWidget *zip_entry = create_entry("Zipcode");
    gtk_style_context_add_class(gtk_widget_get_style_context(zip_entry), "entry");
    gtk_box_pack_start(GTK_BOX(main_box), zip_entry, FALSE, FALSE, 0);

    //Password entry
    GtkWidget *password_entry = create_entry("Password");
    gtk_style_context_add_class(gtk_widget_get_style_context(password_entry), "entry");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(main_box), password_entry, FALSE, FALSE, 0);

    //reenter Password entry
    GtkWidget *re_password_entry = create_entry("Password Again");
    gtk_style_context_add_class(gtk_widget_get_style_context(password_entry), "entry");
    gtk_entry_set_visibility(GTK_ENTRY(re_password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(main_box), re_password_entry, FALSE, FALSE, 0);
    
    RegistrationContext *rtx = g_new(RegistrationContext, 1);
    rtx->name_entry = name_entry;
    rtx->birth_entry = birth_entry;
    rtx->email_entry = mail_entry;
    rtx->phone_entry = number_entry;
    rtx->city_entry = city_entry;
    rtx->street_entry = street_entry;
    rtx->house_entry = house_entry;
    rtx->zip_entry = zip_entry;
    rtx->password_entry = password_entry;
    rtx->re_password_entry = re_password_entry;

    // create button
    GtkWidget *create_button = gtk_button_new_with_label("CREATE");
    gtk_style_context_add_class(gtk_widget_get_style_context(create_button), "create-button");
    gtk_box_pack_start(GTK_BOX(main_box), create_button, FALSE, FALSE, 0);
    g_signal_connect(create_button, "clicked", G_CALLBACK(on_create_clicked), rtx);


    gtk_widget_show_all(register_window);


}