/* ================================================================
   train_fleet.c - Member 1 | Data Structure: ARRAY
   Module: Train Fleet Registry
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/train_fleet.h"

/* ---------- Global array & counter ---------- */
Train fleet[MAX_TRAINS];
int   trainCount = 0;

/* ---------- ID generator ---------- */
static int idCounter = 100;
static int generateTrainID() { return ++idCounter; }

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

/* Check if fleet array is full */
int isFleetFull()  { return trainCount >= MAX_TRAINS; }

/* Check if fleet array is empty */
int isFleetEmpty() { return trainCount == 0; }

/* Register a new train into the fleet array */
void addTrain() {
    if (isFleetFull()) {
        printf("[!] Fleet is at maximum capacity (%d trains).\n", MAX_TRAINS);
        return;
    }
    Train t;
    t.trainID     = generateTrainID();
    t.currentLoad = 0;

    printf("\n--- Register New Train ---\n");
    printf("Train Name (e.g. Udarata Menike) : "); scanf(" %[^\n]", t.trainName);
    printf("Train Type (Express/Intercity/Local): "); scanf(" %[^\n]", t.trainType);
    printf("Seat Capacity                    : "); scanf("%d", &t.seatCapacity);
    printf("Home Depot                       : "); scanf(" %[^\n]", t.depot);
    printf("Assigned Route                   : "); scanf(" %[^\n]", t.assignedRoute);
    strcpy(t.status, "Active");

    fleet[trainCount++] = t;
    printf("[+] Train registered. ID: T%d | %s\n", t.trainID, t.trainName);
}

/* Remove a train from the fleet by trainID */
void removeTrain() {
    if (isFleetEmpty()) { printf("[!] Fleet is empty.\n"); return; }
    int id;
    printf("\nEnter Train ID to remove: T"); scanf("%d", &id);

    int found = -1;
    for (int i = 0; i < trainCount; i++) {
        if (fleet[i].trainID == id) { found = i; break; }
    }
    if (found == -1) { printf("[!] Train T%d not found.\n", id); return; }

    printf("[+] Removing: %s (T%d)\n", fleet[found].trainName, id);
    for (int i = found; i < trainCount - 1; i++)
        fleet[i] = fleet[i + 1];
    trainCount--;
    printf("[+] Train removed. Fleet size: %d\n", trainCount);
}

/* Update train information */
void updateTrainInfo() {
    if (isFleetEmpty()) { printf("[!] Fleet is empty.\n"); return; }
    int id;
    printf("\nEnter Train ID to update: T"); scanf("%d", &id);

    Train* t = findTrainByID(id);
    if (!t) { printf("[!] Train T%d not found.\n", id); return; }

    printf("Update:\n  1. Status\n  2. Seat Capacity\n"
           "  3. Depot\n  4. Current Load\nChoice: ");
    int ch; scanf("%d", &ch);
    switch (ch) {
        case 1: printf("New status (Active/Maintenance/Retired): ");
                scanf(" %[^\n]", t->status); break;
        case 2: printf("New capacity: "); scanf("%d", &t->seatCapacity); break;
        case 3: printf("New depot: "); scanf(" %[^\n]", t->depot); break;
        case 4: printf("Current passenger load: "); scanf("%d", &t->currentLoad); break;
        default: printf("[!] Invalid choice.\n"); return;
    }
    printf("[+] Train T%d updated.\n", id);
}

/* Search train by ID or name */
void searchTrain() {
    if (isFleetEmpty()) { printf("[!] Fleet is empty.\n"); return; }
    printf("\nSearch by:\n  1. Train ID\n  2. Name\nChoice: ");
    int ch; scanf("%d", &ch);
    int found = 0;

    if (ch == 1) {
        int id; printf("Enter Train ID: T"); scanf("%d", &id);
        for (int i = 0; i < trainCount; i++) {
            if (fleet[i].trainID == id) {
                printf(DIVIDER);
                printf("  ID       : T%d\n",   fleet[i].trainID);
                printf("  Name     : %s\n",     fleet[i].trainName);
                printf("  Type     : %s\n",     fleet[i].trainType);
                printf("  Capacity : %d seats\n",fleet[i].seatCapacity);
                printf("  Load     : %d passengers\n",fleet[i].currentLoad);
                printf("  Status   : %s\n",     fleet[i].status);
                printf("  Depot    : %s\n",     fleet[i].depot);
                printf("  Route    : %s\n",     fleet[i].assignedRoute);
                printf(DIVIDER);
                found = 1; break;
            }
        }
    } else {
        char name[NAME_LEN];
        printf("Enter train name: "); scanf(" %[^\n]", name);
        for (int i = 0; i < trainCount; i++) {
            if (strstr(fleet[i].trainName, name)) {
                printf("  T%-4d | %-30s | %-12s | %d seats | %s\n",
                       fleet[i].trainID, fleet[i].trainName,
                       fleet[i].trainType, fleet[i].seatCapacity,
                       fleet[i].status);
                found = 1;
            }
        }
    }
    if (!found) printf("[!] No matching train found.\n");
}

/* Display all trains in the fleet */
void displayFleet() {
    if (isFleetEmpty()) { printf("[!] Fleet is empty.\n"); return; }
    printf("\n%-6s %-30s %-12s %-8s %-8s %-12s\n",
           "ID","Name","Type","Seats","Load","Status");
    printf(DIVIDER);
    for (int i = 0; i < trainCount; i++) {
        printf("T%-5d %-30s %-12s %-8d %-8d %-12s\n",
               fleet[i].trainID, fleet[i].trainName,
               fleet[i].trainType, fleet[i].seatCapacity,
               fleet[i].currentLoad, fleet[i].status);
    }
    printf(DIVIDER);
    printf("Total trains: %d / %d\n", trainCount, MAX_TRAINS);
}

/* ================================================================
   SORT - BUBBLE SORT by Seat Capacity (high → low)
   ================================================================ */
void bubbleSortByCapacity() {
    if (trainCount < 2) { printf("[!] Not enough trains to sort.\n"); return; }
    Train temp;
    int swapped;
    for (int i = 0; i < trainCount - 1; i++) {
        swapped = 0;
        for (int j = 0; j < trainCount - i - 1; j++) {
            if (fleet[j].seatCapacity < fleet[j+1].seatCapacity) {
                temp       = fleet[j];
                fleet[j]   = fleet[j+1];
                fleet[j+1] = temp;
                swapped    = 1;
            }
        }
        if (!swapped) break;
    }
    printf("[+] Fleet sorted by seat capacity (Highest → Lowest).\n");
    displayFleet();
}

/* ================================================================
   EXTRA FUNCTION - calculateTotalSeatCapacity()
   TYPE: Aggregate SUM across entire array
   Traverses full fleet array summing all seatCapacity values.
   Answers: "What is the total passenger capacity of the fleet?"
   ================================================================ */
void calculateTotalSeatCapacity() {
    if (isFleetEmpty()) { printf("[!] Fleet is empty.\n"); return; }
    int total = 0;
    int active = 0;
    for (int i = 0; i < trainCount; i++) {
        total += fleet[i].seatCapacity;
        if (strcmp(fleet[i].status, "Active") == 0)
            active += fleet[i].seatCapacity;
    }
    printf("\n========== TOTAL SEAT CAPACITY ==========\n");
    printf("  All trains (fleet total) : %d seats\n", total);
    printf("  Active trains only       : %d seats\n", active);
    printf("  Trains in fleet          : %d\n", trainCount);
    printf("  Average per train        : %.1f seats\n",
           (float)total / trainCount);
    printf("==========================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
// void displayFleetTable() {
//     if (isFleetEmpty()) { printf("[!] Fleet is empty.\n"); return; }
//     printf("\n╔═══════╦══════════════════════════════╦════════════╦═══════╦══════╦════════════╗\n");
//     printf("║  ID   ║ Train Name                   ║ Type       ║ Seats ║ Load ║ Status     ║\n");
//     printf("╠═══════╬══════════════════════════════╬════════════╬═══════╬══════╬════════════╣\n");
//     for (int i = 0; i < trainCount; i++) {
//         printf("║ T%-4d ║ %-28s ║ %-10s ║ %-5d ║ %-4d ║ %-10s ║\n",
//                fleet[i].trainID, fleet[i].trainName,
//                fleet[i].trainType, fleet[i].seatCapacity,
//                fleet[i].currentLoad, fleet[i].status);
//     }
//     printf("╚═══════╩══════════════════════════════╩════════════╩═══════╩══════╩════════════╝\n");
//     printf("Fleet: %d / %d trains registered\n", trainCount, MAX_TRAINS);
// }

void displayFleetTable() {
    if (isFleetEmpty()) {
        printf("\n  [!] Fleet is empty.\n");
        return;
    }

    printf("\n");
    printf("  +-------------------------------------------------------------------------------------------+\n");
    printf("  |                                   TRAIN FLEET REGISTRY                                   |\n");
    printf("  +--------+------------------------------+------------+-------+------+------------+\n");
    printf("  |  ID    | Train Name                   | Type       | Seats | Load | Status     |\n");
    printf("  +--------+------------------------------+------------+-------+------+------------+\n");

    for (int i = 0; i < trainCount; i++) {
        printf("  | T%-5d | %-28s | %-10s | %-5d | %-4d | %-10s |\n",
               fleet[i].trainID,
               fleet[i].trainName,
               fleet[i].trainType,
               fleet[i].seatCapacity,
               fleet[i].currentLoad,
               fleet[i].status);
    }

    printf("  +--------+------------------------------+------------+-------+------+------------+\n");
    printf("  Fleet: %d / %d trains registered\n", trainCount, MAX_TRAINS);
}

/* Helper: find train by ID (used by other modules) */
Train* findTrainByID(int id) {
    for (int i = 0; i < trainCount; i++)
        if (fleet[i].trainID == id) return &fleet[i];
    return NULL;
}

/* ================================================================
   SUB-MENU - Member 1
   ================================================================ */
void trainFleetMenu() {
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       TRAIN FLEET REGISTRY  [ARRAY]\n");
        printf("%s", HEADER);
        printf("  1.  Add Train\n");
        printf("  2.  Remove Train\n");
        printf("  3.  Update Train Info\n");
        printf("  4.  Search Train\n");
        printf("  5.  Display Fleet\n");
        printf("  6.  Sort by Capacity  [Bubble Sort]\n");
        printf("  7.  Calculate Total Seat Capacity  [EXTRA]\n");
        printf("  8.  Display Fleet Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addTrain();                    break;
            case 2: removeTrain();                 break;
            case 3: updateTrainInfo();             break;
            case 4: searchTrain();                 break;
            case 5: displayFleet();                break;
            case 6: bubbleSortByCapacity();        break;
            case 7: calculateTotalSeatCapacity();  break;
            case 8: displayFleetTable();           break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
