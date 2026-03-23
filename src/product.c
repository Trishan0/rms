#include <stdio.h>
#include <string.h>
#include "product.h"

static Product products[MAX_PRODUCTS];
static int productCount = 0;

void initProducts(void) {
    productCount = 5;

    products[0] = (Product){101, "Rice 1kg", 240.00f, 30};
    products[1] = (Product){102, "Milk Powder", 1290.00f, 12};
    products[2] = (Product){103, "Sugar 1kg", 260.00f, 25};
    products[3] = (Product){104, "Tea Pack", 480.00f, 18};
    products[4] = (Product){105, "Soap Bar", 150.00f, 40};
}

void addProduct(void) {
    if (productCount >= MAX_PRODUCTS) {
        printf("Product storage is full.\n");
        return;
    }

    Product p;
    printf("Enter product id: ");
    scanf("%d", &p.id);

    if (searchProductIndexById(p.id) != -1) {
        printf("Product with this ID already exists.\n");
        return;
    }

    printf("Enter product name: ");
    scanf(" %49[^\n]", p.name);
    printf("Enter price: ");
    scanf("%f", &p.price);
    printf("Enter quantity: ");
    scanf("%d", &p.quantity);

    products[productCount++] = p;
    printf("Product added successfully.\n");
}

int searchProductIndexById(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

void searchProduct(void) {
    int id;
    printf("Enter product id to search: ");
    scanf("%d", &id);

    int index = searchProductIndexById(id);
    if (index == -1) {
        printf("\n  [!] Product not found.\n");
        return;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------+\n");
    printf("  |                    PRODUCT SEARCH RESULT                    |\n");
    printf("  +--------------+----------------------------------------------+\n");
    printf("  | Product ID   | %-44d |\n", products[index].id);
    printf("  | Name         | %-44s |\n", products[index].name);
    printf("  | Price        | %-44.2f |\n", products[index].price);
    printf("  | Quantity     | %-44d |\n", products[index].quantity);
    printf("  +--------------+----------------------------------------------+\n");
}

void updateProduct(void) {
    int id;
    printf("Enter product id to update: ");
    scanf("%d", &id);

    int index = searchProductIndexById(id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    printf("Current -> %s | %.2f | %d\n", products[index].name, products[index].price, products[index].quantity);
    printf("Enter new price: ");
    scanf("%f", &products[index].price);
    printf("Enter new quantity: ");
    scanf("%d", &products[index].quantity);
    printf("Product updated successfully.\n");
}

void deleteProduct(void) {
    int id;
    printf("Enter product id to delete: ");
    scanf("%d", &id);

    int index = searchProductIndexById(id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    productCount--;
    printf("Product deleted successfully.\n");
}

void displayProducts(void) {
    if (productCount == 0) {
        printf("\n  [!] No products available.\n");
        return;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------------+\n");
    printf("  |                      PRODUCT INVENTORY TABLE                      |\n");
    printf("  +----------+--------------------------+------------+----------------+\n");
    printf("  | Product  | Name                     | Price      | Quantity       |\n");
    printf("  | ID       |                          |            |                |\n");
    printf("  +----------+--------------------------+------------+----------------+\n");

    for (int i = 0; i < productCount; i++) {
        printf("  | %-8d | %-24s | %-10.2f | %-14d |\n",
               products[i].id,
               products[i].name,
               products[i].price,
               products[i].quantity);
    }

    printf("  +----------+--------------------------+------------+----------------+\n");
}

void selectionSortProductsByPrice(void) {
    for (int i = 0; i < productCount - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < productCount; j++) {
            if (products[j].price < products[minIndex].price) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Product temp = products[i];
            products[i] = products[minIndex];
            products[minIndex] = temp;
        }
    }
    printf("Products sorted by price using selection sort.\n");
    displayProducts();
}

void totalItemsInStock(void) {
    int total = 0;
    for (int i = 0; i < productCount; i++) {
        total += products[i].quantity;
    }
    printf("Total items in stock: %d\n", total);
}

void totalInventoryValue(void) {
    float total = 0.0f;
    for (int i = 0; i < productCount; i++) {
        total += products[i].price * products[i].quantity;
    }
    printf("Total inventory value: %.2f\n", total);
}

void productMenu(void) {
    int choice;
    do {
        printf("\n=== Product Inventory (Array) ===\n");
        printf("1. Add product\n");
        printf("2. Search product\n");
        printf("3. Update product\n");
        printf("4. Delete product\n");
        printf("5. Display products\n");
        printf("6. Sort by price (Selection Sort)\n");
        printf("7. Total items in stock\n");
        printf("8. Total inventory value\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: searchProduct(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: displayProducts(); break;
            case 6: selectionSortProductsByPrice(); break;
            case 7: totalItemsInStock(); break;
            case 8: totalInventoryValue(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
