#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STOCK_FILE "stock.txt"
#define DATASTOCK_FILE "datastock.txt"
#define PROFIT_FILE "profit.txt"

typedef struct {
    int code;
    char name[25];
    int stokLvl;
    int minStok;
    int maxStok;
    double buyPrice;
    double sellPrice;
    int totalSold;
} StokItem;

StokItem nasiGorengVariations[] = {
    {1, "Nasi Goreng USA", 50, 10, 100, 0.0, 7.0, 0},
    {2, "Nasi Goreng Cina", 40, 10, 100, 0.0, 4.0, 0},
    {3, "Nasi Goreng Kampung", 30, 10, 100, 0.0, 5.0, 0}
};

StokItem airVariations[] = {
    {1, "Sirap", 60, 20, 100, 0.50, 1.0, 0},
    {2, "Teh O Ais", 50, 20, 100, 0.0, 4.0, 0},
    {3, "Rootbeer", 40, 20, 100, 0.0, 5.0, 0}
};

StokItem dessertVariations[] = {
    {1, "Ice Cream Malaysia", 70, 30, 100, 0.0, 1.0, 0},
    {2, "Bingsu", 20, 5, 100, 0.0, 9.0, 0},
    {3, "Cupcake", 50, 20, 100, 0.0, 2.0, 0}
};

void readStockLevels() {
    FILE *file = fopen(STOCK_FILE, "r");
    if (file == NULL) {
        printf("Error opening stock file. Using default values.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char name[25];
        int stokLvl, totalSold;
        if (sscanf(line, "%[^,],%d,%d", name, &stokLvl, &totalSold) == 3) {
            for (int i = 0; i < sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]); i++) {
                if (strcmp(nasiGorengVariations[i].name, name) == 0) {
                    nasiGorengVariations[i].stokLvl = stokLvl;
                    nasiGorengVariations[i].totalSold = totalSold;
                }
            }
            for (int i = 0; i < sizeof(airVariations) / sizeof(airVariations[0]); i++) {
                if (strcmp(airVariations[i].name, name) == 0) {
                    airVariations[i].stokLvl = stokLvl;
                    airVariations[i].totalSold = totalSold;
                }
            }
            for (int i = 0; i < sizeof(dessertVariations) / sizeof(dessertVariations[0]); i++) {
                if (strcmp(dessertVariations[i].name, name) == 0) {
                    dessertVariations[i].stokLvl = stokLvl;
                    dessertVariations[i].totalSold = totalSold;
                }
            }
        }
    }
    fclose(file);
}

void writeStockLevels() {
    FILE *file = fopen(STOCK_FILE, "w");
    if (file == NULL) {
        printf("Error opening stock file for writing.\n");
        return;
    }

    for (int i = 0; i < sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]); i++) {
        fprintf(file, "%s,%d,%d\n", nasiGorengVariations[i].name, nasiGorengVariations[i].stokLvl, nasiGorengVariations[i].totalSold);
    }
    for (int i = 0; i < sizeof(airVariations) / sizeof(airVariations[0]); i++) {
        fprintf(file, "%s,%d,%d\n", airVariations[i].name, airVariations[i].stokLvl, airVariations[i].totalSold);
    }
    for (int i = 0; i < sizeof(dessertVariations) / sizeof(dessertVariations[0]); i++) {
        fprintf(file, "%s,%d,%d\n", dessertVariations[i].name, dessertVariations[i].stokLvl, dessertVariations[i].totalSold);
    }

    fclose(file);
}

void writeDataStock() {
    FILE *file = fopen(DATASTOCK_FILE, "w");
    if (file == NULL) {
        printf("Error opening data stock file for writing.\n");
        return;
    }

    for (int i = 0; i < sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]); i++) {
        fprintf(file, "Name: %s\nStock Level: %d\nMin Stock: %d\nMax Stock: %d\nBuy Price: %.2f\nSell Price: %.2f\nTotal Sold: %d\n\n",
            nasiGorengVariations[i].name, nasiGorengVariations[i].stokLvl, nasiGorengVariations[i].minStok, nasiGorengVariations[i].maxStok,
            nasiGorengVariations[i].buyPrice, nasiGorengVariations[i].sellPrice, nasiGorengVariations[i].totalSold);
    }
    for (int i = 0; i < sizeof(airVariations) / sizeof(airVariations[0]); i++) {
        fprintf(file, "Name: %s\nStock Level: %d\nMin Stock: %d\nMax Stock: %d\nBuy Price: %.2f\nSell Price: %.2f\nTotal Sold: %d\n\n",
            airVariations[i].name, airVariations[i].stokLvl, airVariations[i].minStok, airVariations[i].maxStok,
            airVariations[i].buyPrice, airVariations[i].sellPrice, airVariations[i].totalSold);
    }
    for (int i = 0; i < sizeof(dessertVariations) / sizeof(dessertVariations[0]); i++) {
        fprintf(file, "Name: %s\nStock Level: %d\nMin Stock: %d\nMax Stock: %d\nBuy Price: %.2f\nSell Price: %.2f\nTotal Sold: %d\n\n",
            dessertVariations[i].name, dessertVariations[i].stokLvl, dessertVariations[i].minStok, dessertVariations[i].maxStok,
            dessertVariations[i].buyPrice, dessertVariations[i].sellPrice, dessertVariations[i].totalSold);
    }

    fclose(file);
}

void writeProfitFile() {
    FILE *file = fopen(PROFIT_FILE, "w");
    if (file == NULL) {
        printf("Error opening profit file for writing.\n");
        return;
    }

    for (int i = 0; i < sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]); i++) {
        double profit = (nasiGorengVariations[i].sellPrice - nasiGorengVariations[i].buyPrice) * nasiGorengVariations[i].totalSold;
        fprintf(file, "Name: %s\nTotal Sold: %d\nProfit: RM%.2f\n\n", nasiGorengVariations[i].name, nasiGorengVariations[i].totalSold, profit);
    }
    for (int i = 0; i < sizeof(airVariations) / sizeof(airVariations[0]); i++) {
        double profit = (airVariations[i].sellPrice - airVariations[i].buyPrice) * airVariations[i].totalSold;
        fprintf(file, "Name: %s\nTotal Sold: %d\nProfit: RM%.2f\n\n", airVariations[i].name, airVariations[i].totalSold, profit);
    }
    for (int i = 0; i < sizeof(dessertVariations) / sizeof(dessertVariations[0]); i++) {
        double profit = (dessertVariations[i].sellPrice - dessertVariations[i].buyPrice) * dessertVariations[i].totalSold;
        fprintf(file, "Name: %s\nTotal Sold: %d\nProfit: RM%.2f\n\n", dessertVariations[i].name, dessertVariations[i].totalSold, profit);
    }

    fclose(file);
}

void displayMenu() {
    printf("1. Nasi Goreng\n");
    printf("2. Air\n");
    printf("3. Dessert\n");
    printf("4. Go Back\n");
}

void NasiGorengMenu() {
    printf("\nNasi Goreng Variations\n");
    printf("|       Dish                   |   Price List       |   Stock Left   |\n");
    printf("|-------------------------------------------------------------------------|\n");
    for (int i = 0; i < sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]); i++) {
        printf("| %d. %-25s | RM%.2f             | %-14d |\n", nasiGorengVariations[i].code, nasiGorengVariations[i].name, nasiGorengVariations[i].sellPrice, nasiGorengVariations[i].stokLvl);
    }
    printf("| %d. Back to Menu\n", sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]) + 1);
}

void AirMenu() {
    printf("\nAir Variations\n");
    printf("|       Dish                   |   Price List       |   Stock Left   |\n");
    printf("|-------------------------------------------------------------------------|\n");
    for (int i = 0; i < sizeof(airVariations) / sizeof(airVariations[0]); i++) {
        printf("| %d. %-25s | RM%.2f             | %-14d |\n", airVariations[i].code, airVariations[i].name, airVariations[i].sellPrice, airVariations[i].stokLvl);
    }
    printf("| %d. Back to Menu\n", sizeof(airVariations) / sizeof(airVariations[0]) + 1);
}

void DessertMenu() {
    printf("\nDessert Variations\n");
    printf("|       Dish                   |   Price List       |   Stock Left   |\n");
    printf("|-------------------------------------------------------------------------|\n");
    for (int i = 0; i < sizeof(dessertVariations) / sizeof(dessertVariations[0]); i++) {
        printf("| %d. %-25s | RM%.2f             | %-14d |\n", dessertVariations[i].code, dessertVariations[i].name, dessertVariations[i].sellPrice, dessertVariations[i].stokLvl);
    }
    printf("| %d. Back to Menu\n", sizeof(dessertVariations) / sizeof(dessertVariations[0]) + 1);
}

void checkStockDetails() {
    FILE *file = fopen(DATASTOCK_FILE, "r");
    if (file == NULL) {
        printf("Error opening data stock file. Please make sure to update the stock first.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void processOrder(char *dishName, double price, int *stokLvl, int *totalSold) {
    char name[50];
    char phone[20];
    int quantity;
    FILE *file = fopen("list.txt", "a");
    if (file == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }

    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    printf("Enter your phone number: ");
    scanf(" %[^\n]", phone);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity > *stokLvl) {
        printf("Sorry, we only have %d %s left.\n", *stokLvl, dishName);
        fclose(file);
        return;
    }

    *stokLvl -= quantity;
    *totalSold += quantity;

    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Phone: %s\n", phone);
    fprintf(file, "Dish: %s\n", dishName);
    fprintf(file, "Quantity: %d\n", quantity);
    fprintf(file, "Total Price: RM%.2f\n", price * quantity);
    fprintf(file, "Stock left: %d\n", *stokLvl);
    fprintf(file, "---------------------------------------\n");

    printf("Order for %d %s has been added to your list.\n", quantity, dishName);

    fclose(file);
    writeStockLevels();
    writeDataStock();
    writeProfitFile();
}

void updateStock() {
    int choice, variationChoice, newStock;
    double newBuyPrice, newSellPrice;
    int newMinStok, newMaxStok;

    while (1) {
        displayMenu();
        printf("Select the category to update stock: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        switch (choice) {
            case 1:
                NasiGorengMenu();
                printf("Select the variation to update stock: ");
                scanf("%d", &variationChoice);
                if (variationChoice >= 1 && variationChoice <= sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0])) {
                    printf("Enter new stock level for %s: ", nasiGorengVariations[variationChoice - 1].name);
                    scanf("%d", &newStock);
                    nasiGorengVariations[variationChoice - 1].stokLvl = newStock;

                    printf("Enter new minimum stock for %s: ", nasiGorengVariations[variationChoice - 1].name);
                    scanf("%d", &newMinStok);
                    nasiGorengVariations[variationChoice - 1].minStok = newMinStok;

                    printf("Enter new maximum stock for %s: ", nasiGorengVariations[variationChoice - 1].name);
                    scanf("%d", &newMaxStok);
                    nasiGorengVariations[variationChoice - 1].maxStok = newMaxStok;

                    printf("Enter new buy price for %s: ", nasiGorengVariations[variationChoice - 1].name);
                    scanf("%lf", &newBuyPrice);
                    nasiGorengVariations[variationChoice - 1].buyPrice = newBuyPrice;

                    printf("Enter new sell price for %s: ", nasiGorengVariations[variationChoice - 1].name);
                    scanf("%lf", &newSellPrice);
                    nasiGorengVariations[variationChoice - 1].sellPrice = newSellPrice;
                    
                    printf("Stock for %s successfully updated.\n\n", nasiGorengVariations[variationChoice - 1].name);
                    break;
                } else if (variationChoice == sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0]) + 1) {
                    break; // Exit the switch statement to return to the main loop
                } else {
                    printf("Invalid choice.\n");
                }
                break;
            case 2:
                AirMenu();
                printf("Select the variation to update stock: ");
                scanf("%d", &variationChoice);
                if (variationChoice >= 1 && variationChoice <= sizeof(airVariations) / sizeof(airVariations[0])) {
                    printf("Enter new stock level for %s: ", airVariations[variationChoice - 1].name);
                    scanf("%d", &newStock);
                    airVariations[variationChoice - 1].stokLvl = newStock;

                    printf("Enter new minimum stock for %s: ", airVariations[variationChoice - 1].name);
                    scanf("%d", &newMinStok);
                    airVariations[variationChoice - 1].minStok = newMinStok;

                    printf("Enter new maximum stock for %s: ", airVariations[variationChoice - 1].name);
                    scanf("%d", &newMaxStok);
                    airVariations[variationChoice - 1].maxStok = newMaxStok;

                    printf("Enter new buy price for %s: ", airVariations[variationChoice - 1].name);
                    scanf("%lf", &newBuyPrice);
                    airVariations[variationChoice - 1].buyPrice = newBuyPrice;

                    printf("Enter new sell price for %s: ", airVariations[variationChoice - 1].name);
                    scanf("%lf", &newSellPrice);
                    airVariations[variationChoice - 1].sellPrice = newSellPrice;
                    printf("Stock for %s successfully updated.\n\n", airVariations[variationChoice - 1].name);
                    break;
                } else if (variationChoice == sizeof(airVariations) / sizeof(airVariations[0]) + 1) {
                    break; // Exit the switch statement to return to the main loop
                } else {
                    printf("Invalid choice.\n");
                }
                break;
            case 3:
                DessertMenu();
                printf("Select the variation to update stock: ");
                scanf("%d", &variationChoice);
                if (variationChoice >= 1 && variationChoice <= sizeof(dessertVariations) / sizeof(dessertVariations[0])) {
                    printf("Enter new stock level for %s: ", dessertVariations[variationChoice - 1].name);
                    scanf("%d", &newStock);
                    dessertVariations[variationChoice - 1].stokLvl = newStock;

                    printf("Enter new minimum stock for %s: ", dessertVariations[variationChoice - 1].name);
                    scanf("%d", &newMinStok);
                    dessertVariations[variationChoice - 1].minStok = newMinStok;

                    printf("Enter new maximum stock for %s: ", dessertVariations[variationChoice - 1].name);
                    scanf("%d", &newMaxStok);
                    dessertVariations[variationChoice - 1].maxStok = newMaxStok;

                    printf("Enter new buy price for %s: ", dessertVariations[variationChoice - 1].name);
                    scanf("%lf", &newBuyPrice);
                    dessertVariations[variationChoice - 1].buyPrice = newBuyPrice;

                    printf("Enter new sell price for %s: ", dessertVariations[variationChoice - 1].name);
                    scanf("%lf", &newSellPrice);
                    dessertVariations[variationChoice - 1].sellPrice = newSellPrice;
                    
                    printf("Stock for %s successfully updated.\n\n", dessertVariations[variationChoice - 1].name);
                    break;
                } else if (variationChoice == sizeof(dessertVariations) / sizeof(dessertVariations[0]) + 1) {
                    break; // Exit the switch statement to return to the main loop
                } else {
                    printf("Invalid choice.\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        writeStockLevels();
        writeDataStock();
        writeProfitFile();
    }
}


int main() {
    int selection;

    readStockLevels();

    while (1) {
        printf("\n    Welcome to Our Shop!\n");
        printf("Please make a selection\n");
        printf("1. Menu\n");
        printf("2. Update Stock\n");
        printf("3. Check Stock Details\n");
        printf("4. Exit\n");

        printf("Enter your selection: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1: {
                int dishSelection;
                do {
                    displayMenu();
                    printf("\nWhat would you like to see details for?\n");
                    printf("Enter your selection: ");
                    scanf("%d", &dishSelection);

                    if (dishSelection == 4) {
                        break; // Go back
                    }

                    switch (dishSelection) {
                        case 1:
                            NasiGorengMenu();
                            printf("\nWhich Nasi Goreng variation do you want: ");
                            scanf("%d", &dishSelection);
                            if (dishSelection >= 1 && dishSelection <= sizeof(nasiGorengVariations) / sizeof(nasiGorengVariations[0])) {
                                processOrder(nasiGorengVariations[dishSelection - 1].name, nasiGorengVariations[dishSelection - 1].sellPrice, &nasiGorengVariations[dishSelection - 1].stokLvl, &nasiGorengVariations[dishSelection - 1].totalSold);
                            } else {
                                printf("Invalid selection.\n");
                            }
                            break;
                        case 2:
                            AirMenu();
                            printf("\nWhich Air variation do you want: ");
                            scanf("%d", &dishSelection);
                            if (dishSelection >= 1 && dishSelection <= sizeof(airVariations) / sizeof(airVariations[0])) {
                                processOrder(airVariations[dishSelection - 1].name, airVariations[dishSelection - 1].sellPrice, &airVariations[dishSelection - 1].stokLvl, &airVariations[dishSelection - 1].totalSold);
                            } else {
                                printf("Invalid selection.\n");
                            }
                            break;
                        case 3:
                            DessertMenu();
                            printf("\nWhich Dessert variation do you want: ");
                            scanf("%d", &dishSelection);
                            if (dishSelection >= 1 && dishSelection <= sizeof(dessertVariations) / sizeof(dessertVariations[0])) {
                                processOrder(dessertVariations[dishSelection - 1].name, dessertVariations[dishSelection - 1].sellPrice, &dessertVariations[dishSelection - 1].stokLvl, &dessertVariations[dishSelection - 1].totalSold);
                            } else {
                                printf("Invalid selection.\n");
                            }
                            break;
                        default:
                            printf("Invalid selection.\n");
                            break;
                    }
                } while (1); // Loop until "Go Back" is selected
                break;
            }
            case 2:
                updateStock();
                break;
            case 3:
                checkStockDetails();
                break;
            case 4:
                printf("Thank you! See you again ^_^\n");
                return 0;
            default:
                printf("Invalid selection.\n");
                break;
        }
    }

    return 0;
}
