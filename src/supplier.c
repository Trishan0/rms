#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "supplier.h"

static Supplier* head = NULL;

static Supplier* findSupplierById(int id) {
    Supplier* cur = head;
    while (cur != NULL) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

void addSupplier(void) {
    Supplier* node = (Supplier*)malloc(sizeof(Supplier));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter supplier id: ");
    scanf("%d", &node->id);

    if (findSupplierById(node->id) != NULL) {
        printf("Supplier with this ID already exists.\n");
        free(node);
        return;
    }

    printf("Enter supplier name: ");
    scanf(" %49[^\n]", node->name);
    printf("Enter supplier phone: ");
    scanf(" %19s", node->phone);

    node->next = head;
    head = node;
    printf("Supplier added successfully.\n");
}

void searchSupplier(void) {
    int id;
    printf("Enter supplier id to search: ");
    scanf("%d", &id);

    Supplier* s = findSupplierById(id);
    if (s == NULL) {
        printf("Supplier not found.\n");
        return;
    }

    printf("Found: ID=%d | Name=%s | Phone=%s\n", s->id, s->name, s->phone);
}

void updateSupplier(void) {
    int id;
    printf("Enter supplier id to update: ");
    scanf("%d", &id);

    Supplier* s = findSupplierById(id);
    if (s == NULL) {
        printf("Supplier not found.\n");
        return;
    }

    printf("Enter new supplier name: ");
    scanf(" %49[^\n]", s->name);
    printf("Enter new supplier phone: ");
    scanf(" %19s", s->phone);
    printf("Supplier updated successfully.\n");
}

void deleteSupplier(void) {
    int id;
    printf("Enter supplier id to delete: ");
    scanf("%d", &id);

    Supplier* cur = head;
    Supplier* prev = NULL;

    while (cur != NULL && cur->id != id) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        printf("Supplier not found.\n");
        return;
    }

    if (prev == NULL) head = cur->next;
    else prev->next = cur->next;

    free(cur);
    printf("Supplier deleted successfully.\n");
}

void displaySuppliers(void) {
    if (head == NULL) {
        printf("No suppliers available.\n");
        return;
    }

    printf("\n================ SUPPLIER LIST ================\n");
    printf("%-6s %-20s %-15s\n", "ID", "Name", "Phone");
    printf("-----------------------------------------------\n");
    Supplier* cur = head;
    while (cur != NULL) {
        printf("%-6d %-20s %-15s\n", cur->id, cur->name, cur->phone);
        cur = cur->next;
    }
}

void countSuppliers(void) {
    int count = 0;
    Supplier* cur = head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    printf("Total suppliers: %d\n", count);
}

void supplierMenu(void) {
    int choice;
    do {
        printf("\n=== Supplier Management (SLL) ===\n");
        printf("1. Add supplier\n");
        printf("2. Search supplier\n");
        printf("3. Update supplier\n");
        printf("4. Delete supplier\n");
        printf("5. Display suppliers\n");
        printf("6. Count suppliers\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addSupplier(); break;
            case 2: searchSupplier(); break;
            case 3: updateSupplier(); break;
            case 4: deleteSupplier(); break;
            case 5: displaySuppliers(); break;
            case 6: countSuppliers(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

static void preloadOne(int id, const char* name, const char* phone) {
    Supplier* node = (Supplier*)malloc(sizeof(Supplier));
    if (!node) return;
    node->id = id;
    strcpy(node->name, name);
    strcpy(node->phone, phone);
    node->next = head;
    head = node;
}

__attribute__((constructor))
static void preloadSuppliers(void) {
    preloadOne(203, "Lanka Traders", "0771234567");
    preloadOne(202, "Fresh Foods Ltd", "0712345678");
    preloadOne(201, "Ceylon Distributors", "0769988776");
}
