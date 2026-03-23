#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "promo_cycle.h"

static Promo* last = NULL;
static Promo* current = NULL;

static Promo* findPromoById(int id, Promo** previous) {
    if (last == NULL) {
        if (previous != NULL) *previous = NULL;
        return NULL;
    }

    Promo* prev = last;
    Promo* cur = last->next;

    do {
        if (cur->id == id) {
            if (previous != NULL) *previous = prev;
            return cur;
        }
        prev = cur;
        cur = cur->next;
    } while (cur != last->next);

    if (previous != NULL) *previous = NULL;
    return NULL;
}

void addPromo(void) {
    Promo* node = (Promo*)malloc(sizeof(Promo));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter promo id: ");
    scanf("%d", &node->id);

    if (findPromoById(node->id, NULL) != NULL) {
        printf("Promo with this ID already exists.\n");
        free(node);
        return;
    }

    printf("Enter promo title: ");
    scanf(" %99[^\n]", node->title);

    if (last == NULL) {
        last = node;
        node->next = node;
        current = node;
    } else {
        node->next = last->next;
        last->next = node;
        last = node;
    }

    printf("Promo added successfully.\n");
}

void displayNextPromo(void) {
    if (last == NULL) {
        printf("\n  [!] No promos available.\n");
        return;
    }

    if (current == NULL) {
        current = last->next;
    } else {
        current = current->next;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------+\n");
    printf("  |                     NEXT ACTIVE PROMO                       |\n");
    printf("  +--------------+----------------------------------------------+\n");
    printf("  | Promo ID     | %-44d |\n", current->id);
    printf("  | Title        | %-44s |\n", current->title);
    printf("  +--------------+----------------------------------------------+\n");
}

void displayAllPromos(void) {
    if (last == NULL) {
        printf("\n  [!] No promos available.\n");
        return;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------------+\n");
    printf("  |                    PROMOTIONAL BANNER TABLE                       |\n");
    printf("  +----------+--------------------------------------------------------+\n");
    printf("  | Promo ID | Title                                                  |\n");
    printf("  +----------+--------------------------------------------------------+\n");

    Promo* cur = last->next;
    do {
        printf("  | %-8d | %-54s |\n",
               cur->id,
               cur->title);
        cur = cur->next;
    } while (cur != last->next);

    printf("  +----------+--------------------------------------------------------+\n");
}

void searchPromo(void) {
    int id;
    printf("Enter promo id to search: ");
    scanf("%d", &id);

    Promo* promo = findPromoById(id, NULL);
    if (promo == NULL) {
        printf("\n  [!] Promo not found.\n");
        return;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------+\n");
    printf("  |                    PROMO SEARCH RESULT                      |\n");
    printf("  +--------------+----------------------------------------------+\n");
    printf("  | Promo ID     | %-44d |\n", promo->id);
    printf("  | Title        | %-44s |\n", promo->title);
    printf("  +--------------+----------------------------------------------+\n");
}

void updatePromo(void) {
    int id;
    printf("Enter promo id to update: ");
    scanf("%d", &id);

    Promo* promo = findPromoById(id, NULL);
    if (promo == NULL) {
        printf("Promo not found.\n");
        return;
    }

    printf("Enter new promo title: ");
    scanf(" %99[^\n]", promo->title);
    printf("Promo updated successfully.\n");
}

void deletePromo(void) {
    int id;
    printf("Enter promo id to delete: ");
    scanf("%d", &id);

    Promo* prev = NULL;
    Promo* node = findPromoById(id, &prev);

    if (node == NULL) {
        printf("Promo not found.\n");
        return;
    }

    if (node == last && node == last->next) {
        free(node);
        last = NULL;
        current = NULL;
    } else {
        prev->next = node->next;
        if (node == last) last = prev;
        if (current == node) current = node->next;
        free(node);
    }

    printf("Promo deleted successfully.\n");
}

void countActivePromos(void) {
    if (last == NULL) {
        printf("Active promos: 0\n");
        return;
    }

    int count = 0;
    Promo* cur = last->next;
    do {
        count++;
        cur = cur->next;
    } while (cur != last->next);

    printf("Active promos: %d\n", count);
}

void promoCycleMenu(void) {
    int choice;
    do {
        printf("\n=== Promotional Banner Rotation (CLL) ===\n");
        printf("1. Add promo\n");
        printf("2. Display next promo\n");
        printf("3. Search promo\n");
        printf("4. Update promo\n");
        printf("5. Delete promo\n");
        printf("6. Count active promos\n");
        printf("7. Display all promos\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPromo(); break;
            case 2: displayNextPromo(); break;
            case 3: searchPromo(); break;
            case 4: updatePromo(); break;
            case 5: deletePromo(); break;
            case 6: countActivePromos(); break;
            case 7: displayAllPromos(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

static void preloadPromo(int id, const char* title) {
    Promo* node = (Promo*)malloc(sizeof(Promo));
    if (!node) return;
    node->id = id;
    strcpy(node->title, title);
    if (last == NULL) {
        last = node;
        node->next = node;
        current = node;
    } else {
        node->next = last->next;
        last->next = node;
        last = node;
    }
}

__attribute__((constructor))
static void preloadPromos(void) {
    preloadPromo(401, "Buy 1 Get 1 Free - Soap");
    preloadPromo(402, "Weekend Discount - Rice");
    preloadPromo(403, "Tea Pack 10 Percent Off");
}
