/* ================================================================
   route_rotation.c - Member 4 | Data Structure: CIRCULAR LINKED LIST
   Module: Train Route Rotation
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/route_rotation.h"

/* ---------- Rotation pointer & size ---------- */
RouteNode* currentTrain  = NULL;
static int rotationCount = 0;

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

/* Insert a train into the circular rotation cycle */
void addTrainToRoute() {
    RouteNode* newNode = (RouteNode*)malloc(sizeof(RouteNode));
    if (!newNode) { printf("[!] Memory error.\n"); return; }
    newNode->tripsCompleted = 0;

    printf("\n--- Add Train to Route Rotation ---\n");
    printf("Train ID (from Fleet)  : T"); scanf("%d", &newNode->trainID);
    printf("Train Name             : "); scanf(" %[^\n]", newNode->trainName);
    printf("Route Name             : "); scanf(" %[^\n]", newNode->routeName);
    printf("Schedule Time          : "); scanf(" %[^\n]", newNode->scheduleTime);
    printf("Direction (e.g. Northbound): "); scanf(" %[^\n]", newNode->direction);

    if (currentTrain == NULL) {
        /* First node - points to itself */
        newNode->next = newNode;
        currentTrain  = newNode;
    } else {
        /* Find the last node (next == currentTrain) and insert before head */
        RouteNode* temp = currentTrain;
        while (temp->next != currentTrain) temp = temp->next;
        temp->next    = newNode;
        newNode->next = currentTrain;
    }
    rotationCount++;
    printf("[+] T%d %s added to rotation. Cycle size: %d\n",
           newNode->trainID, newNode->trainName, rotationCount);
}

/* Remove a train from the circular cycle by trainID */
void removeTrainFromRoute() {
    if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
    int id;
    printf("\nEnter Train ID to remove: T"); scanf("%d", &id);

    /* Special case: only one node */
    if (rotationCount == 1) {
        if (currentTrain->trainID == id) {
            printf("[+] Removed T%d %s from rotation.\n",
                   currentTrain->trainID, currentTrain->trainName);
            free(currentTrain);
            currentTrain  = NULL;
            rotationCount = 0;
            return;
        }
        printf("[!] Train T%d not in rotation.\n", id); return;
    }

    /* Find node and its predecessor */
    RouteNode* prev = currentTrain;
    while (prev->next != currentTrain && prev->next->trainID != id)
        prev = prev->next;

    RouteNode* toRemove = NULL;
    if (currentTrain->trainID == id) {
        /* Removing the head - advance currentTrain */
        toRemove     = currentTrain;
        prev->next   = currentTrain->next;
        currentTrain = currentTrain->next;
    } else if (prev->next->trainID == id) {
        toRemove   = prev->next;
        prev->next = toRemove->next;
    } else {
        printf("[!] Train T%d not found in rotation.\n", id); return;
    }
    printf("[+] Removed T%d %s from rotation.\n",
           toRemove->trainID, toRemove->trainName);
    free(toRemove);
    rotationCount--;
}

/* Update route schedule or direction */
void updateRouteInfo() {
    if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
    int id;
    printf("\nEnter Train ID to update: T"); scanf("%d", &id);
    RouteNode* curr = currentTrain;
    for (int i = 0; i < rotationCount; i++) {
        if (curr->trainID == id) {
            printf("Update:\n  1. Schedule Time\n  2. Direction\nChoice: ");
            int ch; scanf("%d", &ch);
            if (ch == 1) { printf("New time: "); scanf(" %[^\n]", curr->scheduleTime); }
            else         { printf("New direction: "); scanf(" %[^\n]", curr->direction); }
            printf("[+] T%d updated.\n", id); return;
        }
        curr = curr->next;
    }
    printf("[!] Train T%d not in rotation.\n", id);
}

/* Search for a train in the rotation by trainID */
void searchTrainInRoute() {
    if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
    int id;
    printf("\nEnter Train ID: T"); scanf("%d", &id);
    RouteNode* curr = currentTrain;
    for (int i = 0; i < rotationCount; i++) {
        if (curr->trainID == id) {
            printf(DIVIDER);
            printf("  Train ID        : T%d\n",   curr->trainID);
            printf("  Name            : %s\n",     curr->trainName);
            printf("  Route           : %s\n",     curr->routeName);
            printf("  Schedule        : %s\n",     curr->scheduleTime);
            printf("  Direction       : %s\n",     curr->direction);
            printf("  Trips Completed : %d\n",     curr->tripsCompleted);
            printf("  On Duty Now     : %s\n",     (curr == currentTrain) ? "YES" : "NO");
            printf(DIVIDER);
            return;
        }
        curr = curr->next;
    }
    printf("[!] Train T%d not found in rotation.\n", id);
}

/* Display full circular rotation cycle */
void displayRouteRotation() {
    if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
    printf("\n[ROUTE ROTATION CYCLE]\n");
    printf(DIVIDER);
    RouteNode* curr = currentTrain;
    for (int i = 0; i < rotationCount; i++) {
        if (curr == currentTrain)
            printf("-> [ACTIVE] ");
        else
            printf("   [      ] ");
        printf("T%-4d | %-28s | %-22s | %s | Trips: %d\n",
               curr->trainID, curr->trainName,
               curr->routeName, curr->scheduleTime,
               curr->tripsCompleted);
        curr = curr->next;
    }
    printf(DIVIDER);
    printf("^ (loops back to top of cycle)\n");
    printf("Rotation size: %d trains\n", rotationCount);
}

/* ================================================================
   NAVIGATION - Defining Circular LL operations
   ================================================================ */

/* Advance rotation pointer to next train */
void nextTrainOnRoute() {
    if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
    currentTrain = currentTrain->next;
    currentTrain->tripsCompleted++;
    printf("[+] Rotation advanced.\n");
    printf("    Now Active: T%d - %s | Route: %s | Time: %s\n",
           currentTrain->trainID, currentTrain->trainName,
           currentTrain->routeName, currentTrain->scheduleTime);
}

/* Show currently active/deployed train */
void getCurrentTrain() {
    if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
    printf("\n[CURRENTLY ACTIVE TRAIN]\n");
    printf(DIVIDER);
    printf("  T%-4d | %s\n",     currentTrain->trainID, currentTrain->trainName);
    printf("  Route    : %s\n",  currentTrain->routeName);
    printf("  Schedule : %s\n",  currentTrain->scheduleTime);
    printf("  Direction: %s\n",  currentTrain->direction);
    printf("  Trips Done: %d\n", currentTrain->tripsCompleted);
    printf(DIVIDER);
}

/* ================================================================
   EXTRA FUNCTION - getRouteSize()
   TYPE: Structural COUNT via circular traversal
   Traverses circular cycle counting nodes until loop detected.
   Necessary because circular list has NO NULL end point.
   ================================================================ */
void getRouteSize() {
    if (!currentTrain) {
        printf("[!] Rotation is empty. Size: 0\n"); return;
    }
    /* Must traverse manually - no NULL to detect end */
    int count    = 0;
    RouteNode* curr = currentTrain;
    do {
        count++;
        curr = curr->next;
    } while (curr != currentTrain);

    printf("\n========== ROTATION SIZE ==========\n");
    printf("  Trains in cycle : %d\n", count);
    printf("  Active now      : T%d - %s\n",
           currentTrain->trainID, currentTrain->trainName);
    printf("====================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
// void displayRotationTable() {
//     if (!currentTrain) { printf("[!] Rotation is empty.\n"); return; }
//     printf("\n╔════════╦══════════════════════════════╦══════════════════════╦══════════╦═══════╗\n");
//     printf("║  TrnID ║ Train Name                   ║ Route                ║ Schedule ║ Trips ║\n");
//     printf("╠════════╬══════════════════════════════╬══════════════════════╬══════════╬═══════╣\n");
//     RouteNode* curr = currentTrain;
//     for (int i = 0; i < rotationCount; i++) {
//         printf("║ T%-5d ║ %-28s ║ %-20s ║ %-8s ║ %-5d ║%s\n",
//                curr->trainID, curr->trainName,
//                curr->routeName, curr->scheduleTime,
//                curr->tripsCompleted,
//                (curr == currentTrain) ? " <- ACTIVE" : "");
//         curr = curr->next;
//     }
//     printf("╚════════╩══════════════════════════════╩══════════════════════╩══════════╩═══════╝\n");
// }

void displayRotationTable() {
    if (!currentTrain) {
        printf("\n  [!] Rotation is empty.\n");
        return;
    }

    printf("\n");
    printf("  +---------------------------------------------------------------------------------+\n");
    printf("  |                                  TRAIN ROUTE ROTATION                           |\n");
    printf("  +--------+------------------------------+----------------------+----------+-------+\n");
    printf("  | TrnID  | Train Name                   | Route                | Schedule | Trips |\n");
    printf("  +--------+------------------------------+----------------------+----------+-------+\n");

    RouteNode* curr = currentTrain;

    for (int i = 0; i < rotationCount; i++) {
        printf("  | T%-5d | %-28s | %-20s | %-8s | %-5d |%s\n",
               curr->trainID,
               curr->trainName,
               curr->routeName,
               curr->scheduleTime,
               curr->tripsCompleted,
               (curr == currentTrain) ? " <- ACTIVE" : "");

        curr = curr->next;
    }

    printf("  +--------+------------------------------+----------------------+----------+-------+\n");
}

/* ================================================================
   SUB-MENU - Member 4
   ================================================================ */
void routeRotationMenu() {
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       TRAIN ROUTE ROTATION  [CIRCULAR LINKED LIST]\n");
        printf("%s", HEADER);
        printf("  1.  Add Train to Rotation\n");
        printf("  2.  Remove Train from Rotation\n");
        printf("  3.  Update Route Info\n");
        printf("  4.  Search Train in Rotation\n");
        printf("  5.  Display Full Rotation\n");
        printf("  6.  Next Train on Route  [Navigation]\n");
        printf("  7.  Get Current Active Train  [Navigation]\n");
        printf("  8.  Get Rotation Size  [EXTRA]\n");
        printf("  9.  Display Rotation Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addTrainToRoute();        break;
            case 2: removeTrainFromRoute();   break;
            case 3: updateRouteInfo();        break;
            case 4: searchTrainInRoute();     break;
            case 5: displayRouteRotation();   break;
            case 6: nextTrainOnRoute();       break;
            case 7: getCurrentTrain();        break;
            case 8: getRouteSize();           break;
            case 9: displayRotationTable();   break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
