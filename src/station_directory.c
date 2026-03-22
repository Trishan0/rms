/* ================================================================
   station_directory.c - Member 2 | Data Structure: SINGLY LINKED LIST
   Module: Station Directory
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/station_directory.h"

/* ---------- List head pointer ---------- */
StationNode* stationHead = NULL;

/* ---------- ID generator ---------- */
static int stationIDCounter = 200;
static int generateStationID() { return ++stationIDCounter; }

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

/* Add a new station node to the directory */
void addStation() {
    StationNode* newNode = (StationNode*)malloc(sizeof(StationNode));
    if (!newNode) { printf("[!] Memory allocation failed.\n"); return; }

    newNode->stationID = generateStationID();
    newNode->next      = NULL;
    strcpy(newNode->status, "Active");

    printf("\n--- Add New Station ---\n");
    printf("Station Name (e.g. Colombo Fort) : "); scanf(" %[^\n]", newNode->stationName);
    printf("Station Code (e.g. CMB)          : "); scanf(" %[^\n]", newNode->stationCode);
    printf("Route ID                         : "); scanf("%d", &newNode->routeID);
    printf("Route Name                       : "); scanf(" %[^\n]", newNode->routeName);
    printf("Number of Platforms              : "); scanf("%d", &newNode->platformCount);
    printf("District                         : "); scanf(" %[^\n]", newNode->district);

    /* Append to end of singly linked list */
    if (stationHead == NULL) {
        stationHead = newNode;
    } else {
        StationNode* temp = stationHead;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    printf("[+] Station added. ID: ST%d | %s (%s)\n",
           newNode->stationID, newNode->stationName, newNode->stationCode);
}

/* Remove a station by stationID */
void removeStation() {
    if (stationHead == NULL) { printf("[!] Directory is empty.\n"); return; }
    int id;
    printf("\nEnter Station ID to remove: ST"); scanf("%d", &id);

    if (stationHead->stationID == id) {
        StationNode* temp = stationHead;
        stationHead = stationHead->next;
        printf("[+] Removed: %s (ST%d)\n", temp->stationName, id);
        free(temp); return;
    }
    StationNode* prev = stationHead;
    StationNode* curr = stationHead->next;
    while (curr && curr->stationID != id) { prev = curr; curr = curr->next; }
    if (!curr) { printf("[!] Station ST%d not found.\n", id); return; }
    prev->next = curr->next;
    printf("[+] Removed: %s (ST%d)\n", curr->stationName, id);
    free(curr);
}

/* Update station information */
void updateStationInfo() {
    if (stationHead == NULL) { printf("[!] Directory is empty.\n"); return; }
    int id;
    printf("\nEnter Station ID to update: ST"); scanf("%d", &id);
    StationNode* curr = stationHead;
    while (curr && curr->stationID != id) curr = curr->next;
    if (!curr) { printf("[!] Station ST%d not found.\n", id); return; }

    printf("Update:\n  1. Platform Count\n  2. Status\n  3. Route\nChoice: ");
    int ch; scanf("%d", &ch);
    switch (ch) {
        case 1: printf("New platform count: "); scanf("%d", &curr->platformCount); break;
        case 2: printf("New status: ");         scanf(" %[^\n]", curr->status);    break;
        case 3: printf("New route ID: ");       scanf("%d", &curr->routeID);
                printf("New route name: ");     scanf(" %[^\n]", curr->routeName); break;
        default: printf("[!] Invalid.\n"); return;
    }
    printf("[+] Station ST%d updated.\n", id);
}

/* Search station by ID or name */
void searchStation() {
    if (stationHead == NULL) { printf("[!] Directory is empty.\n"); return; }
    printf("\nSearch by:\n  1. Station ID\n  2. Name\nChoice: ");
    int ch; scanf("%d", &ch);
    int found = 0;

    if (ch == 1) {
        int id; printf("Enter Station ID: ST"); scanf("%d", &id);
        StationNode* curr = stationHead;
        while (curr) {
            if (curr->stationID == id) {
                printf(DIVIDER);
                printf("  ID        : ST%d\n",  curr->stationID);
                printf("  Name      : %s\n",     curr->stationName);
                printf("  Code      : %s\n",     curr->stationCode);
                printf("  Route     : %s (ID:%d)\n", curr->routeName, curr->routeID);
                printf("  Platforms : %d\n",     curr->platformCount);
                printf("  District  : %s\n",     curr->district);
                printf("  Status    : %s\n",     curr->status);
                printf(DIVIDER);
                found = 1; break;
            }
            curr = curr->next;
        }
    } else {
        char name[NAME_LEN];
        printf("Enter station name: "); scanf(" %[^\n]", name);
        StationNode* curr = stationHead;
        while (curr) {
            if (strstr(curr->stationName, name)) {
                printf("  ST%-4d | %-25s | %-5s | Route: %-20s | %s\n",
                       curr->stationID, curr->stationName,
                       curr->stationCode, curr->routeName, curr->status);
                found = 1;
            }
            curr = curr->next;
        }
    }
    if (!found) printf("[!] No matching station found.\n");
}

/* Traverse and display all station nodes */
void displayAllStations() {
    if (stationHead == NULL) { printf("[!] Directory is empty.\n"); return; }
    printf("\n%-6s %-25s %-6s %-5s %-22s %-12s\n",
           "ID","Name","Code","Plat","Route","Status");
    printf(DIVIDER);
    StationNode* curr = stationHead;
    int count = 0;
    while (curr) {
        printf("ST%-4d %-25s %-6s %-5d %-22s %-12s\n",
               curr->stationID, curr->stationName, curr->stationCode,
               curr->platformCount, curr->routeName, curr->status);
        count++;
        curr = curr->next;
    }
    printf(DIVIDER);
    printf("Total stations: %d\n", count);
}

/* ================================================================
   SORT - INSERTION SORT by Station Code (alphabetical A→Z)
   Re-links nodes into correct sorted position.
   ================================================================ */
void insertionSortByCode() {
    if (!stationHead || !stationHead->next) {
        printf("[!] Not enough stations to sort.\n"); return;
    }
    StationNode* sorted = NULL;
    StationNode* curr   = stationHead;

    while (curr) {
        StationNode* next = curr->next;
        /* Find correct insertion point in sorted list */
        if (!sorted || strcmp(curr->stationCode, sorted->stationCode) < 0) {
            curr->next = sorted;
            sorted     = curr;
        } else {
            StationNode* temp = sorted;
            while (temp->next &&
                   strcmp(temp->next->stationCode, curr->stationCode) < 0)
                temp = temp->next;
            curr->next  = temp->next;
            temp->next  = curr;
        }
        curr = next;
    }
    stationHead = sorted;
    printf("[+] Stations sorted by code (A → Z).\n");
    displayAllStations();
}

/* ================================================================
   EXTRA FUNCTION - countStationsOnRoute()
   TYPE: Filtered COUNT - traverses list counting nodes
   matching a specific routeID.
   Answers: "How many stations are on route X?"
   ================================================================ */
void countStationsOnRoute() {
    if (stationHead == NULL) { printf("[!] Directory is empty.\n"); return; }
    int routeID;
    printf("Enter Route ID to count stations for: "); scanf("%d", &routeID);

    int count = 0;
    char routeName[50] = "Unknown";
    StationNode* curr  = stationHead;

    while (curr) {
        if (curr->routeID == routeID) {
            count++;
            strcpy(routeName, curr->routeName);
        }
        curr = curr->next;
    }
    printf("\n========== STATIONS ON ROUTE ==========\n");
    printf("  Route ID   : %d\n", routeID);
    printf("  Route Name : %s\n", routeName);
    printf("  Station Count : %d stations\n", count);
    printf("========================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
// void displayStationTable() {
//     if (stationHead == NULL) { printf("[!] Directory is empty.\n"); return; }
//     printf("\n╔════════╦═════════════════════════╦════════╦══════╦══════════════════════╦════════════╗\n");
//     printf("║   ID   ║ Station Name            ║  Code  ║ Plat ║ Route                ║ Status     ║\n");
//     printf("╠════════╬═════════════════════════╬════════╬══════╬══════════════════════╬════════════╣\n");
//     StationNode* curr = stationHead;
//     while (curr) {
//         printf("║ ST%-4d ║ %-23s ║ %-6s ║ %-4d ║ %-20s ║ %-10s ║\n",
//                curr->stationID, curr->stationName, curr->stationCode,
//                curr->platformCount, curr->routeName, curr->status);
//         curr = curr->next;
//     }
//     printf("╚════════╩═════════════════════════╩════════╩══════╩══════════════════════╩════════════╝\n");
// }

void displayStationTable() {
    if (stationHead == NULL) {
        printf("\n  [!] Directory is empty.\n");
        return;
    }

    printf("\n");
    printf("  +--------------------------------------------------------------------------------------+\n");
    printf("  |                                   STATION DIRECTORY                                  |\n");
    printf("  +--------+-------------------------+--------+------+----------------------+------------+\n");
    printf("  |   ID   | Station Name            | Code   | Plat | Route                | Status     |\n");
    printf("  +--------+-------------------------+--------+------+----------------------+------------+\n");

    StationNode* curr = stationHead;

    while (curr) {
        printf("  | ST%-4d | %-23s | %-6s | %-4d | %-20s | %-10s |\n",
               curr->stationID,
               curr->stationName,
               curr->stationCode,
               curr->platformCount,
               curr->routeName,
               curr->status);

        curr = curr->next;
    }

    printf("  +--------+-------------------------+--------+------+----------------------+------------+\n");
}

/* Helper: find station by ID */
StationNode* findStationByID(int id) {
    StationNode* curr = stationHead;
    while (curr) { if (curr->stationID == id) return curr; curr = curr->next; }
    return NULL;
}

/* ================================================================
   SUB-MENU - Member 2
   ================================================================ */
void stationDirectoryMenu() {
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       STATION DIRECTORY  [SINGLY LINKED LIST]\n");
        printf("%s", HEADER);
        printf("  1.  Add Station\n");
        printf("  2.  Remove Station\n");
        printf("  3.  Update Station Info\n");
        printf("  4.  Search Station\n");
        printf("  5.  Display All Stations\n");
        printf("  6.  Sort by Station Code  [Insertion Sort]\n");
        printf("  7.  Count Stations on Route  [EXTRA]\n");
        printf("  8.  Display Station Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStation();              break;
            case 2: removeStation();           break;
            case 3: updateStationInfo();       break;
            case 4: searchStation();           break;
            case 5: displayAllStations();      break;
            case 6: insertionSortByCode();     break;
            case 7: countStationsOnRoute();    break;
            case 8: displayStationTable();     break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
