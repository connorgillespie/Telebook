/*
	Connor Gillespie
	3/22/2024
	ITT-310
*/

#include <stdbool.h>

#ifndef USERS_H
#define USERS_H

#define MAX_USERS 64
#define USERNAME_MAX_LENGTH 129  // 128 Characters Used, 129 Required to Fit Null Terminator "\0"
#define PHONE_MAX_LENGTH 11  // 10 Characters Used, 11 Required to Fit Null Terminator "\0"
#define CONTACTS_MAX_LENGTH 16
#define FILENAME "users.data"

#endif /* USERS_H */

unsigned long hash(const char* str);
bool store_to_file();
bool load_from_file();
bool verify_username_exists(const char* username);
bool verify_contact_already_saved(const char* username, const char* contact);
bool validate_credentials(const char* username, const char* password);
char* get_phone_by_username(const char* username);
bool add_user(const char username[USERNAME_MAX_LENGTH], unsigned long password, const char phone[PHONE_MAX_LENGTH], const char contacts[USERNAME_MAX_LENGTH][CONTACTS_MAX_LENGTH], int length_of_contacts);
bool remove_user(const char* username);
bool add_contact_to_user(const char* username, const char* contact);
bool remove_contact_from_user(const char* username, const char* contact);
void list_users();
void list_saved_contacts(const char* username);
