/*
	Connor Gillespie
	3/22/2024
	ITT-310
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "menu.h"
#include "users.h"

int main(void) {
	load_from_file();  // Load Current Users from Data File
	menu();  // Start Menu Loop
}
