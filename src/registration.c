#include "registration.h"
#include <regex.h>

void is_valid_operation(const gchar* input, const char *re_expression, const char *dialog_message) {
    regex_t regex;
    int n_reti = regcomp(&regex, re_expression, REG_EXTENDED);
    if (n_reti != 0) {
        fprintf(stderr, "Regex compilation failed.\n");
        return;
    }

    // Show dialog only if the input does NOT match the pattern
    n_reti = regexec(&regex, input, 0, NULL, 0);
    if (n_reti != 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
            "%s", dialog_message);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    regfree(&regex);
}

void show_warning_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
        "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

bool is_valid_birthdate(const gchar* input) {
    regex_t regex;
    const char *pattern = "^([0-9]{2}/[0-9]{2}/[0-9]{4}|[0-9]{2}\\.[0-9]{2}\\.[0-9]{4})$";
    const char *birth_warning = "Date of birth should be in format dd/MM/YYYY or dd.MM.YYYY";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Regex compilation failed for pattern: %s\n", pattern);
        return false;
    }

    int match = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    if (match != 0) {
        show_warning_dialog(birth_warning);
        return false;
    }

    char normalized[16];
    strncpy(normalized, input, sizeof(normalized));
    normalized[sizeof(normalized) - 1] = '\0';
    for (int i = 0; normalized[i]; i++) {
        if (normalized[i] == '.') normalized[i] = '/';
    }

    int day, month, year;
    if (sscanf(normalized, "%2d/%2d/%4d", &day, &month, &year) != 3) {
        return false;
    }

    int days_in_month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    const char *semantic_warning = "Date of birth is not a valid calendar date.";

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (year < 1900 || year > 2100 || month < 1 || month > 12 ||
        day < 1 || day > days_in_month[month - 1]) {
        show_warning_dialog(semantic_warning);
        return false;
    }

    return true;
}


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
    const gchar *re_password = gtk_entry_get_text(GTK_ENTRY(rtx->re_password_entry));

    if (g_strcmp0(name, "") == 0 || g_strcmp0(birth, "") == 0 || g_strcmp0(email, "") == 0 ||
        g_strcmp0(phone_number, "") == 0 ||g_strcmp0(city, "") == 0 ||g_strcmp0(street, "") == 0 ||
        g_strcmp0(house_number, "") == 0 ||g_strcmp0(zipcode, "") == 0 ||
        g_strcmp0(user_id, "") == 0 || g_strcmp0(password, "") == 0 || g_strcmp0(re_password, "") == 0) 
    {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
            "Please enter all the informations.");

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        return;
    }

    //valiadation username
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
    is_valid_operation(name, phone_pattern, phone_warning);

    //valiadation city
    const char *city_pattern = "^[A-Za-zÀ-ÿ' -]+$";
    const char *city_warning = "City have only letters, and characters: ' - and space.";
    is_valid_operation(name, city_pattern, city_warning);

    //validation street
    const char *street_pattern = "^[A-Za-zÀ-ÿ' -]+$";
    const char *street_warning = "Street have only letters and characters: ' - and space";
    is_valid_operation(name, street_pattern, street_warning);

    //validation house number
    const char *house_pattern = "^[0-9]{1,4}$";
    const char *house_warning = "House number muss have at least 1 digit and 3 digits maximum";
    is_valid_operation(name, house_pattern, house_warning);

    //validation zip code
    const char *zip_pattern = "^[0-9]{5}$";
    const char *zip_warning = "Zipcode muss be a 5 digits";
    is_valid_operation(name, zip_pattern, zip_warning);

    //validation user ID
    const char *id_pattern = "^[a-zA-Z0-9_-À-ÿ' -]{6,}$";
    const char *id_warning = "User ID muss have only letters and digits";
    is_valid_operation(name, id_pattern, id_warning);

    //validation passwort
    const char *password_pattern = "^(?=.*[A-Z])(?=.*[0-9])(?=.*[ \\-_*+=@#\\/?!%$€]).{8,}$";
    const char *password_warning = "Passwort muss have at least 8 characters, have letters, digits, and "
                             "special characters !+=?.,*-_/%$@";

    is_valid_operation(name, password_pattern, password_warning);

    //validation re_passwort
    if (g_strcmp0(password, re_password) == 0) {
    // Strings are equal
    } else {
        // Strings are different
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
            "The two passworts do not match.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
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

    // Main vertical box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_name(main_box, "main-box");
    gtk_container_add(GTK_CONTAINER(register_window), main_box);

    // User icon
    GtkWidget *user_icon = set_image("images/profile.png", 80, 80);
    gtk_box_pack_start(GTK_BOX(main_box), user_icon, FALSE, FALSE, 0);

    // Title label
    GtkWidget *title = set_label("MEMBER REGISTRATION");
    gtk_widget_set_name(title, "title");
    gtk_box_pack_start(GTK_BOX(main_box), title, FALSE, FALSE, 0);

    // Username entry
    GtkWidget *name_entry  = create_entry("Username");
    gtk_widget_set_name(name_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), name_entry, FALSE, FALSE, 0);

    // date of birth entry
    GtkWidget *birth_entry  = create_entry( "date of birth  dd/MM/YYYY");
    gtk_widget_set_name(birth_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), birth_entry, FALSE, FALSE, 0);

    // mail entry
    GtkWidget *mail_entry = create_entry("Email");
    gtk_widget_set_name(mail_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), mail_entry, FALSE, FALSE, 0);

    // phone number entry
    GtkWidget *number_entry = create_entry("Phone number");
    gtk_widget_set_name(number_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), number_entry, FALSE, FALSE, 0);

    // city entry
    GtkWidget *city_entry = create_entry("City");
    gtk_widget_set_name(city_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), city_entry, FALSE, FALSE, 0);

    // street entry
    GtkWidget *street_entry = create_entry("Street");
    gtk_widget_set_name(street_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), street_entry, FALSE, FALSE, 0);

    // house number entry
    GtkWidget *house_entry = create_entry("House number");
    gtk_widget_set_name(house_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), house_entry, FALSE, FALSE, 0);

    // Zipcode entry
    GtkWidget *zip_entry = create_entry("Zipcode");
    gtk_widget_set_name(zip_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), zip_entry, FALSE, FALSE, 0);

    // Id entry
    GtkWidget *id_entry = create_entry("User ID");
    gtk_entry_set_visibility(GTK_ENTRY(id_entry), FALSE);
    gtk_widget_set_name(id_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), id_entry, FALSE, FALSE, 0);

    //Password entry
    GtkWidget *password_entry = create_entry("Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_widget_set_name(password_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), password_entry, FALSE, FALSE, 0);

    //reenter Password entry
    GtkWidget *re_password_entry = create_entry("Password Again");
    gtk_entry_set_visibility(GTK_ENTRY(re_password_entry), FALSE);
    gtk_widget_set_name(re_password_entry, "entry");
    gtk_box_pack_start(GTK_BOX(main_box), re_password_entry, FALSE, FALSE, 0);
    
    RegistrationContext *rtx = g_new(RegistrationContext, 1);
    rtx->name_entry = name_entry;
    rtx->birth_entry = birth_entry;
    rtx->email_entry = city_entry;
    rtx->phone_entry = number_entry;
    rtx->city_entry = city_entry;
    rtx->street_entry = street_entry;
    rtx->house_entry = house_entry;
    rtx->zip_entry = zip_entry;
    rtx->id_entry = id_entry;
    rtx->password_entry = password_entry;
    rtx->re_password_entry = re_password_entry;

    // create button
    GtkWidget *create_button = gtk_button_new_with_label("CREATE");
    gtk_widget_set_name(create_button, "create-button");
    gtk_box_pack_start(GTK_BOX(main_box), create_button, FALSE, FALSE, 0);
    g_signal_connect(create_button, "clicked", G_CALLBACK(on_create_clicked), rtx);

    // CSS styling
    GtkCssProvider *css = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css,
        "#main-box {"
        " background-image: linear-gradient(to bottom right, #0165BD, #ffb88c);"
        " padding: 20px;"
        " border-radius: 15px;"
        " }"
        "#title {"
        " font-size: 20px;"
        " font-weight: bold;"
        " color: white;"
        " }"
        "#entry {"
        " background-color: white;"
        " border-radius: 10px;"
        " padding: 8px;"
        " border: 1px solid #ccc;"
        " }"
        "#create-button {"
        " background-color: #ffffff;"
        " color: #ff6f61;"
        " font-weight: bold;"
        " border-radius: 20px;"
        " padding: 10px 20px;"
        " border: none;"
        " }"
        "#create-button:hover {"
        " background-color: #ff6f61;"
        " color: white;"
        " }",
        -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(main_box);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_signal_connect(register_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(register_window);

	gtk_main();

}