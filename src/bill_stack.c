#include <stdio.h>
#include <string.h>
#include "types.h"
#include "bill_stack.h"

static BillStack bill;

void initBillStack(void) {
    bill.top = 2;
    bill.items[0] = (BillItem){101, "Rice 1kg", 240.00f, 2};
    bill.items[1] = (BillItem){105, "Soap Bar", 150.00f, 3};
    bill.items[2] = (BillItem){104, "Tea Pack", 480.00f, 1};
}

static int isStackEmpty(void) {
    return bill.top == -1;
}

static int isStackFull(void) {
    return bill.top == MAX_STACK - 1;
}

void pushScannedItem(void) {
    if (isStackFull()) {
        printf("Bill stack is full.\n");
        return;
    }

    BillItem item;
    printf("Enter product id: ");
    scanf("%d", &item.productId);
    printf("Enter product name: ");
    scanf(" %49[^\n]", item.productName);
    printf("Enter price: ");
    scanf("%f", &item.price);
    printf("Enter quantity: ");
    scanf("%d", &item.qty);

    bill.top++;
    bill.items[bill.top] = item;
    printf("Item pushed to current bill.\n");
}

void popLastItem(void) {
    if (isStackEmpty()) {
        printf("Bill stack is empty.\n");
        return;
    }

    BillItem item = bill.items[bill.top--];
    printf("Last item removed: ID=%d | Name=%s | Price=%.2f | Qty=%d\n",
           item.productId, item.productName, item.price, item.qty);
}

void peekLatestItem(void) {
    if (isStackEmpty()) {
        printf("Bill stack is empty.\n");
        return;
    }

    BillItem item = bill.items[bill.top];
    printf("Latest item: ID=%d | Name=%s | Price=%.2f | Qty=%d\n",
           item.productId, item.productName, item.price, item.qty);
}

void displayCurrentBillStack(void) {
    if (isStackEmpty()) {
        printf("Bill stack is empty.\n");
        return;
    }

    printf("\n============= CURRENT BILL STACK =============\n");
    printf("%-6s %-20s %-10s %-8s\n", "ID", "Name", "Price", "Qty");
    printf("----------------------------------------------\n");
    for (int i = bill.top; i >= 0; i--) {
        printf("%-6d %-20s %-10.2f %-8d\n",
               bill.items[i].productId,
               bill.items[i].productName,
               bill.items[i].price,
               bill.items[i].qty);
    }
}

void currentBillTotal(void) {
    float total = 0.0f;
    for (int i = 0; i <= bill.top; i++) {
        total += bill.items[i].price * bill.items[i].qty;
    }
    printf("Current bill total: %.2f\n", total);
}

void billStackMenu(void) {
    int choice;
    do {
        printf("\n=== Undo Last Item in Current Bill (Stack) ===\n");
        printf("1. Push scanned item\n");
        printf("2. Pop last item\n");
        printf("3. Peek latest item\n");
        printf("4. Display current bill stack\n");
        printf("5. Current bill total\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: pushScannedItem(); break;
            case 2: popLastItem(); break;
            case 3: peekLatestItem(); break;
            case 4: displayCurrentBillStack(); break;
            case 5: currentBillTotal(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
