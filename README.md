# Project-Stock

This code is a simple inventory management system for a shop that sells various items like Nasi Goreng (fried rice), drinks, and desserts. Let's break down its functionality:

    Struct Definition (StokItem): This defines a structure representing an item in the inventory. It includes fields like code, name, stock level, minimum stock, maximum stock, buy price, and sell price.

    Data Initialization: Three arrays of StokItem structs are initialized: nasiGorengVariations, airVariations, and dessertVariations. Each array holds different variations of items like different types of Nasi Goreng, drinks, and desserts, along with their respective properties.

    File Handling Functions:
        readStockLevels(): Reads stock levels from a file (stock.txt) and updates the stock levels of the items accordingly.
        writeStockLevels(): Writes the current stock levels of items back to the file.
        writeDataStock(): Writes detailed information about items (name, stock level, min/max stock, buy/sell prices) to another file (datastock.txt).

    Menu Display Functions:
        displayMenu(): Displays the main menu with options to view different categories of items.
        NasiGorengMenu(), AirMenu(), DessertMenu(): Display menus for specific categories with their respective items and stock levels.

    Order Processing Function (processOrder()): Takes an order for a specific item, deducts the quantity from stock if available, and records the order details along with updating the stock levels. It also checks if the requested quantity exceeds the available stock.

    Stock Update Function (updateStock()): Allows updating the stock levels of items. It displays sub-menus for each category, allowing the user to select a specific variation and update its stock level.

    Main Function (main()): It's the entry point of the program. It repeatedly displays the main menu, reads user input, and calls appropriate functions based on the user's selection until the user chooses to exit.
