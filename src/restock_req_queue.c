#include <stdio.h>
#include <string.h>
#include "types.h"
#include "restock_req_queue.h"

static RestockQueue restockQueue;

void initQueue(void) {
    restockQueue.front = 0;
    restockQueue.rear = 2;

    restockQueue.items[0] = (RestockRequest){101, "Rice 1kg", 20};
    restockQueue.items[1] = (RestockRequest){102, "Milk Powder", 10};
    restockQueue.items[2] = (RestockRequest){104, "Tea Pack", 15};
}

static int isQueueEmpty(void) {
    return restockQueue.front > restockQueue.rear;
}

static int isQueueFull(void) {
    return restockQueue.rear == MAX_QUEUE - 1;
}

void enqueueRestockRequest(void) {
    if (isQueueFull()) {
        printf("Restock request queue is full.\n");
        return;
    }

    RestockRequest r;
    printf("Enter product id: ");
    scanf("%d", &r.productId);
    printf("Enter product name: ");
    scanf(" %49[^\n]", r.productName);
    printf("Enter requested quantity: ");
    scanf("%d", &r.requestedQty);

    RestockQueue.rear++;
    RestockQueue.items[RestockQueue.rear] = r;
    printf("Restock request added successfully.\n");
}

void dequeueRestockRequest(void) {
    if (isQueueEmpty()) {
        printf("No pending restock requests.\n");
        return;
    }

    RestockRequest r = RestockQueue.items[RestockQueue.front++];
    printf("Processed restock request: ID=%d | Name=%s | Qty=%d\n",
           r.productId, r.productName, r.requestedQty);
}

void frontRestockRequest(void) {
    if (isQueueEmpty()) {
        printf("\n  [!] No pending restock requests.\n");
        return;
    }

    RestockRequest r = queueData.items[queueData.front];

    printf("\n");
    printf("  +-------------------------------------------------------------+\n");
    printf("  |                  FRONT RESTOCK REQUEST                      |\n");
    printf("  +--------------+----------------------------------------------+\n");
    printf("  | Product ID   | %-44d |\n", r.productId);
    printf("  | Product Name | %-44s |\n", r.productName);
    printf("  | Request Qty  | %-44d |\n", r.requestedQty);
    printf("  +--------------+----------------------------------------------+\n");
}

void displayRestockRequests(void) {
    if (isQueueEmpty()) {
        printf("\n  [!] No pending restock requests.\n");
        return;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------------+\n");
    printf("  |                    RESTOCK REQUEST QUEUE TABLE                    |\n");
    printf("  +------------+--------------------------+---------------------------+\n");
    printf("  | Product ID | Product Name             | Requested Quantity        |\n");
    printf("  +------------+--------------------------+---------------------------+\n");

    for (int i = queueData.front; i <= queueData.rear; i++) {
        printf("  | %-10d | %-24s | %-25d |\n",
               queueData.items[i].productId,
               queueData.items[i].productName,
               queueData.items[i].requestedQty);
    }

    printf("  +------------+--------------------------+---------------------------+\n");
}

void searchRestockRequest(void) {
    if (isQueueEmpty()) {
        printf("\n  [!] No pending restock requests.\n");
        return;
    }

    int productId;
    printf("Enter product id to search: ");
    scanf("%d", &productId);

    for (int i = queueData.front; i <= queueData.rear; i++) {
        if (queueData.items[i].productId == productId) {
            printf("\n");
            printf("  +-------------------------------------------------------------+\n");
            printf("  |                RESTOCK REQUEST SEARCH RESULT                |\n");
            printf("  +--------------+----------------------------------------------+\n");
            printf("  | Product ID   | %-44d |\n", queueData.items[i].productId);
            printf("  | Product Name | %-44s |\n", queueData.items[i].productName);
            printf("  | Request Qty  | %-44d |\n", queueData.items[i].requestedQty);
            printf("  +--------------+----------------------------------------------+\n");
            return;
        }
    }

    printf("\n  [!] Restock request not found.\n");
}
void countPendingRestockRequests(void) {
    if (isQueueEmpty()) {
        printf("Pending restock requests: 0\n");
        return;
    }

    printf("Pending restock requests: %d\n", RestockQueue.rear - RestockQueue.front + 1);
}

void totalRequestedQuantity(void) {
    if (isQueueEmpty()) {
        printf("Total requested quantity: 0\n");
        return;
    }

    int total = 0;
    for (int i = RestockQueue.front; i <= RestockQueue.rear; i++) {
        total += restockQueue.items[i].requestedQty;
    }
    printf("Total requested quantity: %d\n", total);
}

void restockQueueMenu(void) {
    int choice;
    do {
        printf("\n=== Restocking Request Management (Queue) ===\n");
        printf("1. Enqueue restock request\n");
        printf("2. Dequeue next request\n");
        printf("3. View front request\n");
        printf("4. Display pending requests\n");
        printf("5. Search request by product ID\n");
        printf("6. Count pending requests\n");
        printf("7. Total requested quantity\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: enqueueRestockRequest(); break;
            case 2: dequeueRestockRequest(); break;
            case 3: frontRestockRequest(); break;
            case 4: displayRestockRequests(); break;
            case 5: searchRestockRequest(); break;
            case 6: countPendingRestockRequests(); break;
            case 7: totalRequestedQuantity(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
