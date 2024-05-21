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
    {1, "Nasi Goreng", 0, 0, 0.0, 0.0},
    {2, "Air", 0, 0, 0.0, 0.0},
    {3, "Desert", 0, 0, 0.0, 0.0}
};

StokItem nasiGorengVariations[] = {
    {1, "Nasi Goreng USA", 0, 0, 0.0, 7.0},
    {2, "Nasi Goreng Cina", 0, 0, 0.0, 4.0},
    {3, "Nasi Goreng Kampung", 0, 0, 0.0, 5.0}
};

StokItem airVariations[] = {
    {1, "Sirap", 0, 0, 0.0, 1.0},
    {2, "Teh O Ais", 0, 0, 0.0, 4.0},
    {3, "Rootbeer", 0, 0, 0.0, 5.0}
};

StokItem dessertVariations[] = {
    {1, "Ice Cream Malaysia", 0, 0, 0.0, 1.0},
    {2, "Bingsu", 0, 0, 0.0, 9.0},
    {3, "Cupcake", 0, 0, 0.0, 2.0}
};

void displayMenu() {
    for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
        printf("%d. %-25s\n", menu[i].code, menu[i].name);
    }
}

void NasiGorengMenu() {
    printf("\nNasi Goreng Variations\n");
    printf("|       Dish                   |   Price List       |   Stock Left	  |\n");
    printf("|-------------------------------------------------------------------------|\n");
    for (int i = 0; i < sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]); i++) {
        printf("| %d. %-25s | RM%.2f             |\n", nasiGorengVariations[i].code, nasiGorengVariations[i].name, nasiGorengVariations[i].sellPrice);
    }
}

void AirMenu() {
    printf("\nAir Variations\n");
    printf("|       Dish                   |   Price List       |   Stock Left	  |\n");
    printf("|-------------------------------------------------------------------------|\n");
    for (int i = 0; i < sizeof(airVariations) / sizeof(airVariations[0]); i++) {
        printf("| %d. %-25s | RM%.2f             |\n", airVariations[i].code, airVariations[i].name, airVariations[i].sellPrice);
    }
}

void DessertMenu() {
	printf("\nDessert Variations\n");
    	printf("|       Dish                   |   Price List       |   Stock Left	  |\n");
    	printf("|-------------------------------------------------------------------------|\n");
    	for (int i = 0; i < sizeof(dessertVariations) / sizeof(dessertVariations[0]); i++) {
        	printf("| %d. %-25s | RM%.2f             |\n", dessertVariations[i].code, dessertVariations[i].name, dessertVariations[i].sellPrice);
    	}
}

void processOrder(char *dishName, double price) {
    char name[50];12313132
    char phone[20];
    int quantity;
    FILE *file = fopen("list.txt", "a");
    if (file == NULL) {12313132
        printf("Error opening file for appending.\n");
        return;
    }

    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    printf("Enter your phone number: ");
    scanf(" %[^\n]", phone);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Phone: %s\n", phone);
    fprintf(file, "Dish: %s\n", dishName);
    fprintf(file, "Quantity: %d\n", quantity);
    fprintf(file, "Total Price: RM%.2f\n", price * quantity);
    fprintf(file, "Stock left %s: \n", dishName); // test
    fprintf(file, "---------------------------------------\n");

    printf("Order for %d %s has been added to your list.\n", quantity, dishName);

    fclose(file);
}

int main() {
    int choice, subChoice, menuChoice;

    while (1) {
        printf("\tWelcome to Our Shop!\n");
        printf("Please make a selection\n");
        printf("1. Menu\n");
        printf("2. Exit\n");

        printf("Enter your selection: ");
        scanf("%d", &choice);

        if (choice == 1) {
            displayMenu();

            printf("\nWhat would you like to see details for?\n");
            printf("Enter your selection: ");
            scanf("%d", &subChoice);

            if (subChoice == 1) {  // Nasi Goreng
                NasiGorengMenu();
                printf("\nWhich Nasi Goreng variation do you want: ");
                scanf("%d", &menuChoice);

                if (menuChoice >= 1 && menuChoice <= sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0])) {
                    processOrder(nasiGorengVariations[menuChoice - 1].name, nasiGorengVariations[menuChoice - 1].sellPrice);
                } else {
                    printf("Invalid Choice\n");
                }
            } 
            
            else if (subChoice == 2) {  // Air
                AirMenu();
                printf("\nWhich Air variation do you want: ");
                scanf("%d", &menuChoice);

                if (menuChoice >= 1 && menuChoice <= sizeof(airVariations) / sizeof(airVariations[0])) {
                    processOrder(airVariations[menuChoice - 1].name, airVariations[menuChoice - 1].sellPrice);
                } else {
                    printf("Invalid Choice\n");
                }
            } 
            
            else if (subChoice == 3) { // Dessert
            	DessertMenu();
            	printf("\nWhich Dessert variation do you want: ");
                scanf("%d", &menuChoice);
            	
            	if (menuChoice >= 1 && menuChoice <= sizeof(airVariations) / sizeof(airVariations[0])) {
                    processOrder(dessertVariations[menuChoice - 1].name, dessertVariations[menuChoice - 1].sellPrice);
                } else {
                	printf("Invalid Choice\n");
                }
            } else {
                printf("Invalid Choice\n");
            }
            
        } else if (choice == 2) {
            printf("Thank you! See you again ^_^\n");
            break;   
        } else {
            printf("Invalid Choice.\n");
        }
    }

    return 0;
}
