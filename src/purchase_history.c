#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "purchase_history.h"

static Purchase* head = NULL;
static Purchase* tail = NULL;

static Purchase* findPurchaseByRecordId(int recordId) {
    Purchase* cur = head;
    while (cur != NULL) {
        if (cur->recordId == recordId) return cur;
        cur = cur->next;
    }
    return NULL;
}

void addPurchaseRecord(void) {
    Purchase* node = (Purchase*)malloc(sizeof(Purchase));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter record id: ");
    scanf("%d", &node->recordId);

    if (findPurchaseByRecordId(node->recordId) != NULL) {
        printf("Record ID already exists.\n");
        free(node);
        return;
    }

    printf("Enter customer id: ");
    scanf("%d", &node->customerId);
    printf("Enter customer name: ");
    scanf(" %49[^\n]", node->customerName);
    printf("Enter purchase amount: ");
    scanf("%f", &node->amount);

    node->prev = tail;
    node->next = NULL;

    if (tail != NULL) tail->next = node;
    else head = node;
    tail = node;

    printf("Purchase record added successfully.\n");
}

void searchPurchaseRecord(void) {
    int recordId;
    printf("Enter record id to search: ");
    scanf("%d", &recordId);

    Purchase* p = findPurchaseByRecordId(recordId);
    if (p == NULL) {
        printf("Purchase record not found.\n");
        return;
    }

    printf("Found: RecordID=%d | CustomerID=%d | Name=%s | Amount=%.2f\n",
           p->recordId, p->customerId, p->customerName, p->amount);
}

void updatePurchaseRecord(void) {
    int recordId;
    printf("Enter record id to update: ");
    scanf("%d", &recordId);

    Purchase* p = findPurchaseByRecordId(recordId);
    if (p == NULL) {
        printf("Purchase record not found.\n");
        return;
    }

    printf("Enter new customer name: ");
    scanf(" %49[^\n]", p->customerName);
    printf("Enter new amount: ");
    scanf("%f", &p->amount);
    printf("Purchase record updated successfully.\n");
}

void deletePurchaseRecord(void) {
    int recordId;
    printf("Enter record id to delete: ");
    scanf("%d", &recordId);

    Purchase* node = findPurchaseByRecordId(recordId);
    if (node == NULL) {
        printf("Purchase record not found.\n");
        return;
    }

    if (node->prev != NULL) node->prev->next = node->next;
    else head = node->next;

    if (node->next != NULL) node->next->prev = node->prev;
    else tail = node->prev;

    free(node);
    printf("Purchase record deleted successfully.\n");
}

void traversePurchasesForward(void) {
    if (head == NULL) {
        printf("No purchase records available.\n");
        return;
    }

    printf("\n============= PURCHASE HISTORY (FORWARD) =============\n");
    printf("%-8s %-10s %-20s %-10s\n", "RecID", "CustID", "Name", "Amount");
    printf("------------------------------------------------------\n");
    Purchase* cur = head;
    while (cur != NULL) {
        printf("%-8d %-10d %-20s %-10.2f\n",
               cur->recordId, cur->customerId, cur->customerName, cur->amount);
        cur = cur->next;
    }
}

void traversePurchasesBackward(void) {
    if (tail == NULL) {
        printf("No purchase records available.\n");
        return;
    }

    printf("\n============= PURCHASE HISTORY (BACKWARD) =============\n");
    printf("%-8s %-10s %-20s %-10s\n", "RecID", "CustID", "Name", "Amount");
    printf("-------------------------------------------------------\n");
    Purchase* cur = tail;
    while (cur != NULL) {
        printf("%-8d %-10d %-20s %-10.2f\n",
               cur->recordId, cur->customerId, cur->customerName, cur->amount);
        cur = cur->prev;
    }
}

void totalPurchasesByCustomer(void) {
    int customerId;
    float total = 0.0f;
    int found = 0;

    printf("Enter customer id: ");
    scanf("%d", &customerId);

    Purchase* cur = head;
    while (cur != NULL) {
        if (cur->customerId == customerId) {
            total += cur->amount;
            found = 1;
        }
        cur = cur->next;
    }

    if (!found) {
        printf("No purchase records found for customer ID %d.\n", customerId);
        return;
    }

    printf("Total purchases by customer %d: %.2f\n", customerId, total);
}

void purchaseHistoryMenu(void) {
    int choice;
    do {
        printf("\n=== Customer Purchase History (DLL) ===\n");
        printf("1. Add purchase record\n");
        printf("2. Search purchase record\n");
        printf("3. Update purchase record\n");
        printf("4. Delete purchase record\n");
        printf("5. Traverse forward\n");
        printf("6. Traverse backward\n");
        printf("7. Total purchases by customer\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPurchaseRecord(); break;
            case 2: searchPurchaseRecord(); break;
            case 3: updatePurchaseRecord(); break;
            case 4: deletePurchaseRecord(); break;
            case 5: traversePurchasesForward(); break;
            case 6: traversePurchasesBackward(); break;
            case 7: totalPurchasesByCustomer(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

static void preloadRecord(int recordId, int customerId, const char* name, float amount) {
    Purchase* node = (Purchase*)malloc(sizeof(Purchase));
    if (!node) return;
    node->recordId = recordId;
    node->customerId = customerId;
    strcpy(node->customerName, name);
    node->amount = amount;
    node->prev = tail;
    node->next = NULL;
    if (tail) tail->next = node;
    else head = node;
    tail = node;
}

__attribute__((constructor))
static void preloadPurchases(void) {
    preloadRecord(301, 1, "Nimal", 2450.00f);
    preloadRecord(302, 2, "Kasuni", 1890.00f);
    preloadRecord(303, 1, "Nimal", 760.00f);
    preloadRecord(304, 3, "Tharindu", 3320.00f);
}
