#ifndef DATABASE_CONTEXT_H
#define DATABASE_CONTEXT_H

#include "types.h"



int create_user_table();
char* encrypt_passwort(const char* passwort);
sqlite3_int64 add_user(sqlite3 *db, RegistrationContext *user);
int operation_made();
int log_operation(sqlite3 *db, sqlite3_int64 user_id, OperationType type, double amount);


#endif



