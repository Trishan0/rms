#include <stdio.h>
#include "types.h"
#include "sales_report.h"

static SaleRecord sales[MAX_SALES];
static int salesCount = 0;

void initSales(void) {
    salesCount = 5;
    sales[0] = (SaleRecord){1, 24500.00f};
    sales[1] = (SaleRecord){2, 19800.00f};
    sales[2] = (SaleRecord){3, 22150.00f};
    sales[3] = (SaleRecord){4, 28700.00f};
    sales[4] = (SaleRecord){5, 17600.00f};
}

void addSalesRecord(void) {
    if (salesCount >= MAX_SALES) {
        printf("Sales storage is full.\n");
        return;
    }

    printf("Enter day number: ");
    scanf("%d", &sales[salesCount].day);
    printf("Enter sales amount: ");
    scanf("%f", &sales[salesCount].amount);
    salesCount++;

    printf("Sales record added successfully.\n");
}

static int searchSalesIndexByDay(int day) {
    for (int i = 0; i < salesCount; i++) {
        if (sales[i].day == day) return i;
    }
    return -1;
}

void searchSalesRecord(void) {
    int day;
    printf("Enter day number to search: ");
    scanf("%d", &day);

    int index = searchSalesIndexByDay(day);
    if (index == -1) {
        printf("Sales record not found.\n");
        return;
    }

    printf("Found: Day=%d | Amount=%.2f\n", sales[index].day, sales[index].amount);
}

void updateSalesRecord(void) {
    int day;
    printf("Enter day number to update: ");
    scanf("%d", &day);

    int index = searchSalesIndexByDay(day);
    if (index == -1) {
        printf("Sales record not found.\n");
        return;
    }

    printf("Enter new sales amount: ");
    scanf("%f", &sales[index].amount);
    printf("Sales record updated successfully.\n");
}

void deleteSalesRecord(void) {
    int day;
    printf("Enter day number to delete: ");
    scanf("%d", &day);

    int index = searchSalesIndexByDay(day);
    if (index == -1) {
        printf("Sales record not found.\n");
        return;
    }

    for (int i = index; i < salesCount - 1; i++) {
        sales[i] = sales[i + 1];
    }
    salesCount--;

    printf("Sales record deleted successfully.\n");
}

void displaySalesRecords(void) {
    if (salesCount == 0) {
        printf("No sales records available.\n");
        return;
    }

    printf("\n================ SALES RECORDS ================\n");
    printf("%-10s %-15s\n", "Day", "Amount");
    printf("--------------------------------------------\n");
    for (int i = 0; i < salesCount; i++) {
        printf("%-10d %-15.2f\n", sales[i].day, sales[i].amount);
    }
}

void bubbleSortSalesByAmount(void) {
    for (int i = 0; i < salesCount - 1; i++) {
        for (int j = 0; j < salesCount - i - 1; j++) {
            if (sales[j].amount > sales[j + 1].amount) {
                SaleRecord temp = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = temp;
            }
        }
    }

    printf("Sales records sorted by amount using bubble sort.\n");
    displaySalesRecords();
}

void totalDailySales(void) {
    float total = 0.0f;
    for (int i = 0; i < salesCount; i++) total += sales[i].amount;
    printf("Total daily sales: %.2f\n", total);
}

void averageSales(void) {
    if (salesCount == 0) {
        printf("Average sales: 0.00\n");
        return;
    }

    float total = 0.0f;
    for (int i = 0; i < salesCount; i++) total += sales[i].amount;
    printf("Average sales: %.2f\n", total / salesCount);
}

void highestSaleDay(void) {
    if (salesCount == 0) {
        printf("No sales records available.\n");
        return;
    }

    int maxIndex = 0;
    for (int i = 1; i < salesCount; i++) {
        if (sales[i].amount > sales[maxIndex].amount) maxIndex = i;
    }

    printf("Highest sale day: Day=%d | Amount=%.2f\n",
           sales[maxIndex].day, sales[maxIndex].amount);
}

void salesReportMenu(void) {
    int choice;
    do {
        printf("\n=== Sales Reports (Array) ===\n");
        printf("1. Add sales record\n");
        printf("2. Search sales record\n");
        printf("3. Update sales record\n");
        printf("4. Delete sales record\n");
        printf("5. Display sales records\n");
        printf("6. Sort sales by amount (Bubble Sort)\n");
        printf("7. Total daily sales\n");
        printf("8. Average sales\n");
        printf("9. Highest sale day\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addSalesRecord(); break;
            case 2: searchSalesRecord(); break;
            case 3: updateSalesRecord(); break;
            case 4: deleteSalesRecord(); break;
            case 5: displaySalesRecords(); break;
            case 6: bubbleSortSalesByAmount(); break;
            case 7: totalDailySales(); break;
            case 8: averageSales(); break;
            case 9: highestSaleDay(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
