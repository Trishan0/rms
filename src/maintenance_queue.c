/* ================================================================
   maintenance_queue.c - Member 7 | Data Structure: QUEUE (2nd use)
   Module: Train Maintenance Queue
   ================================================================ */

#include <stdio.h>
#include <string.h>
#include "../include/maintenance_queue.h"

/* ---------- Global queue instance ---------- */
MaintenanceQueue maintQ;

/* ---------- Initialization ---------- */
static int initialized = 0;
static void ensureInit() {
    if (!initialized) {
        maintQ.front = 0;
        maintQ.rear  = -1;
        maintQ.count = 0;
        initialized  = 1;
    }
}

/* ---------- ID generator ---------- */
static int serviceIDCounter = 700;

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

int isMaintenanceQueueEmpty() { ensureInit(); return maintQ.count == 0; }
int isMaintenanceQueueFull()  { ensureInit(); return maintQ.count == MAX_MAINTENANCE; }

/* Submit a train for maintenance - enqueue at rear */
void enqueueForMaintenance() {
    ensureInit();
    if (isMaintenanceQueueFull()) {
        printf("[!] Maintenance queue is full.\n"); return;
    }
    MaintenanceRecord r;
    r.serviceID = ++serviceIDCounter;
    strcpy(r.status, "Pending");

    printf("\n--- Submit Train for Maintenance ---\n");
    printf("Train ID               : T"); scanf("%d", &r.trainID);
    printf("Train Name             : "); scanf(" %[^\n]", r.trainName);
    printf("Maintenance Type       : "); scanf(" %[^\n]", r.maintenanceType);
    printf("Assigned Depot         : "); scanf(" %[^\n]", r.assignedDepot);
    printf("Submitted At (time)    : "); scanf(" %[^\n]", r.submittedAt);
    printf("Notes / Work Needed    : "); scanf(" %[^\n]", r.notes);

    maintQ.rear = (maintQ.rear + 1) % MAX_MAINTENANCE;
    maintQ.records[maintQ.rear] = r;
    maintQ.count++;
    printf("[+] Service S%d submitted. T%d %s in queue. Position: %d\n",
           r.serviceID, r.trainID, r.trainName, maintQ.count);
}

/* Process next maintenance - dequeue from front */
void processNextMaintenance() {
    ensureInit();
    if (isMaintenanceQueueEmpty()) {
        printf("[!] Maintenance queue is empty.\n"); return;
    }
    MaintenanceRecord r = maintQ.records[maintQ.front];
    strcpy(maintQ.records[maintQ.front].status, "In Service");
    maintQ.front = (maintQ.front + 1) % MAX_MAINTENANCE;
    maintQ.count--;

    printf("\n[MAINTENANCE STARTED]\n");
    printf(DIVIDER);
    printf("  Service ID   : S%d\n",   r.serviceID);
    printf("  Train        : T%d - %s\n", r.trainID, r.trainName);
    printf("  Type         : %s\n",    r.maintenanceType);
    printf("  Depot        : %s\n",    r.assignedDepot);
    printf("  Submitted    : %s\n",    r.submittedAt);
    printf("  Notes        : %s\n",    r.notes);
    printf(DIVIDER);
    printf("[+] Service started. Remaining in queue: %d\n", maintQ.count);
}

/* Peek at next maintenance without dequeuing */
void peekNextMaintenance() {
    ensureInit();
    if (isMaintenanceQueueEmpty()) {
        printf("[!] Maintenance queue is empty.\n"); return;
    }
    MaintenanceRecord r = maintQ.records[maintQ.front];
    printf("\n[NEXT FOR MAINTENANCE]\n");
    printf(DIVIDER);
    printf("  S%d | T%d - %s\n",  r.serviceID, r.trainID, r.trainName);
    printf("  Type   : %s\n",     r.maintenanceType);
    printf("  Depot  : %s\n",     r.assignedDepot);
    printf("  Status : %s\n",     r.status);
    printf(DIVIDER);
}

/* Search maintenance queue by trainID */
void searchMaintenance() {
    ensureInit();
    if (isMaintenanceQueueEmpty()) {
        printf("[!] Queue is empty.\n"); return;
    }
    int tid;
    printf("Enter Train ID to search: T"); scanf("%d", &tid);
    int found = 0;
    for (int i = 0; i < maintQ.count; i++) {
        int idx          = (maintQ.front + i) % MAX_MAINTENANCE;
        MaintenanceRecord r = maintQ.records[idx];
        if (r.trainID == tid) {
            printf("  Pos:%-3d S%-4d | T%d - %-28s | %-12s | %s | %s\n",
                   i + 1, r.serviceID, r.trainID, r.trainName,
                   r.maintenanceType, r.assignedDepot, r.status);
            found = 1;
        }
    }
    if (!found) printf("[!] Train T%d not found in maintenance queue.\n", tid);
}

/* Display all pending maintenance entries */
void displayMaintenanceQueue() {
    ensureInit();
    if (isMaintenanceQueueEmpty()) {
        printf("[!] Maintenance queue is empty.\n"); return;
    }
    printf("\n%-4s %-6s %-6s %-28s %-14s %-20s %-10s\n",
           "Pos","SvcID","TrnID","Train Name","Type","Depot","Status");
    printf(DIVIDER);
    for (int i = 0; i < maintQ.count; i++) {
        int idx          = (maintQ.front + i) % MAX_MAINTENANCE;
        MaintenanceRecord r = maintQ.records[idx];
        printf("%-4d S%-5d T%-5d %-28s %-14s %-20s %-10s%s\n",
               i + 1, r.serviceID, r.trainID, r.trainName,
               r.maintenanceType, r.assignedDepot, r.status,
               (i == 0) ? " <- NEXT" : "");
    }
    printf(DIVIDER);
    printf("Queue: %d / %d\n", maintQ.count, MAX_MAINTENANCE);
}

/* Cancel a specific maintenance entry */
void cancelMaintenance() {
    ensureInit();
    if (isMaintenanceQueueEmpty()) {
        printf("[!] Queue is empty.\n"); return;
    }
    int sid;
    printf("Enter Service ID to cancel: S"); scanf("%d", &sid);

    int found = -1;
    for (int i = 0; i < maintQ.count; i++) {
        int idx = (maintQ.front + i) % MAX_MAINTENANCE;
        if (maintQ.records[idx].serviceID == sid) { found = i; break; }
    }
    if (found == -1) { printf("[!] Service S%d not found.\n", sid); return; }

    for (int i = found; i < maintQ.count - 1; i++) {
        int curr = (maintQ.front + i)     % MAX_MAINTENANCE;
        int next = (maintQ.front + i + 1) % MAX_MAINTENANCE;
        maintQ.records[curr] = maintQ.records[next];
    }
    maintQ.rear = (maintQ.rear - 1 + MAX_MAINTENANCE) % MAX_MAINTENANCE;
    maintQ.count--;
    printf("[+] Service S%d cancelled and removed.\n", sid);
}
/* ================================================================
   EXTRA FUNCTION — findPositionInQueue()
   TYPE: Search + positional lookup (FIFO safe)
   ================================================================ */
void findPositionInQueue() {
    ensureInit();
    if (isMaintenanceQueueEmpty()) {
        printf("[!] Queue is empty.\n"); return;
    }

    int tid;
    printf("Enter Train ID: T");
    scanf("%d", &tid);

    for (int i = 0; i < maintQ.count; i++) {
        int idx = (maintQ.front + i) % MAX_MAINTENANCE;

        if (maintQ.records[idx].trainID == tid) {
            printf("\n[POSITION FOUND]\n");
            printf("Train T%d is at position %d out of %d.\n", tid, i + 1, maintQ.count);
            printf("%d train(s) ahead in queue.\n", i);

            if (i == 0)
                printf("[+] This train is NEXT for maintenance.\n");

            return;
        }
    }

    printf("[!] Train T%d not found in queue.\n", tid);
}
/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
// void displayMaintenanceTable() {
//     ensureInit();
//     if (isMaintenanceQueueEmpty()) {
//         printf("[!] Maintenance queue is empty.\n"); return;
//     }
//     printf("\n╔═════╦════════╦════════╦══════════════════════════════╦══════════════╦════════════════════╦══════════╗\n");
//     printf("║ Pos ║  SvcID ║  TrnID ║ Train Name                   ║ Type         ║ Depot              ║ Status   ║\n");
//     printf("╠═════╬════════╬════════╬══════════════════════════════╬══════════════╬════════════════════╬══════════╣\n");
//     for (int i = 0; i < maintQ.count; i++) {
//         int idx          = (maintQ.front + i) % MAX_MAINTENANCE;
//         MaintenanceRecord r = maintQ.records[idx];
//         printf("║ %-3d ║ S%-5d ║ T%-5d ║ %-28s ║ %-12s ║ %-18s ║ %-8s ║%s\n",
//                i + 1, r.serviceID, r.trainID, r.trainName,
//                r.maintenanceType, r.assignedDepot, r.status,
//                (i == 0) ? "<-NEXT" : "");
//     }
//     printf("╚═════╩════════╩════════╩══════════════════════════════╩══════════════╩════════════════════╩══════════╝\n");
//     printf("Queue: %d / %d slots used\n", maintQ.count, MAX_MAINTENANCE);
// }

void displayMaintenanceTable() {
    ensureInit();

    if (isMaintenanceQueueEmpty()) {
        printf("\n  [!] Maintenance queue is empty.\n");
        return;
    }

    printf("\n");
    printf("  +------------------------------------------------------------------------------------------------------+\n");
    printf("  |                                   TRAIN MAINTENANCE QUEUE                                            |\n");
    printf("  +-----+--------+--------+------------------------------+--------------+------------------+----------+\n");
    printf("  | Pos | SvcID  | TrnID  | Train Name                   | Type         | Depot           | Status   |\n");
    printf("  +-----+--------+--------+------------------------------+--------------+------------------+----------+\n");

    for (int i = 0; i < maintQ.count; i++) {
        int idx = (maintQ.front + i) % MAX_MAINTENANCE;
        MaintenanceRecord r = maintQ.records[idx];

        printf("  | %-3d | S%-5d | T%-5d | %-28s | %-12s | %-16s | %-8s |%s\n",
               i + 1,
               r.serviceID,
               r.trainID,
               r.trainName,
               r.maintenanceType,
               r.assignedDepot,
               r.status,
               (i == 0) ? " <-NEXT" : "");
    }

    printf("  +-----+--------+--------+------------------------------+--------------+------------------+----------+\n");
    printf("  Queue: %d / %d slots used\n", maintQ.count, MAX_MAINTENANCE);
}

/* ================================================================
   SUB-MENU - Member 7
   ================================================================ */
void maintenanceQueueMenu() {
    ensureInit();
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       TRAIN MAINTENANCE QUEUE  [QUEUE]\n");
        printf("%s", HEADER);
        printf("  1.  Submit Train for Maintenance\n");
        printf("  2.  Process Next Maintenance\n");
        printf("  3.  Peek Next Maintenance\n");
        printf("  4.  Search by Train ID\n");
        printf("  5.  Display Maintenance Queue\n");
        printf("  6.  Cancel Maintenance\n");
        printf("  7.  Find Position in Queue  [EXTRA]\n");
        printf("  8.  Display Maintenance Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: enqueueForMaintenance();   break;
            case 2: processNextMaintenance();  break;
            case 3: peekNextMaintenance();     break;
            case 4: searchMaintenance();       break;
            case 5: displayMaintenanceQueue(); break;
            case 6: cancelMaintenance();       break;
            case 7: findPositionInQueue();     break;
            case 8: displayMaintenanceTable(); break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
