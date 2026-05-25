#include "../../include/buttons_callback.h"
#include "widgets.h"
#include "verifications.h"
#include "admin_window.h"
#include "client_window.h"
#include "database_context.h"
#include "registration.h"
#include "main_window.h"

/**
 * THis function is called when the link for password forgot 
 * is clicked, it created a window for initialising 
 * the user passwort
 */
gboolean on_link_clicked(GtkLinkButton *button, gpointer user_data) {

    (void)button;
    (void) user_data;
    show_warning_dialog("Password recovery coming soon!");
    return TRUE; 
}


//extract the text and call your open_connect_window():
void on_login_clicked(GtkWidget *button, gpointer user_data) {
    LoginContext *ctx = (LoginContext *)user_data;

    const gchar *identifier = gtk_entry_get_text(GTK_ENTRY(ctx->user_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(ctx->password_entry));


    if (g_strcmp0(identifier, "") == 0 || g_strcmp0(password, "") == 0) {
        show_warning_dialog("Please enter User_ID/Email and password.");
         return;
    }
    AuthResult auth;
    int auth_result = authenticate_user(identifier, password, &auth);
    if(auth_result == 1) {
        if(strcmp(auth.role,"Admin") == 0) {
            GtkWindow *parent = GTK_WINDOW(gtk_widget_get_toplevel(button));
            gtk_window_close(parent);
            open_admin_window(button, NULL);
            //log the operation
            sqlite3 *db_operation;
            if (sqlite3_open("databases/operations.db", &db_operation) != SQLITE_OK) {
                fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_operation));
                return;
            }
    
            log_operation(db_operation, auth.id, 1, 0.0);

        } else if(strcmp(auth.role, "Client") == 0) {
            GtkWindow *parent = GTK_WINDOW(gtk_widget_get_toplevel(button));
            gtk_window_close(parent);
            open_client_window(button, NULL);
              //log the operation
            sqlite3 *db_operation;
            if (sqlite3_open("databases/operations.db", &db_operation) != SQLITE_OK) {
                fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_operation));
                return;
            }
    
            log_operation(db_operation, auth.id, 1, 0.0);

        } else {
            show_warning_dialog("Unknown role. Access denied.");
        }

    } else if(auth_result == 0) {
        show_warning_dialog("Incorrect password.");
    } else {
        show_warning_dialog("Login failed. PLease try again");
    }

    //g_free(ctx);  // When done with ctx and not using it again
}


/**
 * This function is called when the user click on 
 * button create in the registration window
 * it takes the user input datas and proceed with 
 * inputs validation checking.
 */
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
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(rtx->password_entry));
    const gchar *re_password = gtk_entry_get_text(GTK_ENTRY(rtx->re_password_entry));

    if (g_strcmp0(name, "") == 0 || g_strcmp0(birth, "") == 0 || g_strcmp0(email, "") == 0 ||
        g_strcmp0(phone_number, "") == 0 ||g_strcmp0(city, "") == 0 ||g_strcmp0(street, "") == 0 ||
        g_strcmp0(house_number, "") == 0 ||g_strcmp0(zipcode, "") == 0 ||
        g_strcmp0(password, "") == 0 || g_strcmp0(re_password, "") == 0) 
    {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
            "Please enter all the informations.");

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        return;
    }

    //validation username
    const char *name_pattern = "^[A-Za-zÀ-ÿ' -]+$";
    const char *name_warning = "Names have only letters, and characters: ' - and space.";
    is_valid_operation(name, name_pattern, name_warning);

    //validation date of birth
    is_valid_birthdate(birth);
   
    //valiadation email address
    const char *email_pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    const char *email_warning = "Your email address is invalid";
    is_valid_operation(email, email_pattern, email_warning);

    //valiadation phone number
    const char *phone_pattern = "^[0-9]{12}$";
    const char *phone_warning = "Phone number is a 12 digits and no letters or specials characters.";
    is_valid_operation(phone_number, phone_pattern, phone_warning);

    //valiadation city
    const char *city_pattern = "^[A-Za-zÀ-ÿ' -]+$";
    const char *city_warning = "City have only letters, and characters: ' - and space.";
    is_valid_operation(city, city_pattern, city_warning);

    //validation street
    const char *street_pattern = "^[A-Za-zÀ-ÿ' -]+$";
    const char *street_warning = "Street have only letters and characters: ' - and space";
    is_valid_operation(street, street_pattern, street_warning);

    //validation house number
    const char *house_pattern = "^[0-9]{1,4}$";
    const char *house_warning = "House number muss have at least 1 digit and 3 digits maximum";
    is_valid_operation(house_number, house_pattern, house_warning);

    //validation zip code
    const char *zip_pattern = "^[0-9]{5}$";
    const char *zip_warning = "Zipcode muss be a 5 digits";
    is_valid_operation(zipcode, zip_pattern, zip_warning);

    //validation passwort
    const char *password_pattern = "^(?=.*[A-Z])(?=.*[0-9])(?=.*[ \\-_*+=@#\\/?!%$€]).{8,}$";
    const char *password_warning = "Passwort muss have at least 8 characters, have letters, digits, and "
                             "special characters !+=?.,*-_/%$@";

    is_valid_operation(password, password_pattern, password_warning);

    //validation re_passwort
    if (g_strcmp0(password, re_password) != 0) {
        // Strings are different
        show_warning_dialog("The two passworts do not match.");
        return;
    } 

    //create the Users database
    create_user_table();

    open_create_account(name, birth, email, phone_number, city, street, house_number, 
        zipcode, password);  

    //open the User database
    sqlite3 *db_user;
    if (sqlite3_open("databases/users.db", &db_user) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_user));
        return;
    }

    //insert user datas in the database and retrieve user ID
    sqlite3_int64 new_user_id = add_user(db_user, rtx);
    if (new_user_id == -1) {
        show_warning_dialog("Failed to create account. Please try Again.");
        sqlite3_close(db_user); 
        return;
    }
    

    //show a dialog window for account creation success
    show_warning_dialog("Account created successfully!");

    //transmit the user his User_ID
    char Id_buffer[200];
    sprintf(Id_buffer, "Your user ID is: CUST%08lld\nPlease keep it carefully.\n You need it to login.",
                        new_user_id);
    show_warning_dialog(Id_buffer);

    //Zero out passwort from memory
    for(size_t i = 0; password[i] != '\0'; ++i) {
        ((volatile char*)password)[i] = 0;
    }
 
    // create the operation database
    operation_made();

    //log the operation
    sqlite3 *db_operation;
    if (sqlite3_open("databases/operations.db", &db_operation) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_operation));
        sqlite3_close(db_user);
        return;
    }
    
    log_operation(db_operation, new_user_id, 0, 0.0);

    //close the databases
    sqlite3_close(db_user);
    sqlite3_close(db_operation);

    GtkWidget *window = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(window);

    g_free(rtx); 
}

void on_logout_clicked(GtkWidget *button, gpointer user_data) {
    (void)user_data;
    GtkWindow *window = GTK_WINDOW(gtk_widget_get_toplevel(button));
    GtkApplication *app =
        GTK_APPLICATION(gtk_window_get_application(window));

    // Close the window
    gtk_window_close(window);

    // Reopen the Main window
    create_main_window(app);
}