/*
    Connor Gillespie
    3/22/2024
    ITT-310
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "users.h"
#include "menu.h"

typedef struct {
    char username[USERNAME_MAX_LENGTH];
    unsigned long password;
    char phone[PHONE_MAX_LENGTH];
    char contacts[USERNAME_MAX_LENGTH][CONTACTS_MAX_LENGTH];
    int length_of_contacts;
} USER;

USER users[MAX_USERS];
int length_of_users = 0;

// Hash Plaintext to Ciphertext: DJB2
unsigned long hash(const char* str) {
    /*
        WARNING: Do NOT use this hashing algorithm in a
        production environment! This hashing algorithm is
        extremely unsecure. This is STRICTLY to illustrate
        the understanding of hashing as a concept in the
        use of an application.
    */

    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

bool store_to_file() {
    FILE* file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return false;
    }

    // Write Number of Users to File
    fwrite(&length_of_users, sizeof(int), 1, file);

    // Write Each User to File
    for (int i = 0; i < length_of_users; i++) {
        fwrite(&users[i], sizeof(USER), 1, file);
    }

    fclose(file);
    return true;
}

bool load_from_file() {
    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return false;
    }

    // Read Number of Users From File
    fread(&length_of_users, sizeof(int), 1, file);

    // Read Each User From File
    for (int i = 0; i < length_of_users; i++) {
        fread(&users[i], sizeof(USER), 1, file);
    }

    fclose(file);
    return true;
}

bool verify_username_exists(const char* username) {
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

bool verify_contact_already_saved(const char* username, const char* contact) {
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = 0; j < users[i].length_of_contacts; j++) {
                if (strcmp(users[i].contacts[j], contact) == 0) {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

bool validate_credentials(const char* username, const char* password) {
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            // Check Saved Hashed Password Matches to Provided Password
            if (users[i].password == hash(password)) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

char* get_phone_by_username(const char* username) {
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return users[i].phone;
        }
    }
}

bool add_user(const char username[USERNAME_MAX_LENGTH], unsigned long password, const char phone[PHONE_MAX_LENGTH], const char contacts[USERNAME_MAX_LENGTH][CONTACTS_MAX_LENGTH], int length_of_contacts) {
    // Check Max Users Exceeded
    if (length_of_users >= MAX_USERS) {
        return false;
    }

    // Check If Username Already Exists
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return false;
        }
    }

    // Copy User to Next Available Slot in Memory
    strcpy(users[length_of_users].username, username);
    users[length_of_users].password = password;
    strcpy(users[length_of_users].phone, phone);
    for (int i = 0; i < length_of_contacts; i++) {
        strcpy(users[length_of_users].contacts[i], contacts[i]);
    }
    users[length_of_users].length_of_contacts = length_of_contacts;

    length_of_users++;  // Increment to Next Available User
    store_to_file();  // Update Data Files
    return true;
}

bool remove_user(const char* username) {
    // Determine Index of User
    int index = -1;
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            index = i;
            break;
        }
    }

    // User Not Found
    if (index == -1) {
        return false;
    }

    // Shift Elements After User Left 
    for (int i = index; i < length_of_users - 1; i++) {
        memcpy(&users[i], &users[i + 1], sizeof(USER));
    }

    length_of_users--;  // Decrement to Next Available User
    store_to_file();  // Update Data Files
    return true;
}

bool add_contact_to_user(const char* username, const char* contact) {
    // Find Index of User
    int user = -1;
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            user = i;
            break;
        }
    }

    // Check User Index
    if (user == -1) {
        return false;
    }

    // Check Max Contacts Not Exceeded
    if (users[user].length_of_contacts >= CONTACTS_MAX_LENGTH) {
        return false;
    }

    // Define Temporary User Variables
    unsigned long password;
    const char phone[PHONE_MAX_LENGTH];
    char contacts[USERNAME_MAX_LENGTH][CONTACTS_MAX_LENGTH];
    int length_of_contacts;

    // Copy Existing User to Temporary User
    password = users[user].password;
    strcpy(phone, users[user].phone);
    length_of_contacts = users[user].length_of_contacts;
    for (int i = 0; i < length_of_contacts; i++) {
        strcpy(contacts[i], users[user].contacts[i]);
    }

    // Copy New Contact to Temporary User
    strcpy(contacts[length_of_contacts], contact);
    length_of_contacts++;

    remove_user(username);  // Remove User
    add_user(username, password, phone, contacts, length_of_contacts);  // Add New User
}

bool remove_contact_from_user(const char* username, const char* contact) {
    // Find Index of User
    int user = -1;
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            user = i;
            break;
        }
    }

    // Check User Index
    if (user == -1) {
        return false;
    }

    // Check Contact is Saved
    if (verify_contact_already_saved(username, contact) == false) {
        return false;
    }

    // Define Temporary User Variables
    unsigned long password;
    const char phone[PHONE_MAX_LENGTH];
    char contacts[USERNAME_MAX_LENGTH][CONTACTS_MAX_LENGTH];
    int length_of_contacts;

    // Copy Existing User to Temporary User
    password = users[user].password;
    strcpy(phone, users[user].phone);
    length_of_contacts = users[user].length_of_contacts;
    for (int i = 0; i < length_of_contacts; i++) {
        // Do Not Copy Username if Equal to Contact
        if (strcmp(users[user].contacts[i], contact) == 1) {
            strcpy(contacts[i], users[user].contacts[i]);
        }
    }

    length_of_contacts--;  // Remove Exisiting Contact from Length of Contacts
    remove_user(username);  // Remove User
    add_user(username, password, phone, contacts, length_of_contacts);  // Add New User
}

void list_users(const char* divider) {
    system("cls");
    printf("%s%s", CYAN, TELEBOOK);
    printf("%s%s\n\n", WHITE, DIVIDER);
    
    for (int i = 0; i < length_of_users; i++) {
        printf("    %s%d. %s%s : %s\n", CYAN, (i + 1), WHITE, users[i].username, users[i].phone);
    }

    printf("%s%s\n\n", WHITE, DIVIDER);
}

void list_saved_contacts(const char* username) {
    for (int i = 0; i < length_of_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            // Check User Has Saved Contacts
            if (users[i].length_of_contacts < 1) {
                system("cls");
                printf("%s%s", CYAN, TELEBOOK);
                printf("%s%s\n\n", WHITE, DIVIDER);
                printf("    %sX %sNo Saved Contacts\n", RED, WHITE);
                printf("%s%s\n\n", WHITE, DIVIDER);
                return;
            }

            system("cls");
            printf("%s%s", CYAN, TELEBOOK);
            printf("%s%s\n\n", WHITE, DIVIDER);

            // List Saved Contacts
            for (int j = 0; j < users[i].length_of_contacts && users[i].contacts[j][0] != "\0"; j++) {
                const char phone[PHONE_MAX_LENGTH];
                strcpy(phone, get_phone_by_username(users[i].contacts[j]));
                printf("    %s%d. %s%s : %s\n", CYAN, (j + 1), WHITE, users[i].contacts[j], phone);
            }

            printf("%s%s\n\n", WHITE, DIVIDER);
        }
    }
}
