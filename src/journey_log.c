/* ================================================================
   journey_log.c — Member 3 | Data Structure: DOUBLY LINKED LIST
   Module: Journey Log
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/journey_log.h"

/* ---------- List pointers ---------- */
JourneyNode* journeyHead = NULL;
JourneyNode* journeyTail = NULL;

/* ---------- ID generator ---------- */
static int journeyIDCounter = 300;

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

/* Append a new journey record to the tail of the doubly LL */
void addJourneyRecord() {
    JourneyNode* newNode = (JourneyNode*)malloc(sizeof(JourneyNode));
    if (!newNode) { printf("[!] Memory error.\n"); return; }

    newNode->journeyID = ++journeyIDCounter;
    newNode->prev      = NULL;
    newNode->next      = NULL;

    printf("\n--- Log New Journey ---\n");
    printf("Train ID              : T"); scanf("%d", &newNode->trainID);
    printf("Train Name            : "); scanf(" %[^\n]", newNode->trainName);
    printf("From Station ID       : ST"); scanf("%d", &newNode->fromStationID);
    printf("From Station Name     : "); scanf(" %[^\n]", newNode->fromStation);
    printf("To Station ID         : ST"); scanf("%d", &newNode->toStationID);
    printf("To Station Name       : "); scanf(" %[^\n]", newNode->toStation);
    printf("Departure Time        : "); scanf(" %[^\n]", newNode->departureTime);
    printf("Arrival Time          : "); scanf(" %[^\n]", newNode->arrivalTime);
    printf("Distance (km)         : "); scanf("%f", &newNode->distanceKm);
    printf("Delay (minutes, 0=none): "); scanf("%d", &newNode->delayMinutes);
    strcpy(newNode->status, newNode->delayMinutes > 0 ? "Delayed" : "On Time");

    /* Append to tail */
    if (!journeyHead) {
        journeyHead = newNode;
        journeyTail = newNode;
    } else {
        newNode->prev       = journeyTail;
        journeyTail->next   = newNode;
        journeyTail         = newNode;
    }
    printf("[+] Journey J%d logged: %s -> %s\n",
           newNode->journeyID, newNode->fromStation, newNode->toStation);
}

/* Remove a journey record by journeyID */
void removeJourneyRecord() {
    if (!journeyHead) { printf("[!] Journey log is empty.\n"); return; }
    int id;
    printf("\nEnter Journey ID to remove: J"); scanf("%d", &id);

    JourneyNode* curr = journeyHead;
    while (curr && curr->journeyID != id) curr = curr->next;
    if (!curr) { printf("[!] Journey J%d not found.\n", id); return; }

    if (curr->prev) curr->prev->next = curr->next;
    else            journeyHead      = curr->next;
    if (curr->next) curr->next->prev = curr->prev;
    else            journeyTail      = curr->prev;

    printf("[+] Journey J%d removed.\n", id);
    free(curr);
}

/* Update journey status or delay */
void updateJourneyStatus() {
    if (!journeyHead) { printf("[!] Journey log is empty.\n"); return; }
    int id;
    printf("\nEnter Journey ID to update: J"); scanf("%d", &id);
    JourneyNode* curr = journeyHead;
    while (curr && curr->journeyID != id) curr = curr->next;
    if (!curr) { printf("[!] Journey J%d not found.\n", id); return; }

    printf("Update:\n  1. Status\n  2. Delay Minutes\n  3. Arrival Time\nChoice: ");
    int ch; scanf("%d", &ch);
    switch (ch) {
        case 1: printf("New status: "); scanf(" %[^\n]", curr->status);        break;
        case 2: printf("Delay (min): "); scanf("%d", &curr->delayMinutes);     break;
        case 3: printf("Arrival time: "); scanf(" %[^\n]", curr->arrivalTime); break;
        default: printf("[!] Invalid.\n"); return;
    }
    printf("[+] Journey J%d updated.\n", id);
}

/* Search journey by ID or trainID */
void searchJourneyRecord() {
    if (!journeyHead) { printf("[!] Journey log is empty.\n"); return; }
    printf("\nSearch by:\n  1. Journey ID\n  2. Train ID\nChoice: ");
    int ch; scanf("%d", &ch);
    int found = 0;

    if (ch == 1) {
        int id; printf("Enter Journey ID: J"); scanf("%d", &id);
        JourneyNode* curr = journeyHead;
        while (curr) {
            if (curr->journeyID == id) {
                printf(DIVIDER);
                printf("  Journey ID  : J%d\n",   curr->journeyID);
                printf("  Train       : T%d — %s\n", curr->trainID, curr->trainName);
                printf("  From        : %s\n",    curr->fromStation);
                printf("  To          : %s\n",    curr->toStation);
                printf("  Departure   : %s\n",    curr->departureTime);
                printf("  Arrival     : %s\n",    curr->arrivalTime);
                printf("  Distance    : %.1f km\n", curr->distanceKm);
                printf("  Delay       : %d min\n", curr->delayMinutes);
                printf("  Status      : %s\n",    curr->status);
                printf(DIVIDER);
                found = 1; break;
            }
            curr = curr->next;
        }
    } else {
        int tid; printf("Enter Train ID: T"); scanf("%d", &tid);
        JourneyNode* curr = journeyHead;
        while (curr) {
            if (curr->trainID == tid) {
                printf("  J%-4d | %-15s -> %-15s | %s | %.1fkm | %s\n",
                       curr->journeyID, curr->fromStation, curr->toStation,
                       curr->departureTime, curr->distanceKm, curr->status);
                found = 1;
            }
            curr = curr->next;
        }
    }
    if (!found) printf("[!] No matching journey found.\n");
}

/* Display all records — forward traversal */
void displayAllJourneys() {
    if (!journeyHead) { printf("[!] Journey log is empty.\n"); return; }
    printf("\n%-6s %-6s %-18s %-18s %-8s %-8s %-6s\n",
           "JID","TrnID","From","To","Depart","Arrive","Status");
    printf(DIVIDER);
    JourneyNode* curr = journeyHead;
    int count = 0;
    while (curr) {
        printf("J%-5d T%-5d %-18s %-18s %-8s %-8s %-6s\n",
               curr->journeyID, curr->trainID,
               curr->fromStation, curr->toStation,
               curr->departureTime, curr->arrivalTime, curr->status);
        count++; curr = curr->next;
    }
    printf(DIVIDER);
    printf("Total journeys logged: %d\n", count);
}

/* Browse forward — oldest to newest */
void traverseForward() {
    if (!journeyHead) { printf("[!] Log is empty.\n"); return; }
    printf("\n[FORWARD — Oldest Journey -> Latest]\n");
    printf(DIVIDER);
    JourneyNode* curr = journeyHead;
    int step = 1;
    while (curr) {
        printf("Step %d: J%d | T%d | %s -> %s | %s | %.1fkm\n",
               step++, curr->journeyID, curr->trainID,
               curr->fromStation, curr->toStation,
               curr->departureTime, curr->distanceKm);
        curr = curr->next;
    }
    printf(DIVIDER);
}

/* Browse backward — latest to oldest (unique to Doubly LL) */
void traverseBackward() {
    if (!journeyTail) { printf("[!] Log is empty.\n"); return; }
    printf("\n[BACKWARD — Latest Journey -> Oldest]\n");
    printf(DIVIDER);
    JourneyNode* curr = journeyTail;
    int step = 1;
    while (curr) {
        printf("Step %d: J%d | T%d | %s -> %s | %s | %.1fkm\n",
               step++, curr->journeyID, curr->trainID,
               curr->fromStation, curr->toStation,
               curr->departureTime, curr->distanceKm);
        curr = curr->prev;
    }
    printf(DIVIDER);
}

/* ================================================================
   SORT — SELECTION SORT by Departure Time (lexicographic)
   Swaps data between nodes, leaves prev/next pointers intact.
   ================================================================ */
void selectionSortByDeparture() {
    if (!journeyHead || !journeyHead->next) {
        printf("[!] Not enough records to sort.\n"); return;
    }
    JourneyNode* i = journeyHead;
    while (i) {
        JourneyNode* minNode = i;
        JourneyNode* j       = i->next;
        while (j) {
            if (strcmp(j->departureTime, minNode->departureTime) < 0)
                minNode = j;
            j = j->next;
        }
        if (minNode != i) {
            /* Swap all data fields between i and minNode */
            int   tmpJID  = i->journeyID; i->journeyID  = minNode->journeyID;  minNode->journeyID  = tmpJID;
            int   tmpTID  = i->trainID;   i->trainID    = minNode->trainID;    minNode->trainID    = tmpTID;
            int   tmpFSID = i->fromStationID; i->fromStationID = minNode->fromStationID; minNode->fromStationID = tmpFSID;
            int   tmpTSID = i->toStationID;   i->toStationID   = minNode->toStationID;   minNode->toStationID   = tmpTSID;
            int   tmpDelay = i->delayMinutes; i->delayMinutes  = minNode->delayMinutes;  minNode->delayMinutes  = tmpDelay;
            float tmpDist  = i->distanceKm;   i->distanceKm    = minNode->distanceKm;    minNode->distanceKm    = tmpDist;

            char tmp[NAME_LEN];
            #define SWAP_STR(a,b) strcpy(tmp,a); strcpy(a,b); strcpy(b,tmp);
            SWAP_STR(i->trainName,     minNode->trainName)
            SWAP_STR(i->fromStation,   minNode->fromStation)
            SWAP_STR(i->toStation,     minNode->toStation)
            SWAP_STR(i->departureTime, minNode->departureTime)
            SWAP_STR(i->arrivalTime,   minNode->arrivalTime)
            SWAP_STR(i->status,        minNode->status)
            #undef SWAP_STR
        }
        i = i->next;
    }
    printf("[+] Journeys sorted by departure time (Earliest -> Latest).\n");
    displayAllJourneys();
}

/* ================================================================
   EXTRA FUNCTION — calculateJourneyDistance()
   TYPE: Aggregate SUM — traverses DLL nodes summing distanceKm
   for all journeys belonging to a specific trainID.
   Answers: "What is the total distance covered by this train?"
   ================================================================ */
void calculateJourneyDistance() {
    if (!journeyHead) { printf("[!] Journey log is empty.\n"); return; }
    int tid;
    printf("Enter Train ID: T"); scanf("%d", &tid);

    float totalKm   = 0;
    int   tripCount = 0;
    char  trainName[NAME_LEN] = "Unknown";
    JourneyNode* curr = journeyHead;

    while (curr) {
        if (curr->trainID == tid) {
            totalKm += curr->distanceKm;
            tripCount++;
            strcpy(trainName, curr->trainName);
        }
        curr = curr->next;
    }

    if (tripCount == 0) {
        printf("[!] No journeys found for Train T%d.\n", tid); return;
    }
    printf("\n========== JOURNEY DISTANCE SUMMARY ==========\n");
    printf("  Train          : T%d — %s\n", tid, trainName);
    printf("  Total Trips    : %d journeys\n", tripCount);
    printf("  Total Distance : %.2f km\n", totalKm);
    printf("  Avg per Trip   : %.2f km\n", totalKm / tripCount);
    printf("===============================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
// void displayJourneyTable() {
//     if (!journeyHead) { printf("[!] Journey log is empty.\n"); return; }
//     printf("\n╔══════╦═══════╦══════════════════╦══════════════════╦═════════╦════════╦════════╗\n");
//     printf("║  JID ║ TrnID ║ From             ║ To               ║ Depart  ║ Dist   ║ Status ║\n");
//     printf("╠══════╬═══════╬══════════════════╬══════════════════╬═════════╬════════╬════════╣\n");
//     JourneyNode* curr = journeyHead;
//     while (curr) {
//         printf("║ J%-4d║ T%-5d║ %-16s ║ %-16s ║ %-7s ║ %5.1fkm║ %-6s ║\n",
//                curr->journeyID, curr->trainID,
//                curr->fromStation, curr->toStation,
//                curr->departureTime, curr->distanceKm, curr->status);
//         curr = curr->next;
//     }
//     printf("╚══════╩═══════╩══════════════════╩══════════════════╩═════════╩════════╩════════╝\n");
// }

void displayJourneyTable() {
    if (!journeyHead) {
        printf("\n  [!] Journey log is empty.\n");
        return;
    }

    printf("\n");
    printf("  +----------------------------------------------------------------------------------+\n");
    printf("  |                              JOURNEY LOG TABLE                                   |\n");
    printf("  +--------+--------+------------------+------------------+----------+--------+--------+\n");
    printf("  |  JID   | TrnID  | From             | To               | Depart   | Dist   | Status |\n");
    printf("  +--------+--------+------------------+------------------+----------+--------+--------+\n");

    JourneyNode* curr = journeyHead;

    while (curr) {
        printf("  | J%-5d | T%-5d | %-16s | %-16s | %-8s | %6.1f | %-6s |\n",
               curr->journeyID,
               curr->trainID,
               curr->fromStation,
               curr->toStation,
               curr->departureTime,
               curr->distanceKm,
               curr->status);

        curr = curr->next;
    }

    printf("  +--------+--------+------------------+------------------+----------+--------+--------+\n");
}

/* ================================================================
   SUB-MENU — Member 3
   ================================================================ */
void journeyLogMenu() {
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       JOURNEY LOG  [DOUBLY LINKED LIST]\n");
        printf("%s", HEADER);
        printf("  1.  Add Journey Record\n");
        printf("  2.  Remove Journey Record\n");
        printf("  3.  Update Journey Status\n");
        printf("  4.  Search Journey\n");
        printf("  5.  Display All Journeys\n");
        printf("  6.  Traverse Forward (Oldest -> Latest)\n");
        printf("  7.  Traverse Backward (Latest -> Oldest)\n");
        printf("  8.  Sort by Departure Time  [Selection Sort]\n");
        printf("  9.  Calculate Journey Distance  [EXTRA]\n");
        printf(" 10.  Display Journey Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:  addJourneyRecord();           break;
            case 2:  removeJourneyRecord();        break;
            case 3:  updateJourneyStatus();        break;
            case 4:  searchJourneyRecord();        break;
            case 5:  displayAllJourneys();         break;
            case 6:  traverseForward();            break;
            case 7:  traverseBackward();           break;
            case 8:  selectionSortByDeparture();   break;
            case 9:  calculateJourneyDistance();   break;
            case 10: displayJourneyTable();        break;
            case 0:  break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
