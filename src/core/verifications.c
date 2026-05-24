#include "../../include/verifications.h"
#include "widgets.h"
#include "bcrypt.h"

/***
 * This function check if the user entry are valid
 * by comparing the user inputs here input 
 * to some pattern here re_expression using regular expressions 
 * if pattern doesn't match open a dialog window
 */
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


/**
 * This function check if the entered user birthdate here input
 * is valid and  follow the format dd/MM/YYYY or dd.MM.YYYY
 * if not open a dialog window.
 */
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


/**
 * This function proceed with the authentification
 * taking the User_ID or Email and Password
 * and checking if it is found in the database
 */
int authenticate_user(const char* identifier, const char* password_input, AuthResult *output) {
    sqlite3 *db_user;
    if (sqlite3_open("databases/users.db", &db_user) != SQLITE_OK) {
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
