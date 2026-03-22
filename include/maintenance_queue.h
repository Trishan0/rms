#ifndef MAINTENANCE_QUEUE_H
#define MAINTENANCE_QUEUE_H

/* ================================================================
   maintenance_queue.h — Member 7 | Data Structure: QUEUE (2nd use)
   Module: Train Maintenance Queue
   ================================================================
   RESPONSIBILITY:
     Manages trains waiting for servicing at the depot.
     Trains are submitted for maintenance and processed
     strictly in submission order — FIFO. This ensures
     no train skips its scheduled service regardless of
     its type or importance.

   WHY QUEUE AGAIN (2nd use justification):
     Boarding Queue → processes PASSENGERS at platforms
                      input: passengers joining queue
                      output: passengers boarding trains
     Maintenance Q  → processes TRAINS at depots
                      input: trains submitted for service
                      output: trains returned to active fleet
     Same DS principle — different domain, different data.

   EXTRA FUNCTION:
  findPositionInQueue()
  → SEARCH + POSITIONAL LOOKUP — scans queue to find
    the position of a train using Train ID
  → Answers: "Where is my train in the queue?"
  → Maintains FIFO integrity (no reordering)
   ================================================================ */

#include "shared_types.h"

/* ---------- Maintenance record structure ---------- */
typedef struct {
    int  serviceID;
    int  trainID;                 /* links to Train Fleet            */
    char trainName[NAME_LEN];
    char maintenanceType[30];     /* "Routine","Repair","Emergency"  */
    char submittedAt[TIME_LEN];   /* when submitted to queue         */
    char assignedDepot[40];       /* "Colombo Depot","Kandy Depot"   */
    char status[STATUS_LEN];      /* "Pending","In Service","Done"   */
    char notes[DESC_LEN];         /* description of work needed      */
} MaintenanceRecord;

/* ---------- Queue structure (circular array) ---------- */
typedef struct {
    MaintenanceRecord records[MAX_MAINTENANCE];
    int front;
    int rear;
    int count;
} MaintenanceQueue;

/* ---------- Global queue instance ---------- */
extern MaintenanceQueue maintQ;

/* ---------- Base operations ---------- */
void enqueueForMaintenance();    /* submit train for servicing       */
void processNextMaintenance();   /* dequeue front, begin service     */
void peekNextMaintenance();      /* who is next without removing     */
void searchMaintenance();        /* find by trainID in queue         */
void displayMaintenanceQueue();  /* show all pending services        */
void cancelMaintenance();        /* remove specific train            */
int  isMaintenanceQueueEmpty();  /* check if queue is empty          */
int  isMaintenanceQueueFull();   /* check if queue is full           */

/* ---------- Extra function ---------- */
void findPositionInQueue();      /* Find position of a train in queue */      

/* ---------- Formatted display ---------- */
void displayMaintenanceTable();  /* formatted box table              */

/* ---------- Sub-menu ---------- */
void maintenanceQueueMenu();

#endif /* MAINTENANCE_QUEUE_H */
