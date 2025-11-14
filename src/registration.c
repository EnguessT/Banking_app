#include "registration.h"

void open_create_account(const gchar* name, const gchar* birth, const gchar* mail,
                const gchar* phone, const gchar* city, const gchar* street,
                const gchar* house, const gchar* zip,
                const gchar* ID, const gchar* password) 
{
    char buffer[200];
    printf("Account create\n");
    printf("name: %s\n", name);
    printf("birthday: %s\n", birth);
    printf("email: %s\n", mail);
    printf("phone number: %s\n", phone);
    sprintf(buffer, "%s %s, %s %s", street,house,zip, city);
    printf("Address is: %s\n", buffer);
    printf("ID: %s\n", ID);
    printf("Passwort: %s\n", password);
}

void on_create_clicked(GtkWidget *button, gpointer user_infos) {
    RegistrationContext *rtx = (RegistrationContext *)user_infos;

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(rtx->name_entry));
    const gchar *birth = gtk_entry_get_text(GTK_ENTRY(rtx->birth_entry));
    const gchar *email = gtk_entry_get_text(GTK_ENTRY(rtx->email_entry));
    const gchar *phone_number = gtk_entry_get_text(GTK_ENTRY(rtx->phone_entry));
    const gchar *city = gtk_entry_get_text(GTK_ENTRY(rtx->city_entry));
    const gchar *street = gtk_entry_get_text(GTK_ENTRY(rtx->street_entry));
    const gchar *house_number = gtk_entry_get_text(GTK_ENTRY(rtx->house_entry));
    const gchar *zipcode = gtk_entry_get_text(GTK_ENTRY(rtx->zip_entry));
    const gchar *user_id = gtk_entry_get_text(GTK_ENTRY(rtx->id_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(rtx->password_entry));

    if (g_strcmp0(name, "") == 0 || g_strcmp0(birth, "") == 0 || g_strcmp0(email, "") == 0 ||
        g_strcmp0(phone_number, "") == 0 ||g_strcmp0(city, "") == 0 ||g_strcmp0(street, "") == 0 ||
        g_strcmp0(house_number, "") == 0 ||g_strcmp0(zipcode, "") == 0 ||
        g_strcmp0(user_id, "") == 0 || g_strcmp0(password, "") == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
            "Please enter all the informations.");

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        return;
    }

    open_create_account(name, birth, email, phone_number, city, street, house_number, 
        zipcode, user_id, password);  
    //g_free(rtx);  // Only if you're done with it and not using it again
}

void open_signup_window(void) {

    GtkWidget *register_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(register_window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(register_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(register_window), "Registration");
	gtk_container_set_border_width(GTK_CONTAINER(register_window), 10);
	gtk_window_set_default_size(GTK_WINDOW(register_window), 400, 700);


    g_signal_connect(register_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(register_window);
	gtk_main();

}