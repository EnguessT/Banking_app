#include "database_context.h"
#include "bcrypt.h"


/**
 * This function create a database to store all users's datas
 */
int create_user_table() {
    sqlite3 *db;
    const char* user_db = "databases/users.db";
    if (sqlite3_open(user_db, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s: %s\n", user_db,sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS Users ("
                       "User_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "Role TEXT NOT NULL DEFAULT 'Client',"
                       "Username TEXT NOT NULL COLLATE NOCASE,"
                       "Password TEXT NOT NULL,"
                       "Birth_date TEXT,"
                       "Email TEXT UNIQUE NOT NULL COLLATE NOCASE,"
                       "City TEXT ,"
                       "Street TEXT,"
                       "House_number TEXT,"
                       "Zipcode TEXT,"
                       "Balance DOUBLE DEFAULT 0.0,"
                       "Created_at TEXT DEFAULT CURRENT_TIMESTAMP);";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 

    //sqlite3_close(db);

    return EXIT_SUCCESS;
}


/**
 * This function encrypts the user passwort using the bcrypt.h
 * function for hashing and slating and returns the
 * hashed passwort to store in the database
 */
char* encrypt_passwort(const char* passwort) {
    char salt[BCRYPT_HASHSIZE];
    char* hash = malloc(BCRYPT_HASHSIZE);
    if (!hash) {
        free(hash);
        return NULL;
    } 

    bcrypt_gensalt(12, salt);
    if (bcrypt_hashpw(passwort, salt, hash) != 0) return NULL;

    return hash;  
}


/**
 * This function adds a user in the database and insert his datas
 */
sqlite3_int64 add_user(sqlite3 *db, RegistrationContext *user) {

    const char *sql_insert = "INSERT INTO Users "
                         "(Role, Username, Password, Birth_date,"
                         "Email, City, Street, House_number, Zipcode, Balance) "
                         "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
                         
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    // Generate user ID
    sqlite3_stmt *id_stmt;
    if (sqlite3_prepare_v2(db, "SELECT MAX(User_ID) FROM Users;", -1, &id_stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare ID query: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_step(id_stmt);
    sqlite3_int64 max_id = sqlite3_column_int64(id_stmt, 0);
    sqlite3_finalize(id_stmt);

    char User_ID[32];
    snprintf(User_ID, sizeof(User_ID), "CUST%08lld", max_id + 1);

    // Extract text from entries
    const gchar *name     = gtk_entry_get_text(GTK_ENTRY(user->name_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(user->password_entry));
    char *hash_password = encrypt_passwort(password);
    if(!hash_password) {
        fprintf(stderr, "Password hashing failed.\n");
        return EXIT_FAILURE;
    }
    const gchar *birth    = gtk_entry_get_text(GTK_ENTRY(user->birth_entry));
    const gchar *email    = gtk_entry_get_text(GTK_ENTRY(user->email_entry));
    const gchar *city     = gtk_entry_get_text(GTK_ENTRY(user->city_entry));
    const gchar *street   = gtk_entry_get_text(GTK_ENTRY(user->street_entry));
    const gchar *house    = gtk_entry_get_text(GTK_ENTRY(user->house_entry));
    const gchar *zip      = gtk_entry_get_text(GTK_ENTRY(user->zip_entry));

    sqlite3_bind_text(stmt, 1, "Client", -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, hash_password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, birth, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, city, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, street, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, house, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, zip, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 10, 0.0);  // Initial balance

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Insert failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return EXIT_FAILURE;
    }

    sqlite3_finalize(stmt);
    sqlite3_int64 new_user_id = sqlite3_last_insert_rowid(db);
    free(hash_password);

    return new_user_id;
}


/**
 * This function create a database to keep track
 * of user operations
 */
int operation_made() {
    sqlite3 *db;
    const char* operation_db = "databases/operations.db";
    if (sqlite3_open(operation_db, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s : %s\n", operation_db,sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS Operations ("
                      "Operation_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "User_id INTEGER NOT NULL,"                    
                      "Type TEXT NOT NULL,"                          
                      "Amount DOUBLE NOT NULL,"
                      "Timestamp TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "Description TEXT,"
                      "FOREIGN KEY(user_id) REFERENCES users(ID));";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 

    sqlite3_close(db);

    return EXIT_SUCCESS;
}


/**
 * This function insert user operations in 
 * the operation database
 */
int log_operation(sqlite3 *db, sqlite3_int64 user_id, OperationType type, double amount) {
    const char *sql = "INSERT INTO operations (User_id, Type, Amount, Description) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    const char *op_descriptions[] = {
        "New user registered",
        "User logged in",
        "User made a deposit",
        "User made a withdraw",
        "User made a transfer",
        "User updated their profile",
        "Admin checked database",
        "User Logged out"
    };

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare operation log: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *type_str = NULL;
    switch (type) {
        case REGISTRATION:      type_str = "registration"; break;
        case LOGIN:             type_str = "login"; break;
        case DEPOSIT:           type_str = "deposit"; break;
        case WITHDRAW:          type_str = "withdraw"; break;
        case TRANSFERT:         type_str = "transfert"; break;
        case PROFILE_UPDATE:    type_str = "profile_update"; break;
        case DATABASE_CHECKING: type_str = "database_checking"; break;
        case LOGOUT:            type_str = "logout"; break;
        default:                type_str = "unknown"; break;
    }

    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, type_str, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, amount);
    sqlite3_bind_text(stmt, 4, op_descriptions[type], -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? 0 : 1;
}