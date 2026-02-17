#include"include/main_window.h"
#include "include/widgets.h"
#include "include/registration.h"
#include <sqlite3.h>
#include <string.h>
#include <bcrypt.h>


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

/**
 * This function proceed with the authentification
 * taking the User_ID or Email and Password
 * and checking if it is found in the database
 */
int authenticate_user(const char* identifier, const char* password_input, AuthResult *output) {
    sqlite3 *db_user;
    if (sqlite3_open("users.db", &db_user) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_user));
        return -1;
    }

    const char *sql = "SELECT User_ID, Password, Role "
                      "FROM Users WHERE User_ID = ? OR Email = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_user, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db_user));
        sqlite3_finalize(stmt);
        sqlite3_close(db_user);
        return -1;
    }

    // Bind the same identifier to both fields, 4
    long long numeric_id = -1;
    if (strncmp(identifier, "CUST", 4) == 0) {
        char *endptr;
        numeric_id = strtoll(identifier + 4, &endptr, 10);

        if (*endptr == '\0') {
            sqlite3_bind_int64(stmt, 1, numeric_id);
        } else {
            sqlite3_bind_null(stmt, 1);
        }
    } else {
        sqlite3_bind_null(stmt, 1);
    }

    sqlite3_bind_text(stmt, 2, identifier, -1, SQLITE_STATIC);

    int result = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_int64 user_id = sqlite3_column_int64(stmt, 0);
        //const char *user_id     = (const char *)sqlite3_column_text(stmt, 1);
        const char *stored_hash = (const char *)sqlite3_column_text(stmt, 1);
        const char *role        = (const char *)sqlite3_column_text(stmt, 2);

         if (bcrypt_checkpw(password_input, stored_hash) == 0) {
            //login successful
            output->id = user_id;
            char cust_id[32];
            snprintf(cust_id, sizeof(cust_id), "CUST%08lld", user_id);
            strncpy(output->user_id, cust_id, sizeof(output->user_id));
            strncpy(output->role, role, sizeof(output->role));
            result = 1;
         } else {
            //wrong passord
            result = 0;
         }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db_user);
    return result;
}

//extract the text and call your open_connect_window():
void on_login_clicked(GtkWidget *button, gpointer user_data) {
    (void) button;
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
            open_admin_window();
            //log the operation
            sqlite3 *db_operation;
            if (sqlite3_open("operations.db", &db_operation) != SQLITE_OK) {
                fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_operation));
                return;
            }
    
            log_operation(db_operation, auth.id, 2, 0.0);

        } else if(strcmp(auth.role, "Client") == 0) {
            open_client_window();
              //log the operation
            sqlite3 *db_operation;
            if (sqlite3_open("operations.db", &db_operation) != SQLITE_OK) {
                fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_operation));
                return;
            }
    
            log_operation(db_operation, auth.id, 2, 0.0);

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
 * This function opens Client window after 
 * login was successful
 */
void open_client_window(void) {
    GtkWidget *user_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(user_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(user_window), FALSE);
    gtk_window_set_title(GTK_WINDOW(user_window), "Bank Account");
    gtk_container_set_border_width(GTK_CONTAINER(user_window), 10);

    gtk_window_set_default_size(GTK_WINDOW(user_window), 800, 500);
    g_signal_connect(user_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(user_window);

	gtk_main();
}

/**
 * This function opens a Admin window after 
 * login was successful and role Admin was proved
 */
void  open_admin_window() {

}

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
    g_signal_connect(create, "clicked", G_CALLBACK(open_signup_window), NULL);

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