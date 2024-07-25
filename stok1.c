#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For access function
#include <time.h>

#define NUM_ITEMS_LELAKI 5
#define NUM_ITEMS_PEREMPUAN 8
#define NUM_ITEMS_ACCESSORIES 7
#define NUM_ITEMS (NUM_ITEMS_LELAKI + NUM_ITEMS_PEREMPUAN + NUM_ITEMS_ACCESSORIES)
#define FILENAME "MyKdata.txt"
#define BACKUP_FILENAME "MyKdata.ori"
#define CUSTOMER_FILENAME "CustomerData.txt"
#define TRANSACTION_FILENAME "Transactions.txt"
#define PROFIT_FILENAME "ProfitData.txt"
#define MARKUP 0.30 // Fixed markup value (30%)

typedef struct {
    int id;
    char name[50];
    int quantity;
    int max_stock;
    int min_stock;
    float cost_price;
    float selling_price;
} Item;

typedef struct {
    char name[50];
    char phone[15];
} Customer;

typedef struct {
    char phone[15];
    int item_id;
    int quantity;
    float total_price;
} Transaction;

// Forward declaration
void saveProfitData(const char *filename, float grossProfit, float netProfit, float totalRestockingCost, Item items[], int numItems);

// Global variables to track total profit and restocking costs
float totalProfit = 0.0;
float totalRestockingCost = 0.0;
float grossProfit = 0.0;
float netProfit = 0.0;

void trimTrailingSpaces(char *str) {
    int index, i;
    index = -1;

    // Find the last non-space character
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            index = i;
        }
    }

    // Null terminate the string after the last non-space character
    str[index + 1] = '\0';
}

void createBackup(const char *srcFilename, const char *backupFilename) {
    FILE *srcFile = fopen(srcFilename, "r");
    if (!srcFile) {
        printf("Error: Unable to open source file.\n");
        return;
    }

    FILE *backupFile = fopen(backupFilename, "w");
    if (!backupFile) {
        printf("Error: Unable to create backup file.\n");
        fclose(srcFile);
        return;
    }

    char ch;
    while ((ch = fgetc(srcFile)) != EOF) {
        fputc(ch, backupFile);
    }

    fclose(srcFile);
    fclose(backupFile);
}

void saveItemsToFile(const char *filename, Item items[], int numItems) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < numItems; i++) {
        fprintf(file, "ID: %d | Name: %s | Quantity: %d | Max Stock: %d | Min Stock: %d | Cost Price: %.2f | Selling Price: %.2f\n", 
                items[i].id, items[i].name, items[i].quantity, 
                items[i].max_stock, items[i].min_stock, 
                items[i].cost_price, items[i].selling_price);
    }

    fclose(file);
}

void loadItemsFromFile(const char *filename, Item items[], int numItems) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    for (int i = 0; i < numItems; i++) {
        int result = fscanf(file, "ID: %d | Name: %49[^|] | Quantity: %d | Max Stock: %d | Min Stock: %d | Cost Price: %f | Selling Price: %f\n", 
                            &items[i].id, items[i].name, &items[i].quantity, 
                            &items[i].max_stock, &items[i].min_stock, 
                            &items[i].cost_price, &items[i].selling_price);
        if (result != 7) { // Ensure all 7 fields are read correctly
            printf("Error: Incorrect data format in file.\n");
            break;
        }
        trimTrailingSpaces(items[i].name); // Trim trailing spaces from item name
    }

    fclose(file);

    // Fixed selling prices
    const float fixedSellingPrices[] = {
        80.00, 80.00, 80.00, 60.00, 70.00,
        280.00, 200.00, 150.00, 190.00, 200.00,
        170.00, 250.00, 200.00,
        45.00, 50.00, 30.00, 2.00, 10.00, 5.00, 10.00
    };

    for (int i = 0; i < numItems; i++) {
        items[i].selling_price = fixedSellingPrices[i];
    }
}


void createSampleData(Item items[], int numItems) {
    const char *names[] = {
        "[LELAKI] Lengan Pendek", "[LELAKI] Cekak Musang", "[LELAKI] Teluk Belanga", "[LELAKI] Kurta", "[LELAKI] Jubah",
        "[PEREMPUAN] Cekak Musang", "[PEREMPUAN] Kebaya", "[PEREMPUAN] Pario", "[PEREMPUAN] Kedah", "[PEREMPUAN] Moden",
        "[PEREMPUAN] Jubah", "[PEREMPUAN] Kebarung", "[PEREMPUAN] Teluk Belanga",
        "Sampin", "Selendang", "Songkok", "Kerongsang", "Butang Baju", "Sampul Raya", "Handkerchief"
    };

    const float sellingPrices[] = {
        80.00, 80.00, 80.00, 60.00, 70.00,
        280.00, 200.00, 150.00, 190.00, 200.00,
        170.00, 250.00, 200.00,
        45.00, 50.00, 30.00, 2.00, 10.00, 5.00, 10.00
    };

    const int quantities[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 200, 100}; // Initial quantities

    for (int i = 0; i < numItems; i++) {
        items[i].id = i + 1;
        strncpy(items[i].name, names[i], 50);
        trimTrailingSpaces(items[i].name); // Trim trailing spaces from item name
        items[i].quantity = quantities[i]; // Initial stock quantity
        items[i].max_stock = 100; // Maximum stock size
        items[i].min_stock = 10; // Minimum stock size limit
        items[i].selling_price = sellingPrices[i]; // Fixed selling price

        // Calculate cost price based on fixed selling price and markup
        items[i].cost_price = items[i].selling_price / (1 + MARKUP);
    }
}


void displayItems(Item items[], int numItems, const char *category) {
    printf("\n****** %s ******\n", category);
    printf("-------------------------------\n");
    for (int i = 0; i < numItems; i++) {
        printf(" %d. %s        	| RM %.2f\n", items[i].id, items[i].name, items[i].selling_price);
    }
}

void displayAllItems(Item items[], int numItemsLelaki, int numItemsPerempuan, int numItemsAccessories) {
    displayItems(items, numItemsLelaki, "BAJU RAYA LELAKI");
    displayItems(items + numItemsLelaki, numItemsPerempuan, "BAJU KURUNG PEREMPUAN");
    displayItems(items + numItemsLelaki + numItemsPerempuan, numItemsAccessories, "ACCESSORIES RAYA");
}

int findCustomerIndex(Customer customers[], int numCustomers, const char *phone) {
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            return i;
        }
    }
    return -1;
}

void loadCustomers(Customer customers[], int *numCustomers) {
    FILE *file = fopen(CUSTOMER_FILENAME, "r");
    if (!file) {
        *numCustomers = 0;
        return;
    }

    *numCustomers = 0;
    while (fscanf(file, "Customer Name: %49[^|]| Phone Number: %14[^\n]\n", customers[*numCustomers].name, customers[*numCustomers].phone) != EOF) {
        (*numCustomers)++;
    }

    fclose(file);
}

void saveCustomer(const Customer *customer) {
    FILE *file = fopen(CUSTOMER_FILENAME, "a");
    if (!file) {
        printf("Error: Unable to open customer file for appending.\n");
        return;
    }
    
    fprintf(file, "Customer Name: %-20s | Phone Number: %s\n", customer->name, customer->phone);
    fclose(file);
}

void saveTransaction(const Transaction *transaction) {
    FILE *file = fopen(TRANSACTION_FILENAME, "a");
    if (!file) {
        printf("Error: Unable to open transaction file for appending.\n");
        return;
    }
    
    fprintf(file, "Phone Number: %-15s | Item ID: %d | Quantity: %d | Total Price: %.2f\n", transaction->phone, transaction->item_id, transaction->quantity, transaction->total_price);
    fclose(file);
}

void sellItem(Item items[], int numItems, Customer customers[], int *numCustomers, float sellingPrices[]) {
    int itemId, quantity;
    char customerPhone[15], customerName[50];

    printf("Enter Customer Phone Number: ");
    scanf("%s", customerPhone);

    int customerIndex = findCustomerIndex(customers, *numCustomers, customerPhone);
    if (customerIndex == -1) {
        printf("New Customer! Enter Customer Name: ");
        scanf("%s", customerName);
        Customer newCustomer;
        strcpy(newCustomer.phone, customerPhone);
        strcpy(newCustomer.name, customerName);
        customers[*numCustomers] = newCustomer;
        saveCustomer(&newCustomer);
        (*numCustomers)++;
    } else {
        strcpy(customerName, customers[customerIndex].name);
        printf("Welcome back, %s\n", customerName);
    }

    printf("Enter Item ID: ");
    scanf("%d", &itemId);

    if (itemId < 1 || itemId > numItems) {
        printf("Invalid Item ID. Please try again.\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if (items[itemId - 1].quantity < quantity) {
        printf("Insufficient stock. Available quantity: %d\n", items[itemId - 1].quantity);
        return;
    }

    items[itemId - 1].quantity -= quantity;

    float totalPrice = sellingPrices[itemId - 1] * quantity;
    totalProfit += totalPrice;

    Transaction newTransaction;
    strcpy(newTransaction.phone, customerPhone);
    newTransaction.item_id = itemId;
    newTransaction.quantity = quantity;
    newTransaction.total_price = totalPrice;
    saveTransaction(&newTransaction);

    printf("Item sold successfully! Total Price: RM%.2f\n", totalPrice);
}

void displayEndOfDayReport(Item items[], int numItems) {
    FILE *file = fopen(TRANSACTION_FILENAME, "r");
    if (!file) {
        printf("No transactions recorded.\n");
        return;
    }

    float totalGrossProfitForDay = 0.0;
    float totalCostForDay = 0.0;

    printf("\n****** End of Day Report ******\n");
    printf("-------------------------------\n");

    char phone[15];
    int item_id, quantity;
    float total_price;
    while (fscanf(file, "Phone Number: %14[^|] | Item ID: %d | Quantity: %d | Total Price: %f\n", phone, &item_id, &quantity, &total_price) != EOF) {
        printf("Phone Number: %s | Item ID: %d | Quantity: %d | Total Price: RM%.2f\n", phone, item_id, quantity, total_price);

        float itemGrossProfit = items[item_id - 1].selling_price * quantity;
        float itemCost = items[item_id - 1].cost_price * quantity;

        totalGrossProfitForDay += itemGrossProfit;
        totalCostForDay += itemCost;
    }

    fclose(file);

    grossProfit = totalGrossProfitForDay;
    netProfit = grossProfit - totalCostForDay;

    printf("\nTotal Gross Profit for the Day: RM%.2f\n", grossProfit);
    printf("Total Net Profit for the Day: RM%.2f\n", netProfit);

    printf("\nItems Below Minimum Stock:\n");
    for (int i = 0; i < numItems; i++) {
        if (items[i].quantity < items[i].min_stock) {
            printf("Item ID: %d | Name: %s | Quantity: %d | Min Stock: %d\n", items[i].id, items[i].name, items[i].quantity, items[i].min_stock);
        }
    }

    saveProfitData(PROFIT_FILENAME, grossProfit, netProfit, totalRestockingCost, items, numItems);
}


void checkItemsBelowLimitAndRestock(Item items[], int numItems) {
    printf("\n---- Checking items below minimum stock ----\n");

    int restockNeeded = 0;

    for (int i = 0; i < numItems; i++) {
        if (items[i].quantity < items[i].min_stock) {
            restockNeeded = 1;
            printf("Item ID: %d | Name: %s | Quantity: %d | Min Stock: %d\n", items[i].id, items[i].name, items[i].quantity, items[i].min_stock);
        }
    }

    if (!restockNeeded) {
        printf("No items below minimum stock.\n");
        return;
    }

    char choice;
    for (int i = 0; i < numItems; i++) {
        if (items[i].quantity < items[i].min_stock) {
            printf("\nDo you want to restock Item ID %d (%s)? (Y/N): ", items[i].id, items[i].name);
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y') {
                int restockAmount = items[i].max_stock - items[i].quantity;
                items[i].quantity += restockAmount;
                printf("Restocked Item ID %d (%s) by %d units.\n", items[i].id, items[i].name, restockAmount);
            } else {
                printf("Skipping restock for Item ID %d (%s).\n", items[i].id, items[i].name);
            }
        }
    }
}


void saveProfitData(const char *filename, float grossProfit, float netProfit, float totalRestockingCost, Item items[], int numItems) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open profit data file for writing.\n");
        return;
    }

    fprintf(file, "Gross Profit: %.2f\n", grossProfit);
    fprintf(file, "Net Profit: %.2f\n", netProfit);
    fclose(file);
}

void loadProfitData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No previous profit data found. Starting fresh.\n");
        return;
    }

    fscanf(file, "Gross Profit: %f\n", &grossProfit);
    fscanf(file, "Net Profit: %f\n", &netProfit);
    fclose(file);
}

int main() {
    Item items[NUM_ITEMS];
    Customer customers[100];
    int numCustomers = 0;
    float sellingPrices[NUM_ITEMS]; // Store selling prices

    // Initialize items with sample data
    if (access(FILENAME, F_OK) == -1) {
        createSampleData(items, NUM_ITEMS);
        saveItemsToFile(FILENAME, items, NUM_ITEMS);
    } else {
        loadItemsFromFile(FILENAME, items, NUM_ITEMS);
    }

    // Create a backup of the original data
    createBackup(FILENAME, BACKUP_FILENAME);

    // Load customer data
    loadCustomers(customers, &numCustomers);

    // Load profit data
    loadProfitData(PROFIT_FILENAME);

    // Initialize selling prices
    for (int i = 0; i < NUM_ITEMS; i++) {
        sellingPrices[i] = items[i].selling_price;
    }

    int choice;
    while (1) {
        printf("\n****** Bintang Bulan Kiosk Menu ******\n");
        printf("-- BAJU RAYA ON TOP BRADER --\n\n");
        printf("1. Display All Items\n");
        printf("2. Sell Item\n");
        printf("3. End of Day Report\n");
        printf("4. Check Items Below Minimum Stock and Restock\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAllItems(items, NUM_ITEMS_LELAKI, NUM_ITEMS_PEREMPUAN, NUM_ITEMS_ACCESSORIES);
                break;
            case 2:
                sellItem(items, NUM_ITEMS, customers, &numCustomers, sellingPrices);
                break;
            case 3:
                displayEndOfDayReport(items, NUM_ITEMS);
                break;
            case 4:
                checkItemsBelowLimitAndRestock(items, NUM_ITEMS);
                saveItemsToFile(FILENAME, items, NUM_ITEMS);
                break;
            case 5:
                saveProfitData(PROFIT_FILENAME, grossProfit, netProfit, totalRestockingCost, items, NUM_ITEMS); // Save profit data before exiting
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
