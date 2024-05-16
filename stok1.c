#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int code;
	char name[25];
	int stokLvl;
	int minStok;
	double buyPrice, sellPrice;
} StokItem;

StokItem menu[] = {
	{1, "Nasi Goreng\n", 0, 0 , 0.0, 0.0}, 
	{2, "Air\n", 0, 0 , 0.0, 0.0}, 
	{3, "Desert\n", 0, 0 , 0.0, 0.0}
};

void displayMenu() {
	for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
		printf("%d. %-25s\n", menu[i].code, menu[i].name);
		}
}

void NasiGorengMenu() {
	printf("\nNasi Goreng Variations\n");
	printf("| 		Dish			| 	Price List		|\n");
	printf("|-----------------------------------------------------------------------|\n");
	printf("| 1. Nasi Goreng USA			| RM2.00\n");
}


int main() {
	// menu variable
	int choice, subChoice;
	StokItem myStok;
	
	// Message & Menu Options
		printf("\tWelcome to Our Shop!1\n");
		printf("Please make a selection\n");
		printf("1. Menu\n");
		printf("2. Exit\n");
		
		printf("Enter your selection: ");
		scanf("%d", &choice);
		
	if (choice == 1) {
		displayMenu();
	

		// Prompt for sub-selection for each MENU
	
		printf("\nWhat would you like to see details for?\n");
		printf("1. Nasi Goreng\n");
		
		printf("Enter your selection: ");
		scanf("%d", &subChoice);
	
			if (subChoice == 1) {
				NasiGorengMenu();
			} else {
				printf("Invalid Choice\n");
			}
		} else if (choice == 2) {
			printf("Thank you! See you again ^_^\n");
			return 0;
		} else {
			printf("Invalid Choice.\n");
		}
			
	return 0;
}
