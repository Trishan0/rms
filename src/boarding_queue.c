/* ================================================================
   boarding_queue.c — Member 6 | Data Structure: QUEUE
   Module: Passenger Boarding Queue
   ================================================================ */

#include <stdio.h>
#include <string.h>
#include "../include/boarding_queue.h"

/* ---------- Global queue instance ---------- */
BoardingQueue boardingQ;

/* ---------- Initialization flag ---------- */
static int initialized = 0;
static void ensureInit() {
    if (!initialized) {
        boardingQ.front = 0;
        boardingQ.rear  = -1;
        boardingQ.count = 0;
        initialized     = 1;
    }
}

/* ---------- ID generator ---------- */
static int passengerIDCounter = 600;

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

int isBoardingQueueEmpty() { ensureInit(); return boardingQ.count == 0; }
int isBoardingQueueFull()  { ensureInit(); return boardingQ.count == MAX_BOARDING; }

/* Enqueue a passenger at the rear of the boarding queue */
void enqueuePassenger() {
    ensureInit();
    if (isBoardingQueueFull()) {
        printf("[!] Boarding queue is full.\n"); return;
    }
    Passenger p;
    p.passengerID = ++passengerIDCounter;
    strcpy(p.status, "Waiting");

    printf("\n--- Add Passenger to Boarding Queue ---\n");
    printf("Passenger Name         : "); scanf(" %[^\n]", p.passengerName);
    printf("Train ID               : T"); scanf("%d", &p.trainID);
    printf("Train Name             : "); scanf(" %[^\n]", p.trainName);
    printf("Station ID             : ST"); scanf("%d", &p.stationID);
    printf("Station Name           : "); scanf(" %[^\n]", p.stationName);
    printf("Ticket Class (1st/2nd/3rd): "); scanf(" %[^\n]", p.ticketClass);
    printf("Ticket Number          : "); scanf(" %[^\n]", p.ticketNumber);
    printf("Queue Join Time        : "); scanf(" %[^\n]", p.joinedQueueAt);

    boardingQ.rear = (boardingQ.rear + 1) % MAX_BOARDING;
    boardingQ.passengers[boardingQ.rear] = p;
    boardingQ.count++;
    printf("[+] Passenger P%d %s joined queue. Position: %d\n",
           p.passengerID, p.passengerName, boardingQ.count);
}

/* Dequeue the next passenger from the front */
void dequeuePassenger() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("[!] Boarding queue is empty.\n"); return;
    }
    Passenger p = boardingQ.passengers[boardingQ.front];
    strcpy(boardingQ.passengers[boardingQ.front].status, "Boarded");
    boardingQ.front = (boardingQ.front + 1) % MAX_BOARDING;
    boardingQ.count--;

    printf("\n[PASSENGER BOARDING]\n");
    printf(DIVIDER);
    printf("  P%d — %s is now boarding\n", p.passengerID, p.passengerName);
    printf("  Train   : T%d — %s\n",       p.trainID, p.trainName);
    printf("  Station : %s\n",              p.stationName);
    printf("  Class   : %s\n",              p.ticketClass);
    printf(DIVIDER);
    printf("[+] Passenger boarded. Remaining in queue: %d\n", boardingQ.count);
}

/* Peek at front passenger without dequeuing */
void peekNextPassenger() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("[!] Boarding queue is empty.\n"); return;
    }
    Passenger p = boardingQ.passengers[boardingQ.front];
    printf("\n[NEXT TO BOARD]\n");
    printf(DIVIDER);
    printf("  P%d — %s\n",          p.passengerID, p.passengerName);
    printf("  Train   : T%d — %s\n", p.trainID, p.trainName);
    printf("  Class   : %s | Ticket: %s\n", p.ticketClass, p.ticketNumber);
    printf("  Joined  : %s\n",       p.joinedQueueAt);
    printf(DIVIDER);
}

/* Search passenger by ID in the queue */
void searchPassenger() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("[!] Queue is empty.\n"); return;
    }
    int pid;
    printf("Enter Passenger ID: P"); scanf("%d", &pid);
    int found = 0;
    for (int i = 0; i < boardingQ.count; i++) {
        int idx = (boardingQ.front + i) % MAX_BOARDING;
        Passenger p = boardingQ.passengers[idx];
        if (p.passengerID == pid) {
            printf(DIVIDER);
            printf("  Queue Position : %d\n", i + 1);
            printf("  P%d — %s\n",    p.passengerID, p.passengerName);
            printf("  Train          : T%d — %s\n", p.trainID, p.trainName);
            printf("  Station        : %s\n", p.stationName);
            printf("  Class          : %s\n", p.ticketClass);
            printf("  Joined At      : %s\n", p.joinedQueueAt);
            printf("  Status         : %s\n", p.status);
            printf(DIVIDER);
            found = 1; break;
        }
    }
    if (!found) printf("[!] Passenger P%d not found in queue.\n", pid);
}

/* Display all passengers in the boarding queue */
void displayBoardingQueue() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("[!] Boarding queue is empty.\n"); return;
    }
    printf("\n%-4s %-6s %-22s %-6s %-18s %-8s %-10s\n",
           "Pos","PsnID","Name","TrnID","Station","Class","Status");
    printf(DIVIDER);
    for (int i = 0; i < boardingQ.count; i++) {
        int idx     = (boardingQ.front + i) % MAX_BOARDING;
        Passenger p = boardingQ.passengers[idx];
        printf("%-4d P%-5d %-22s T%-5d %-18s %-8s %-10s%s\n",
               i + 1, p.passengerID, p.passengerName,
               p.trainID, p.stationName,
               p.ticketClass, p.status,
               (i == 0) ? " <- NEXT" : "");
    }
    printf(DIVIDER);
    printf("Queue: %d / %d\n", boardingQ.count, MAX_BOARDING);
}

/* Remove a specific passenger from the queue */
void cancelBoarding() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("[!] Queue is empty.\n"); return;
    }
    int pid;
    printf("Enter Passenger ID to remove: P"); scanf("%d", &pid);

    int found = -1;
    for (int i = 0; i < boardingQ.count; i++) {
        int idx = (boardingQ.front + i) % MAX_BOARDING;
        if (boardingQ.passengers[idx].passengerID == pid) {
            found = i; break;
        }
    }
    if (found == -1) { printf("[!] Passenger not found.\n"); return; }

    for (int i = found; i < boardingQ.count - 1; i++) {
        int curr = (boardingQ.front + i)     % MAX_BOARDING;
        int next = (boardingQ.front + i + 1) % MAX_BOARDING;
        boardingQ.passengers[curr] = boardingQ.passengers[next];
    }
    boardingQ.rear = (boardingQ.rear - 1 + MAX_BOARDING) % MAX_BOARDING;
    boardingQ.count--;
    printf("[+] Passenger P%d removed from boarding queue.\n", pid);
}

/* ================================================================
   EXTRA FUNCTION — getAverageWaitTime()
   TYPE: Aggregate AVERAGE — computed queue depth metric
   Computes average position / wait information for queue.
   ================================================================ */
void getAverageWaitTime() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("[!] Boarding queue is empty.\n"); return;
    }
    /* Count by ticket class for distribution report */
    int first = 0, second = 0, third = 0;
    for (int i = 0; i < boardingQ.count; i++) {
        int idx     = (boardingQ.front + i) % MAX_BOARDING;
        Passenger p = boardingQ.passengers[idx];
        if (strstr(p.ticketClass, "First"))  first++;
        else if (strstr(p.ticketClass, "Second")) second++;
        else third++;
    }
    float avgPosition = (boardingQ.count + 1) / 2.0f;

    printf("\n========== BOARDING QUEUE STATUS ==========\n");
    printf("  Total Waiting    : %d passengers\n", boardingQ.count);
    printf("  Average Position : %.1f\n",           avgPosition);
    printf("  First Class      : %d passengers\n",  first);
    printf("  Second Class     : %d passengers\n",  second);
    printf("  Third Class      : %d passengers\n",  third);
    printf("  Queue Capacity   : %d / %d slots used\n",
           boardingQ.count, MAX_BOARDING);
    printf("============================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
// void displayBoardingTable() {
//     ensureInit();
//     if (isBoardingQueueEmpty()) {
//         printf("[!] Boarding queue is empty.\n"); return;
//     }
//     printf("\n╔═════╦════════╦══════════════════════╦════════╦══════════════════╦══════════╦══════════╗\n");
//     printf("║ Pos ║  PsnID ║ Name                 ║  TrnID ║ Station          ║ Class    ║ Status   ║\n");
//     printf("╠═════╬════════╬══════════════════════╬════════╬══════════════════╬══════════╬══════════╣\n");
//     for (int i = 0; i < boardingQ.count; i++) {
//         int idx     = (boardingQ.front + i) % MAX_BOARDING;
//         Passenger p = boardingQ.passengers[idx];
//         printf("║ %-3d ║ P%-5d ║ %-20s ║ T%-5d ║ %-16s ║ %-8s ║ %-8s ║%s\n",
//                i + 1, p.passengerID, p.passengerName, p.trainID,
//                p.stationName, p.ticketClass, p.status,
//                (i == 0) ? "<-NEXT" : "");
//     }
//     printf("╚═════╩════════╩══════════════════════╩════════╩══════════════════╩══════════╩══════════╝\n");
//     printf("Queue: %d / %d slots used\n", boardingQ.count, MAX_BOARDING);
// }

void displayBoardingTable() {
    ensureInit();
    if (isBoardingQueueEmpty()) {
        printf("\n  [!] Boarding queue is empty.\n");
        return;
    }

    printf("\n");
    printf("  +----------------------------------------------------------------------------------------+\n");
    printf("  |                               PASSENGER BOARDING QUEUE                                 |\n");
    printf("  +-----+--------+----------------------+--------+------------------+----------+----------+\n");
    printf("  | Pos | PsnID  | Name                 | TrnID  | Station          | Class    | Status   |\n");
    printf("  +-----+--------+----------------------+--------+------------------+----------+----------+\n");

    for (int i = 0; i < boardingQ.count; i++) {
        int idx     = (boardingQ.front + i) % MAX_BOARDING;
        Passenger p = boardingQ.passengers[idx];

        printf("  | %-3d | P%-5d | %-20s | T%-5d | %-16s | %-8s | %-8s |%s\n",
               i + 1,
               p.passengerID,
               p.passengerName,
               p.trainID,
               p.stationName,
               p.ticketClass,
               p.status,
               (i == 0) ? " <-NEXT" : "");
    }

    printf("  +-----+--------+----------------------+--------+------------------+----------+----------+\n");
    printf("  Queue: %d / %d slots used\n", boardingQ.count, MAX_BOARDING);
}

/* ================================================================
   SUB-MENU — Member 6
   ================================================================ */
void boardingQueueMenu() {
    ensureInit();
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       PASSENGER BOARDING QUEUE  [QUEUE]\n");
        printf("%s", HEADER);
        printf("  1.  Add Passenger to Queue\n");
        printf("  2.  Board Next Passenger\n");
        printf("  3.  Peek Next Passenger\n");
        printf("  4.  Search Passenger\n");
        printf("  5.  Display Boarding Queue\n");
        printf("  6.  Cancel Boarding\n");
        printf("  7.  Get Average Wait Time  [EXTRA]\n");
        printf("  8.  Display Boarding Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: enqueuePassenger();      break;
            case 2: dequeuePassenger();      break;
            case 3: peekNextPassenger();     break;
            case 4: searchPassenger();       break;
            case 5: displayBoardingQueue();  break;
            case 6: cancelBoarding();        break;
            case 7: getAverageWaitTime();    break;
            case 8: displayBoardingTable();  break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
