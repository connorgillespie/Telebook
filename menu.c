/*
	Connor Gillespie
	3/22/2024
	ITT-310
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "users.h"
#include "menu.h"

char current_user[USERNAME_MAX_LENGTH];

void pause_return_to_menu() {
	printf("    %s? %sPress Any Key to Return to the Main Menu\n", YELLOW, WHITE);
	getch();
}

void quit_menu() {
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %sX %sThanks For Using Telebook\n", RED, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);
	exit(0);
}

void create_account_menu() {
	char username[USERNAME_MAX_LENGTH];
	char password[256];
	char phone[PHONE_MAX_LENGTH];
	const char contacts[USERNAME_MAX_LENGTH][CONTACTS_MAX_LENGTH] = { NULL };

	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s? %sThe Following Prompts Are Case Sensitive\n", CYAN, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);

	printf("    %sUsername %s> %s", WHITE, CYAN, WHITE);
	scanf_s("%s", &username, USERNAME_MAX_LENGTH);

	// Check Username Does Not Exist
	if (verify_username_exists(username) == true) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %sX %sThe Username Already Exists\n", RED, WHITE);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return;
	}

	printf("    %sPassword %s> %s", WHITE, CYAN, WHITE);
	scanf_s("%s", password, 256);

	printf("    %sPhone Without Spaces (Ex: 8889991234) %s> %s", WHITE, CYAN, WHITE);
	scanf_s("%s", phone, PHONE_MAX_LENGTH);

	add_user(username, hash(password), phone, contacts, 0);  // Add New User Account
	
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s! %sUser Account Successfully Created\n", GREEN, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);
	pause_return_to_menu();
}

void login_menu() {
	bool loop = true;
	while (loop) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %s? %sEnter Username to Login\n", CYAN, WHITE);
		printf("    %sC %sCreate New Account\n", GREEN, WHITE);
		printf("    %sQ %sQuit Application\n", RED, WHITE);
		printf("%s%s\n\n", WHITE, DIVIDER);

		char username[256];
		printf("    %sUsername %s> %s", WHITE, CYAN, WHITE);
		scanf_s("%s", &username, 256);

		// Check for Quit
		if (strcmp(username, "q") == 0 || strcmp(username, "Q") == 0) {
			quit_menu();
		}

		// Check for Create Account
		if (strcmp(username, "c") == 0 || strcmp(username, "C") == 0) {
			create_account_menu();
		}
		else {
			if (verify_username_exists(username)) {
				char password[256];
				printf("    %sPassword %s> %s", WHITE, CYAN, WHITE);
				scanf_s("%s", &password, 256);

				if (validate_credentials(username, password)) {
					strcpy(current_user, username);  // Assign Current User
					return;
				}
			}
		}
	}
}

void add_new_contact_menu() {
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s? %sEnter Username to Add to Saved Contacts\n", CYAN, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);

	char username[256];
	printf("    %sUsername %s> %s", WHITE, CYAN, WHITE);
	scanf_s("%s", &username, 256);

	// Check if Contact's Username Exists
	if (verify_username_exists(username) == false) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %sX %sThe Username Provided Does Not Exist\n", RED, WHITE);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return;
	}

	// Check if Contact's Username is Already in Saved Contacts
	if (verify_contact_already_saved(current_user, username) == true) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %sX %s%s is Already a Saved Contact\n", RED, WHITE, username);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return;
	}

	// Add New Contact
	add_contact_to_user(current_user, username);
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s! %sAdded %s to Saved Contacts\n", GREEN, WHITE, username);
	printf("%s%s\n\n", WHITE, DIVIDER);
	pause_return_to_menu();
}

void remove_contact_menu() {
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s? %sEnter Username to Remove from Saved Contacts\n", CYAN, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);

	char username[256];
	printf("    %sUsername %s> %s", WHITE, CYAN, WHITE);
	scanf_s("%s", &username, 256);

	// Check if Contact's Username Exists
	if (verify_username_exists(username) == false) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %sX %sThe Username Provided Does Not Exist\n", RED, WHITE);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return;
	}

	// Check if Contact's Username is Not in Saved Contacts
	if (verify_contact_already_saved(current_user, username) == false) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %sX %s%s is Not a Saved Contact\n", RED, WHITE, username);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return;
	}

	// Remove Contact
	remove_contact_from_user(current_user, username);
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s! %sRemoved %s from Saved Contacts\n", GREEN, WHITE, username);
	printf("%s%s\n\n", WHITE, DIVIDER);
	pause_return_to_menu();
}

bool confirm_delete_account() {
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s@ %sThis Action is Irreversible\n", YELLOW, WHITE);
	printf("    %sY %sConfirm to Delete Account\n", GREEN, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);

	char selection[256];
	printf("    %sSelection %s> %s", WHITE, CYAN, WHITE);
	scanf_s("%s", &selection, 256);

	// Check for Confirmation
	if (strcmp(selection, "y") == 0 || strcmp(selection, "Y") == 0) {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %s! %sSuccessfully Removed Account from Telebook\n", GREEN, WHITE);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return true;
	}
	else {
		system("cls");
		printf("%s%s", CYAN, TELEBOOK);
		printf("%s%s\n\n", WHITE, DIVIDER);
		printf("    %sX %sAccount Deletion Confirmation Failed\n", RED, WHITE);
		printf("%s%s\n\n", WHITE, DIVIDER);
		pause_return_to_menu();
		return false;
	}
}

void commands_banner() {
	system("cls");
	printf("%s%s", CYAN, TELEBOOK);
	printf("%s%s\n\n", WHITE, DIVIDER);
	printf("    %s1 %sList Saved Contacts\n", CYAN, WHITE);
	printf("    %s2 %sAdd New Contact\n", CYAN, WHITE);
	printf("    %s3 %sRemove Saved Contact\n", CYAN, WHITE);
	printf("    %s4 %sSearch Telebook for Contacts\n", CYAN, WHITE);
	printf("    %sL %sLogout of Account\n", RED, WHITE);
	printf("    %sD %sDelete Account\n", RED, WHITE);
	printf("    %sQ %sQuit Application\n", RED, WHITE);
	printf("%s%s\n\n", WHITE, DIVIDER);
}

void menu() {
	while (strcmp(current_user, "") == 0) {
		login_menu();  // Set Current User Account

		while (true) {
			commands_banner();

			// Assign Temporary String for Selection Error Handling
			char temporary[128];
			printf("    %sSelection %s> %s", WHITE, CYAN, WHITE);
			if (scanf_s("%19s", temporary, 128) != 1) {
				return;
			}

			// Check for Logout Characters
			if (strcmp(temporary, "l") == 0 || strcmp(temporary, "L") == 0) {
				strcpy(current_user, "");  // Remove Current User
				break;
			}

			// Check for Delete Characters
			if (strcmp(temporary, "d") == 0 || strcmp(temporary, "D") == 0) {
				if (confirm_delete_account()) {
					remove_user(current_user);
					strcpy(current_user, "");
					break;
				}
			}

			// Check for Quit Characters
			if (strcmp(temporary, "q") == 0 || strcmp(temporary, "Q") == 0) {
				quit_menu();
			}

			int selection = atoi(temporary);  // Cast Selection to Integer
			switch (selection) {
			case 1:
				system("cls");
				list_saved_contacts(current_user);
				pause_return_to_menu();
				break;
			case 2:
				add_new_contact_menu();
				break;
			case 3:
				remove_contact_menu();
				break;
			case 4:
				list_users();
				pause_return_to_menu();
				break;
			default:
				break;
			}
		}
	}
}
