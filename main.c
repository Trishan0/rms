#include <stdio.h>
#include "product.h"
#include "supplier.h"
#include "purchase_history.h"
#include "restock_req_queue.h"
#include "bill_stack.h"
#include "promo_cycle.h"
#include "sales_report.h"

static void showDemoGuide(void) {
    printf("\n================ DEMO GUIDE ================\n");
    printf("Preloaded sample data is already available.\n");
    printf("Suggested demo flow:\n");
    printf("1 -> 5 : Display products\n");
    printf("1 -> 6 : Sort products by price\n");
    printf("2 -> 5 : Display suppliers\n");
    printf("3 -> 5 : Traverse purchase history forward\n");
    printf("4 -> 4 : Display restock request queue\n");
    printf("4 -> 7 : Show total requested quantity\n");
    printf("5 -> 4 : Display current bill stack\n");
    printf("5 -> 5 : Show current bill total\n");
    printf("6 -> 2 : Display next promo repeatedly\n");
    printf("7 -> 5 : Display sales records\n");
    printf("7 -> 9 : Highest sale day\n");
    printf("===========================================\n");
}

int main(void) {
    int choice;

    initProducts();
    initQueue();
    initBillStack();
    initSales();

    do {
        printf("\n========================================\n");
        printf("   SUPERMARKET / GROCERY STORE SYSTEM\n");
        printf("========================================\n");
        printf("1. Product Inventory (Array)\n");
        printf("2. Supplier Management (SLL)\n");
        printf("3. Customer Purchase History (DLL)\n");
        printf("4. Restocking Request Management (Queue)\n");
        printf("5. Undo Last Item in Current Bill (Stack)\n");
        printf("6. Promotional Banner Rotation (CLL)\n");
        printf("7. Sales Reports (Array)\n");
        printf("8. Show demo guide\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: productMenu(); break;
            case 2: supplierMenu(); break;
            case 3: purchaseHistoryMenu(); break;
            case 4: restockQueueMenu(); break;
            case 5: billStackMenu(); break;
            case 6: promoCycleMenu(); break;
            case 7: salesReportMenu(); break;
            case 8: showDemoGuide(); break;
            case 0: printf("Exiting system.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
