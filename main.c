/* ================================================================
   main.c -- Master Entry Point
   Sri Lanka Railway Network Management System
   ================================================================
   MODULE MAP:
     1. Train Fleet Registry      [Array]          Member 1
     2. Station Directory         [Singly LL]      Member 2
     3. Journey Log               [Doubly LL]      Member 3
     4. Train Route Rotation      [Circular LL]    Member 4
     5. Ticket Cancellation Log   [Stack]          Member 5
     6. Passenger Boarding Queue  [Queue]          Member 6
     7. Train Maintenance Queue   [Queue x2]       Member 7

   Universal Keys:
     trainID   -> Fleet -> Journey Log, Route Rotation, Maintenance
     stationID -> Station Directory -> Journey Log, Boarding Queue
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "include/shared_types.h"
#include "include/train_fleet.h"
#include "include/station_directory.h"
#include "include/journey_log.h"
#include "include/route_rotation.h"
#include "include/cancellation_log.h"
#include "include/boarding_queue.h"
#include "include/maintenance_queue.h"

/* ---------- Banner ---------- */
void printBanner() {
    printf("\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  |  ** SRI LANKA RAILWAY NETWORK MANAGEMENT SYSTEM **       |\n");
    printf("  |       Colombo Fort Operations Centre                     |\n");
    printf("  +----------------------------------------------------------+\n");
}

/* ---------- Main menu ---------- */
void printMainMenu() {
    printf("\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  |                      MAIN MENU                           |\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  |  1.  Train Fleet Registry       [Array]                  |\n");
    printf("  |  2.  Station Directory          [Singly Linked List]     |\n");
    printf("  |  3.  Journey Log                [Doubly Linked List]     |\n");
    printf("  |  4.  Train Route Rotation       [Circular Linked List]   |\n");
    printf("  |  5.  Ticket Cancellation Log    [Stack]                  |\n");
    printf("  |  6.  Passenger Boarding Queue   [Queue]                  |\n");
    printf("  |  7.  Train Maintenance Queue    [Queue]                  |\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  |  0.  Exit System                                         |\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  Choice: ");
}

/* ---------- Quick reference ---------- */
void printReference() {
    printf("\n");
    printf("  +------------------------------------------------------------+\n");
    printf("  |          FAMOUS SL RAILWAY TRAINS  (Reference)             |\n");
    printf("  +--------------------------+---------------------------------+\n");
    printf("  | Udarata Menike           | Colombo -> Badulla              |\n");
    printf("  | Ruhunu Kumari            | Colombo -> Matara               |\n");
    printf("  | Yal Devi                 | Colombo -> Jaffna               |\n");
    printf("  | Intercity Express        | Colombo -> Kandy                |\n");
    printf("  | Rajarata Rajini          | Colombo -> Vauniya              |\n");
    printf("  +------------------------------------------------------------+\n");
}

/* ================================================================
   MAIN
   ================================================================ */
int main() {
    /* Initialize stack */
    cancelStack.top = -1;

    printBanner();
    printReference();

    int choice;
    do {
        printMainMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: trainFleetMenu();        break;
            case 2: stationDirectoryMenu();  break;
            case 3: journeyLogMenu();        break;
            case 4: routeRotationMenu();     break;
            case 5: cancellationLogMenu();   break;
            case 6: boardingQueueMenu();     break;
            case 7: maintenanceQueueMenu();  break;
            case 0:
                printf("\n  [+] Exiting Sri Lanka Railway System. Goodbye.\n\n");
                break;
            default:
                printf("  [!] Invalid choice. Select 0-7.\n");
        }
    } while (choice != 0);

    return 0;
}