# Bintang Bulan Kiosk Management System

The Bintang Bulan Kiosk Management System is a C programming language-based application designed to manage the daily operations of a kiosk selling traditional Malay clothing and accessories. The system provides features for displaying items, selling items, generating end-of-day reports, and restocking items below minimum stock levels.

# System Design: The system consists of several modules, including:

- Item Management: This module is responsible for managing the inventory of items, including loading sample data, saving items to a file, and displaying all items.
- Customer Management: This module manages customer data, including loading customer data from a file and saving new customer information.
- Transaction Management: This module handles sales transactions, including selling items, calculating total prices, and saving transaction data to a file.
- Reporting: This module generates end-of-day reports, including calculating gross and net profits, and displaying items below minimum stock levels.
- Restocking: This module checks for items below minimum stock levels and allows the user to restock items.

# System Flow: The system flow is as follows:

- The system initializes by loading sample data, customer data, and profit data from files.
- The user is presented with a menu to choose from:

        - Display All Items
        - Sell Item
        - End of Day Report
        - Check Items Below Minimum Stock and Restock
        - Exit
  
- Based on the user's choice, the system performs the corresponding action:

        - Display All Items: displays all items in the inventory.
        - Sell Item: sells an item, calculates the total price, and saves the transaction data.
        - End of Day Report: generates an end-of-day report, including calculating gross and net profits.
        - Check Items Below Minimum Stock and Restock: checks for items below minimum stock levels and allows the user to restock items.
        - Exit: saves profit data and exits the system.

# Pseudocode 

    // Initialize variables and data structures
    ITEMS = loadItemsFromFile("myKdata.txt")
    CUSTOMERS = loadCustomersFromFile("customers.txt")
    TRANSACTIONS = []

    WHILE true
    DISPLAY MENU
    "1. Display All Items"
    "2. Sell Item"
    "3. End-of-Day Report"
    "4. Check Items Below Minimum Stock and Restock"
    "5. Exit"

    READ USER CHOICE

    IF USER CHOICE == 1
    ITEMS = loadSampleData()
    DISPLAY "Sample data loaded successfully!"

    ELSE IF USER CHOICE == 2
    DISPLAY ALL ITEMS IN ITEMS

    ELSE IF USER CHOICE == 3
    DISPLAY "Enter item ID to sell: "
    
    READ ITEM ID
    IF ITEM ID IS VALID
    ITEM = findItemInList(ITEMS, ITEM ID)
    IF ITEM IS NOT NULL
    DISPLAY "Enter quantity to sell: "
    
    READ QUANTITY
    IF QUANTITY IS VALID
    TRANSACTION = createTransaction(ITEM, QUANTITY)
    ADD TRANSACTION TO TRANSACTIONS
    DISPLAY "Transaction successful!"
    ELSE
    DISPLAY "Invalid quantity. Please try again."
    ELSE
    DISPLAY "Item not found. Please try again."
    ELSE
    DISPLAY "Invalid item ID. Please try again."

    ELSE IF USER CHOICE == 4
    GENERATE END-OF-DAY REPORT
    DISPLAY REPORT

    ELSE IF USER CHOICE == 5
    DISPLAY "Enter item ID to restock: "
    
    READ ITEM ID
    IF ITEM ID IS VALID
    ITEM = findItemInList(ITEMS, ITEM ID)
    IF ITEM IS NOT NULL
    DISPLAY "Enter quantity to restock: "
    
    READ QUANTITY
    IF QUANTITY IS VALID
    RESTOCK ITEM WITH QUANTITY
    DISPLAY "Item restocked successfully!"
    ELSE
    DISPLAY "Invalid quantity. Please try again."
    ELSE
    DISPLAY "Item not found. Please try again."
    ELSE
    DISPLAY "Invalid item ID. Please try again."

    ELSE IF USER CHOICE == 5
    SAVE ITEMS TO FILE("myKdata.txt")
    SAVE CUSTOMERS TO FILE("customers.txt")
    SAVE TRANSACTIONS TO FILE("transactions.txt")
    EXIT PROGRAM

    ELSE
    DISPLAY "Invalid choice. Please try again."
  
# Flow Chart  
  ![FlowChart-Stok](https://github.com/naifmuazzam/Project-Stock/assets/87623760/185c1a87-8059-4a59-a574-27c0121c9e30)


# Conclusion: 
The Bintang Bulan Kiosk Management System is a comprehensive application that provides features for managing the daily operations of a kiosk selling traditional Malay clothing and accessories. The system is well-designed and easy to use, but there are  areas for improvement, such as error handling and code organization.

# Usage
- Compile and Run:
- Navigate to the directory containing the source code.
- Compile the code using a C compiler such as GCC:
`gcc stok1.c -o stok1`
- run the executable:
`./stok1`

        Compile the code and run the executable.
        The program will create a sample data file MyKdata.txt if it doesn't exist already.
        The program will also create a backup of the original data file MyKdata.ori.

- Menu Options

The program will display a menu with the following options:

            Display All Items: Displays all items in the inventory, categorized by Lelaki, Perempuan, and Accessories.
            Sell Item: Allows you to sell an item to a customer.
            End of Day Report: Displays a report of all transactions made during the day, including gross profit and net profit.
            Check Items Below Minimum Stock and Restock: Checks for items that are below the minimum stock level and allows you to restock them.
            Exit: Exits the program and saves the profit data.

Selling an Item

    Choose option 2: Sell Item.
    Enter the customer's phone number.
    If the customer is new, enter their name.
    Enter the item ID you want to sell.
    Enter the quantity you want to sell.
    The program will update the inventory and display the total price.

End of Day Report

    Choose option 3: End of Day Report.
    The program will display a report of all transactions made during the day, including gross profit and net profit.

Restocking Items

    Choose option 4: Check Items Below Minimum Stock and Restock.
    The program will display a list of items that are below the minimum stock level.
    For each item, you can choose to restock it by entering 'Y' or skip it by entering 'N'.
    The program will update the inventory accordingly.

Exiting the Program

    Choose option 5: Exit.
    The program will save the profit data and exit.

Note: This program uses files to store data, so make sure to run it in a directory where you have write permissions.
