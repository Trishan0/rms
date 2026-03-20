# Sri Lanka Railway Network Management System
## Technical Report

---

## Cover Page

| | |
|---|---|
| **Project Title** | Sri Lanka Railway Network Management System |
| **Course** | Data Structures & Algorithms |
| **Institution** | University of Moratuwa |
| **Language** | C (C99 Standard) |

### Team Members

| Member | Module | Data Structure | Sort Algorithm |
|--------|--------|---------------|----------------|
| Member 1 | Train Fleet Registry | Array | Bubble Sort |
| Member 2 | Station Directory | Singly Linked List | Insertion Sort |
| Member 3 | Journey Log | Doubly Linked List | Selection Sort |
| Member 4 | Train Route Rotation | Circular Linked List | — |
| Member 5 | Ticket Cancellation Log | Stack | — |
| Member 6 | Passenger Boarding Queue | Queue | — |
| Member 7 | Train Maintenance Queue | Queue (2nd use) | — |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [System Design](#2-system-design)
3. [Implementation](#3-implementation)
4. [Sample Outputs](#4-sample-outputs)
5. [Discussion](#5-discussion)
6. [Conclusion](#6-conclusion)

---

## 1. Introduction

### 1.1 Problem Description

Sri Lanka Railways manages a national rail network connecting major cities across the island — from Colombo Fort to Jaffna in the north, to Galle and Matara in the south, and eastward to Badulla through the hill country. Daily operations involve hundreds of trains, thousands of passengers, multiple stations, ongoing maintenance schedules, and real-time ticket transactions. Without a structured information system, managing this scale of operations efficiently is impossible.

This project implements a **Command-Line Interface (CLI) Railway Network Management System** in C that models the complete operational flow of Sri Lanka Railways. The system handles train registration, station management, journey logging, route scheduling, passenger boarding, ticket cancellations, and maintenance queuing — each module using the data structure most appropriate to the real-world behaviour of that domain.

### 1.2 Objectives

1. Implement **seven independent modules**, each solving a distinct railway operations problem.
2. Apply one **unique data structure** per module, justified by the operational characteristics of each domain (Array, Singly Linked List, Doubly Linked List, Circular Linked List, Stack, Queue × 2).
3. Implement **sorting algorithms** — Bubble Sort, Insertion Sort, and Selection Sort — within appropriate modules.
4. Provide **extra aggregate functions** per module (SUM, COUNT, AVERAGE) that derive operational intelligence from the stored data.
5. Link all modules through **universal keys** (`trainID` and `stationID`) to model real inter-departmental data flow.
6. Demonstrate mastery of **pointer manipulation**, dynamic memory allocation, and bounded array operations in C.

---

## 2. System Design

### 2.1 System Architecture

The system follows a modular architecture: a single entry point (`main.c`) dispatches to seven independent modules, each encapsulated in its own source file and header.

```
main.c  (entry point & main menu)
  │
  ├── train_fleet.c       / include/train_fleet.h       [Array]
  ├── station_directory.c / include/station_directory.h [Singly LL]
  ├── journey_log.c       / include/journey_log.h       [Doubly LL]
  ├── route_rotation.c    / include/route_rotation.h    [Circular LL]
  ├── cancellation_log.c  / include/cancellation_log.h  [Stack]
  ├── boarding_queue.c    / include/boarding_queue.h    [Queue]
  └── maintenance_queue.c / include/maintenance_queue.h [Queue]
```

### 2.2 Data Structure Summary

| Module | Data Structure | Capacity | Key Property |
|--------|---------------|----------|--------------|
| Train Fleet Registry | Array | 50 trains | Fixed, direct O(1) access |
| Station Directory | Singly Linked List | Unbounded | Dynamic growth/shrink |
| Journey Log | Doubly Linked List | Unbounded | Bidirectional navigation |
| Train Route Rotation | Circular Linked List | Unbounded | Endless cycle, no NULL end |
| Ticket Cancellation Log | Stack (array-based) | 100 records | LIFO — most recent first |
| Passenger Boarding Queue | Queue (circular array) | 100 passengers | FIFO — first come, first served |
| Train Maintenance Queue | Queue (circular array) | 50 trains | FIFO — submission order |

### 2.3 Program Flow

```
Train Added to Fleet
        │
        ▼
[Array]          Train registered → trainID assigned (T101, T102, …)
        │
        ├──► [Singly LL]    Station added to route directory → stationID assigned
        │
        ├──► [Circular LL]  Train added to route rotation cycle
        │         │
        │         └──► nextTrainOnRoute() → train departs on schedule
        │
        ├──► [Queue]        Passengers queue up to board at platform (FIFO)
        │
        ├──► [Doubly LL]    Journey logged with distance & departure time
        │         (navigate backward = older trips, forward = latest)
        │
        ├──► [Stack]        Ticket cancelled → pushed to log (LIFO)
        │         (reinstate ticket = pop from stack)
        │
        └──► [Queue]        Train submitted for depot maintenance (FIFO)
```

### 2.4 Universal Keys

Two keys link all modules together, mirroring real inter-departmental data flow:

```
trainID    → assigned in Module 1 (Train Fleet Registry)
             referenced in Module 3 (Journey Log)
             referenced in Module 4 (Train Route Rotation)
             referenced in Module 5 (Ticket Cancellation Log)
             referenced in Module 7 (Train Maintenance Queue)

stationID  → assigned in Module 2 (Station Directory)
             referenced in Module 3 (Journey Log)
             referenced in Module 6 (Passenger Boarding Queue)
```

### 2.5 Data Structure Definitions

```c
/* MODULE 1 — ARRAY */
typedef struct {
    int   trainID, seatCapacity, currentLoad;
    char  trainName[60], trainType[20], status[25], depot[40], assignedRoute[50];
} Train;
Train fleet[MAX_TRAINS];          /* static array — max 50 trains */
int   trainCount = 0;

/* MODULE 2 — SINGLY LINKED LIST */
typedef struct StationNode {
    int  stationID, routeID, platformCount;
    char stationName[60], stationCode[10], routeName[50], district[40], status[25];
    struct StationNode *next;      /* forward pointer only */
} StationNode;
StationNode *stationHead = NULL;

/* MODULE 3 — DOUBLY LINKED LIST */
typedef struct JourneyNode {
    int   journeyID, trainID, fromStationID, toStationID, delayMinutes;
    char  departureTime[25], arrivalTime[25], status[25];
    float distanceKm;
    struct JourneyNode *prev, *next;   /* both directions */
} JourneyNode;
JourneyNode *journeyHead = NULL, *journeyTail = NULL;

/* MODULE 4 — CIRCULAR LINKED LIST */
typedef struct RouteNode {
    int  trainID, tripsCompleted;
    char trainName[60], routeName[50], scheduleTime[25], direction[20];
    struct RouteNode *next;        /* last node → points back to head */
} RouteNode;
RouteNode *currentTrain = NULL;    /* always points to active train */
int rotationCount = 0;

/* MODULE 5 — STACK (array-based) */
typedef struct {
    int   cancellationID, ticketID, passengerID, trainID;
    char  passengerName[60], trainName[60], fromStation[50],
          toStation[50], journeyDate[25], reason[100], cancelledAt[25];
    float ticketPrice;
} Cancellation;
typedef struct {
    Cancellation records[MAX_CANCELLATIONS];
    int top;                       /* -1 = empty */
} CancellationStack;
CancellationStack cancelStack;

/* MODULE 6 — QUEUE (circular array) */
typedef struct {
    int  passengerID, trainID, stationID;
    char passengerName[60], trainName[60], stationName[50],
         ticketClass[20], ticketNumber[20], joinedQueueAt[25], status[25];
} Passenger;
typedef struct {
    Passenger passengers[MAX_BOARDING];
    int front, rear, count;        /* circular pointers */
} BoardingQueue;
BoardingQueue boardingQ;

/* MODULE 7 — QUEUE (circular array) */
typedef struct {
    int  serviceID, trainID;
    char trainName[60], maintenanceType[30], depot[40],
         scheduledTime[25], notes[100], status[25];
} MaintenanceRecord;
typedef struct {
    MaintenanceRecord records[MAX_MAINTENANCE];
    int front, rear, count;        /* circular pointers */
} MaintenanceQueue;
MaintenanceQueue maintQ;
```

---

## 3. Implementation

### 3.1 Module 1 — Train Fleet Registry (Array)

**File:** `src/train_fleet.c` | **Header:** `include/train_fleet.h`

The Sri Lanka Railways fleet is physically bounded — the nation can only operate as many trains as it owns. An **array** with a fixed `MAX_TRAINS = 50` capacity models this hard constraint naturally.

| Function | Type | Description |
|----------|------|-------------|
| `addTrain()` | Base | Registers a new train in the next available array slot. Assigns a unique trainID starting from 101. |
| `removeTrain()` | Base | Finds the train by ID, then shifts all subsequent elements left to close the gap. Decrements `trainCount`. |
| `updateTrainInfo()` | Base | Locates train by ID and updates one of: status, seat capacity, depot, or current load. |
| `searchTrain()` | Base | Searches by trainID (exact match) or by name (partial match using `strstr`). |
| `displayFleet()` | Base | Traverses the array from index 0 to `trainCount-1`, printing each train in a formatted row. |
| `isFleetEmpty()` | Base | Returns 1 if `trainCount == 0`. Guards all operations against empty-fleet errors. |
| `isFleetFull()` | Base | Returns 1 if `trainCount == MAX_TRAINS`. Guards `addTrain` against overflow. |
| `bubbleSortByCapacity()` | Sort (Bubble) | Compares adjacent pairs and swaps if left has lower capacity than right. Early-exit optimisation stops if a full pass completes with no swaps. Sorts highest capacity first. **Time complexity: O(n²) worst, O(n) best.** |
| `calculateTotalSeatCapacity()` | **Extra** | Traverses the full array, sums every `seatCapacity` value, computes active-only subtotal and per-train average. |
| `displayFleetTable()` | Display | Prints a box-drawing table with columns: ID, Name, Type, Seats, Load, Status. |

### 3.2 Module 2 — Station Directory (Singly Linked List)

**File:** `src/station_directory.c` | **Header:** `include/station_directory.h`

The station network expands as new lines open and contracts when stations close for renovation. A **singly linked list** allocates memory only for stations that currently exist.

| Function | Type | Description |
|----------|------|-------------|
| `addStation()` | Base | Allocates a new `StationNode` via `malloc`, fills fields, appends to tail. Assigns stationID from 201. |
| `removeStation()` | Base | Handles head removal (update `stationHead`) and middle/tail removal (re-link predecessor). Calls `free()`. |
| `updateStationInfo()` | Base | Traverses to matching stationID and updates platform count, status, or route assignment. |
| `searchStation()` | Base | By ID (exact) or by name (partial match). Traverses from `stationHead`. |
| `displayAllStations()` | Base | Traverses from `stationHead` to `NULL`, printing each station. |
| `insertionSortByCode()` | Sort (Insertion) | Builds a new sorted list by re-linking nodes into alphabetical order by `stationCode`. **Time complexity: O(n²) worst, O(n) best.** |
| `countStationsOnRoute()` | **Extra** | Traverses entire list counting nodes whose `routeID` matches the given value. Computes filtered count. |
| `findStationByID()` | Helper | Returns a pointer to the `StationNode` matching the given ID, or `NULL`. Used by other modules. |
| `displayStationTable()` | Display | Box-drawing table: ID, Name, Code, Platforms, Route, Status. |

### 3.3 Module 3 — Journey Log (Doubly Linked List)

**File:** `src/journey_log.c` | **Header:** `include/journey_log.h`

Controllers need to scroll **forward** through time to see upcoming departures and **backward** to investigate when a delay first started. Only a **doubly linked list** provides both directions natively via `prev` and `next` pointers.

| Function | Type | Description |
|----------|------|-------------|
| `addJourneyRecord()` | Base | Allocates a new `JourneyNode`, appends to `journeyTail`, sets `prev`/`next` correctly, updates both `journeyHead` and `journeyTail`. Assigns journeyID from 301. |
| `removeJourneyRecord()` | Base | Handles four cases: head removal, tail removal, middle removal, and single-node removal — each correctly re-links `prev`/`next` on neighbours. |
| `updateJourneyStatus()` | Base | Finds journey by ID; updates status, delay minutes, or arrival time. |
| `searchJourneyRecord()` | Base | By journeyID (exact) or by trainID (all matching journeys). |
| `displayAllJourneys()` | Base | Forward traversal from `journeyHead` using `next` pointers. |
| `traverseForward()` | Base | Walks from `journeyHead`, printing each node as a numbered step. Oldest journey = Step 1. |
| `traverseBackward()` | Base | Walks from `journeyTail` using `prev` pointers. **This operation is impossible in a Singly LL.** Latest journey = Step 1. |
| `selectionSortByDeparture()` | Sort (Selection) | In each pass, finds the node with the lexicographically earliest `departureTime` in the unsorted suffix, then swaps all data fields (leaving `prev`/`next` pointers untouched). **Time complexity: O(n²) always.** |
| `calculateJourneyDistance()` | **Extra** | Sums `distanceKm` for all journeys matching a given `trainID`. Also computes trip count and average distance per trip. |
| `displayJourneyTable()` | Display | Box-drawing table: Journey ID, Train, From, To, Departure, Distance, Status. |

### 3.4 Module 4 — Train Route Rotation (Circular Linked List)

**File:** `src/route_rotation.c` | **Header:** `include/route_rotation.h`

Train scheduling is an endless rotation — after the last train's slot, the schedule loops back to the first. There is no terminal "end" to the list. A **circular linked list** (last node's `next` → head node) models this naturally.

| Function | Type | Description |
|----------|------|-------------|
| `addTrainToRoute()` | Base | If cycle is empty, node points to itself. Otherwise inserts at the end (before head). Increments `rotationCount`. |
| `removeTrainFromRoute()` | Base | Handles single-node case (clears everything) and multi-node case (re-links predecessor to skip removed node). If removing `currentTrain`, advances pointer first. |
| `updateRouteInfo()` | Base | Bounded traversal (exactly `rotationCount` steps) to find and update a train's schedule or direction. |
| `searchTrainInRoute()` | Base | Same bounded traversal — prints full details including whether the node is currently `currentTrain`. |
| `displayRouteRotation()` | Base | Traverses exactly `rotationCount` steps from `currentTrain`, marking the active train. |
| `nextTrainOnRoute()` | Navigation | Advances `currentTrain = currentTrain->next`. Increments `tripsCompleted` for newly active train. **Core circular operation.** |
| `getCurrentTrain()` | Navigation | Prints details of `currentTrain` without advancing the pointer. |
| `getRouteSize()` | **Extra** | Uses a `do-while` loop starting at `currentTrain` to count all nodes until the pointer loops back. Necessary because there is no NULL to detect the end. |
| `displayRotationTable()` | Display | Box-drawing table showing all trains in cycle, schedule, direction, trips completed, and active marker. |

### 3.5 Module 5 — Ticket Cancellation Log (Stack)

**File:** `src/cancellation_log.c` | **Header:** `include/cancellation_log.h`

When a passenger cancels a ticket, the record must be immediately retrievable for reversal (reinstatement). The most recently cancelled ticket is always the first candidate for reinstatement — **Last-In First-Out** logic, implemented as an **array-based stack**.

| Function | Type | Description |
|----------|------|-------------|
| `pushCancellation()` | Base | Increments `top`, stores new `Cancellation` struct at `records[top]`. Assigns cancellationID from 501. |
| `popCancellation()` | Base | Reads `records[top]`, decrements `top` (logical removal). Prints full reinstatement details. |
| `peekLastCancellation()` | Base | Reads `records[top]` without modifying `top`. Preview before deciding whether to undo. |
| `searchCancellation()` | Base | Scans entire stack from `top` downward for a matching `ticketID`. |
| `displayCancellationLog()` | Base | Iterates from `top` to 0, printing each record. Marks `records[top]` as "TOP". |
| `clearLog()` | Base | After confirmation, sets `top = -1`. All records become logically unreachable. |
| `isStackEmpty()` | Base | Returns 1 if `top == -1`. |
| `isStackFull()` | Base | Returns 1 if `top == MAX_CANCELLATIONS - 1`. |
| `getTotalRefundAmount()` | **Extra** | Traverses array from index 0 to `top`, summing all `ticketPrice` values. Also computes average, highest, and lowest single refund. |
| `displayFormattedLog()` | Display | Box-drawing table: No., CancelID, Passenger, TrainID, From, To, Price. TOP entry marked. |

### 3.6 Module 6 — Passenger Boarding Queue (Queue)

**File:** `src/boarding_queue.c` | **Header:** `include/boarding_queue.h`

Platform boarding is strictly first-come, first-served — the first passenger who joined the queue boards first. A **queue (FIFO)** implemented as a **circular array** ensures fair ordering with O(1) enqueue/dequeue and efficient memory reuse.

| Function | Type | Description |
|----------|------|-------------|
| `enqueuePassenger()` | Base | Advances `rear` circularly `(rear+1) % MAX_BOARDING`, stores passenger, increments `count`. Assigns passengerID from 601. |
| `dequeuePassenger()` | Base | Reads `passengers[front]`, advances `front` circularly, decrements `count`. Prints boarding confirmation. |
| `peekNextPassenger()` | Base | Reads `passengers[front]` without modifying front or count. Shows who boards next. |
| `searchPassenger()` | Base | Iterates using circular index formula `(front+i) % MAX_BOARDING` for all `count` positions. |
| `displayBoardingQueue()` | Base | Same circular iteration printing every passenger; marks `passengers[front]` as "NEXT". |
| `cancelBoarding()` | Base | Finds passenger by ID, shifts subsequent entries to close the gap, adjusts `rear` and `count`. |
| `isBoardingQueueEmpty()` | Base | Returns 1 if `count == 0`. |
| `isBoardingQueueFull()` | Base | Returns 1 if `count == MAX_BOARDING`. |
| `getAverageWaitTime()` | **Extra** | Counts passengers by ticket class (First/Second/Third), computes average queue position, and reports capacity utilisation. |
| `displayBoardingTable()` | Display | Box-drawing table: Position, PassengerID, Name, TrainID, Station, Class, Status. |

### 3.7 Module 7 — Train Maintenance Queue (Queue)

**File:** `src/maintenance_queue.c` | **Header:** `include/maintenance_queue.h`

Trains requiring depot servicing are processed in the order they were submitted — no train jumps the queue regardless of maintenance type or importance. Same **FIFO queue** principle as Module 6, but applied to train records instead of passenger records, with a different extra function.

| Function | Type | Description |
|----------|------|-------------|
| `enqueueForMaintenance()` | Base | Advances `rear` circularly, stores `MaintenanceRecord`, increments `count`. Assigns serviceID from 701. |
| `processNextMaintenance()` | Base | Reads `records[front]`, marks status "In Service", advances `front` circularly, decrements `count`. |
| `peekNextMaintenance()` | Base | Reads `records[front]` without modifying queue. Shows which train is next for service. |
| `searchMaintenance()` | Base | Circular index traversal finding all entries matching a given `trainID`. |
| `displayMaintenanceQueue()` | Base | Full queue display; marks `records[front]` as "NEXT". |
| `cancelMaintenance()` | Base | Finds by serviceID, shifts entries to close the gap, adjusts `rear` and `count`. |
| `isMaintenanceQueueEmpty()` | Base | Returns 1 if `count == 0`. |
| `isMaintenanceQueueFull()` | Base | Returns 1 if `count == MAX_MAINTENANCE`. |
| `countByMaintenanceType()` | **Extra** | Uses `strstr` to match each entry's `maintenanceType` against "Routine", "Repair", and "Emergency". Counts each category and flags if any Emergency entries are present. |
| `displayMaintenanceTable()` | Display | Box-drawing table: ServiceID, TrainID, Type, Depot, Status. |

---

## 4. Sample Outputs

> **How to build and run:**
> ```bash
> gcc -Wall -std=c99 -I. -Iinclude src/main.c src/*.c -o railway_system
> ./railway_system
> ```

### 4.1 System Startup — Main Menu

```
  ╔══════════════════════════════════════════════════════════╗
  ║   🚂  SRI LANKA RAILWAY NETWORK MANAGEMENT SYSTEM       ║
  ║        Colombo Fort Operations Centre                    ║
  ╚══════════════════════════════════════════════════════════╝

  ┌──────────────────────────────────────────────────────────┐
  │            FAMOUS SL RAILWAY TRAINS (Reference)          │
  ├────────────────────────────┬─────────────────────────────┤
  │ Udarata Menike             │ Colombo → Badulla           │
  │ Ruhunu Kumari              │ Colombo → Matara            │
  │ Yal Devi                   │ Colombo → Jaffna            │
  │ Intercity Express          │ Colombo → Kandy             │
  │ Rajarata Rajini            │ Colombo → Vauniya           │
  └────────────────────────────┴─────────────────────────────┘

  ╔══════════════════════════════════════════════════════════╗
  ║                     MAIN MENU                           ║
  ╠══════════════════════════════════════════════════════════╣
  ║  1.  Train Fleet Registry       [Array]                 ║
  ║  2.  Station Directory          [Singly Linked List]    ║
  ║  3.  Journey Log                [Doubly Linked List]    ║
  ║  4.  Train Route Rotation       [Circular Linked List]  ║
  ║  5.  Ticket Cancellation Log    [Stack]                 ║
  ║  6.  Passenger Boarding Queue   [Queue]                 ║
  ║  7.  Train Maintenance Queue    [Queue]                 ║
  ╠══════════════════════════════════════════════════════════╣
  ║  0.  Exit System                                        ║
  ╚══════════════════════════════════════════════════════════╝
  Choice:
```

### 4.2 Module 1 — Train Fleet Registry (Array)

**Registering trains and displaying the fleet:**

```
==============================================================
       TRAIN FLEET REGISTRY  [ARRAY]
==============================================================
  1.  Add Train
  2.  Remove Train
  3.  Update Train Info
  4.  Search Train
  5.  Display Fleet
  6.  Sort by Capacity  [Bubble Sort]
  7.  Calculate Total Seat Capacity  [EXTRA]
  8.  Display Fleet Table
  0.  Back to Main Menu
==============================================================
Choice: 5

ID     Name                           Type         Seats    Load     Status
--------------------------------------------------------------
T101   Udarata Menike                 Express      460      0        Active
T102   Ruhunu Kumari                  Express      380      0        Active
T103   Intercity Express              Intercity    320      0        Active
--------------------------------------------------------------
Total trains: 3 / 50
```

**Bubble Sort by capacity (highest → lowest):**

```
Choice: 6
[+] Fleet sorted by seat capacity (Highest → Lowest).

ID     Name                           Type         Seats    Load     Status
--------------------------------------------------------------
T101   Udarata Menike                 Express      460      0        Active
T102   Ruhunu Kumari                  Express      380      0        Active
T103   Intercity Express              Intercity    320      0        Active
--------------------------------------------------------------
Total trains: 3 / 50
```

**Calculate Total Seat Capacity (Extra Function):**

```
Choice: 7

========== TOTAL SEAT CAPACITY ==========
  All trains (fleet total) : 1160 seats
  Active trains only       : 1160 seats
  Trains in fleet          : 3
  Average per train        : 386.7 seats
==========================================
```

### 4.3 Module 2 — Station Directory (Singly Linked List)

**Displaying the station directory after adding 4 stations:**

```
ID     Name                      Code   Plat  Route                  Status
--------------------------------------------------------------
ST201  Colombo Fort              CMB    6     Colombo-Kandy          Active
ST202  Ragama                    RGM    2     Colombo-Kandy          Active
ST203  Ambepussa                 ABP    1     Colombo-Kandy          Active
ST204  Kandy                     KDY    3     Colombo-Kandy          Active
--------------------------------------------------------------
Total stations: 4
```

**Insertion Sort by station code (A → Z):**

```
Choice: 6
[+] Stations sorted by code (A → Z).

ID     Name                      Code   Plat  Route                  Status
--------------------------------------------------------------
ST203  Ambepussa                 ABP    1     Colombo-Kandy          Active
ST201  Colombo Fort              CMB    6     Colombo-Kandy          Active
ST204  Kandy                     KDY    3     Colombo-Kandy          Active
ST202  Ragama                    RGM    2     Colombo-Kandy          Active
--------------------------------------------------------------
Total stations: 4
```

**Count Stations on Route (Extra Function):**

```
Choice: 7
Enter Route ID to count stations for: 1

========== STATIONS ON ROUTE ==========
  Route ID   : 1
  Route Name : Colombo-Kandy
  Station Count : 4 stations
========================================
```

### 4.4 Module 5 — Ticket Cancellation Log (Stack)

**Stack display (Latest → Oldest, LIFO order):**

```
[CANCELLATION LOG — Latest → Oldest]
No.   CancelID Passenger            TrnID  From            To              Price
--------------------------------------------------------------
1     C503    Kumari Fernando      T103   Colombo Fort    Kandy           Rs.650.00  <- TOP
2     C502    Nimal Perera         T102   Colombo Fort    Galle           Rs.280.00
3     C501    Anusha Silva         T101   Colombo Fort    Kandy           Rs.450.00
--------------------------------------------------------------
Stack depth: 3 cancellations
```

**Peek Latest Cancellation:**

```
[LATEST CANCELLATION — TOP OF STACK]
--------------------------------------------------------------
  Cancel ID   : C503
  Ticket ID   : 1003
  Passenger   : Kumari Fernando
  Train       : T103 — Intercity Express
  Route       : Colombo Fort → Kandy
  Price       : Rs. 650.00
  Reason      : Family emergency
--------------------------------------------------------------
```

**Get Total Refund Amount (Extra Function):**

```
========== TOTAL REFUND AMOUNT ==========
  Cancellations pending : 3
  Total refund due      : Rs. 1380.00
  Average refund        : Rs. 460.00
  Highest single refund : Rs. 650.00
  Lowest single refund  : Rs. 280.00
==========================================
```

**Pop — Reinstate Ticket (Stack LIFO in action):**

```
[CANCELLATION REVERSED — TICKET REINSTATED]
--------------------------------------------------------------
  Cancel ID   : C503
  Ticket ID   : 1003
  Passenger   : Kumari Fernando
  Train       : T103 — Intercity Express
  Route       : Colombo Fort → Kandy
  Date        : 2024-03-15
  Refund      : Rs. 650.00
--------------------------------------------------------------
[+] Ticket reinstated. Stack depth now: 2
```

### 4.5 Module 6 — Passenger Boarding Queue (Queue)

**Boarding queue after 4 passengers join:**

```
Pos  PsnID  Name                   TrnID  Station            Class    Status
--------------------------------------------------------------
1    P601   Silva                  T101   Colombo Fort       First    Waiting    <- NEXT
2    P602   Perera                 T101   Colombo Fort       Second   Waiting
3    P603   Nair                   T101   Colombo Fort       Third    Waiting
4    P604   Hassan                 T101   Colombo Fort       Second   Waiting
--------------------------------------------------------------
Queue: 4 / 100
```

**Peek Next Passenger:**

```
[NEXT TO BOARD]
--------------------------------------------------------------
  P601 — Silva
  Train   : T101 — Udarata Menike
  Class   : First | Ticket: TK001
  Joined  : 08:45
--------------------------------------------------------------
```

**Get Average Wait Time / Class Distribution (Extra Function):**

```
========== BOARDING QUEUE STATUS ==========
  Total Waiting    : 4 passengers
  Average Position : 2.5
  First Class      : 1 passengers
  Second Class     : 2 passengers
  Third Class      : 1 passengers
  Queue Capacity   : 4 / 100 slots used
============================================
```

**Board Next Passenger (FIFO dequeue):**

```
[PASSENGER BOARDING]
--------------------------------------------------------------
  P601 — Silva is now boarding
  Train   : T101 — Udarata Menike
  Station : Colombo Fort
  Class   : First
--------------------------------------------------------------
[+] Passenger boarded. Remaining in queue: 3
```

---

## 5. Discussion

### 5.1 Justification of Data Structures

#### Array — Train Fleet Registry

The national train fleet has a **hard physical upper limit**. Sri Lanka Railways cannot operate more trains than it physically owns. An array with `MAX_TRAINS = 50` directly models this real constraint. Direct index-based access (`fleet[i]`) provides O(1) train lookup by position. Bubble Sort operates **in-place** on the array without requiring auxiliary memory — an appropriate choice for a bounded, contiguous data structure.

**Alternative considered:** A linked list would allow unbounded growth, but this is semantically incorrect for a fixed-capacity fleet. The array's memory layout also benefits CPU cache locality during sort operations.

#### Singly Linked List — Station Directory

The station network is **dynamic** — stations are added when new lines open and removed when stations close for renovation. A singly linked list allocates exactly as much memory as needed (one `malloc` per station) and releases it on removal (one `free`). Insertion and deletion are O(1) when the predecessor is known, without shifting elements. Insertion Sort re-links nodes by alphabetical code without allocating any additional memory — it simply rearranges the existing pointer structure.

**Alternative considered:** An array would require pre-sizing for worst-case station count, wasting memory, and would require shifting elements on every insertion or deletion.

#### Doubly Linked List — Journey Log

Journey logs are accessed **bidirectionally** — forward in time (to see the most recent journeys) and backward in time (to investigate the history of a specific delay or train). A doubly linked list provides both `next` (newer) and `prev` (older) pointers, making backward traversal `traverseBackward()` a native O(1) per-step operation. A singly linked list cannot traverse backwards without reversing or caching the entire list. A tail pointer (`journeyTail`) makes appending new records O(1).

**Alternative considered:** A doubly linked list is the only standard linear structure that provides native bidirectional traversal. Arrays provide random access but not dynamic growth. Singly lists lack backward traversal.

#### Circular Linked List — Train Route Rotation

Train scheduling is an **endless rotation** — after the last train's deployment, the schedule returns to the first. There is no "end" to the list; the last node's `next` points back to the head. This circular property eliminates boundary checks from `nextTrainOnRoute()` — the operation that advances the active train pointer always succeeds. A regular linked list would require explicit wrapping logic and boundary checks. Arrays would need modular arithmetic for index wrapping. The circular list is the most natural model for a repeating, boundless schedule.

**The `getRouteSize()` function** demonstrates how circular traversal differs from linear traversal: because there is no NULL terminator, the function must use a `do-while` loop and stop when the pointer loops back to `currentTrain`.

#### Stack — Ticket Cancellation Log

Ticket cancellations follow **LIFO semantics** naturally: the most recently cancelled ticket is always the first candidate for reinstatement (undo). `pushCancellation()` records a new cancellation; `popCancellation()` reinstates the most recent one. `peekLastCancellation()` allows review without committing to reinstatement. An array-based stack is appropriate because the maximum number of pending cancellations per session is bounded — no dynamic allocation is needed, and the `top` pointer directly identifies both the most recent entry and the current stack depth.

**Sorting is not applicable** to a cancellation log — the LIFO ordering itself is the meaningful order; sorting by date or amount would destroy the temporal audit trail.

#### Queue — Passenger Boarding and Train Maintenance

**FIFO** is the only fair ordering for both platform boarding and maintenance scheduling:
- Passengers board in the order they arrived at the platform — no exceptions, no priority (apart from ticket class which is a separate seating assignment concern).
- Trains are serviced in the order submitted to the depot — preventing any train from jumping the queue based on train type or importance.

The **circular array** implementation (advancing `front` and `rear` modulo `MAX_*` capacity) reuses memory slots freed by dequeued entries without shifting, keeping enqueue and dequeue at O(1).

**Using Queue twice** is justified by the identical behavioural requirement (FIFO) but with entirely different data types and different extra functions:
- Module 6 processes `Passenger` structs with `getAverageWaitTime()` (class distribution metric).
- Module 7 processes `MaintenanceRecord` structs with `countByMaintenanceType()` (maintenance urgency metric).

### 5.2 Justification of Sorting Algorithms

| Algorithm | Module | Time Complexity | Justification |
|-----------|--------|-----------------|---------------|
| **Bubble Sort** | Train Fleet (Array) | O(n²) worst / O(n) best | In-place, no extra memory; early-exit optimises nearly-sorted arrays. Appropriate for small fleet (max 50 trains). |
| **Insertion Sort** | Station Directory (Singly LL) | O(n²) worst / O(n) best | Works by re-linking nodes — avoids element shifting. Natural fit for linked lists. Efficient on nearly-sorted data. |
| **Selection Sort** | Journey Log (Doubly LL) | O(n²) always | Swaps data fields between nodes without touching `prev`/`next` pointers. Minimises write operations (only n-1 swaps). Demonstrates mastery of DLL pointer preservation during sorting. |

### 5.3 Extra Function Design Philosophy

Each extra function computes an **aggregate over the entire data structure** — not a search (which returns one element by key) and not a display (which renders all elements). This makes them computationally distinct from base operations:

| Module | Function | Computation | Operational Value |
|--------|----------|-------------|-------------------|
| 1 | `calculateTotalSeatCapacity()` | SUM of all `seatCapacity` | Fleet-wide passenger capacity planning |
| 2 | `countStationsOnRoute()` | Filtered COUNT by `routeID` | Route-level infrastructure planning |
| 3 | `calculateJourneyDistance()` | SUM of `distanceKm` per train | Train utilisation and mileage tracking |
| 4 | `getRouteSize()` | Structural COUNT via circular traversal | Rotation cycle management |
| 5 | `getTotalRefundAmount()` | SUM of `ticketPrice` across stack | Financial liability reporting |
| 6 | `getAverageWaitTime()` | AVERAGE position + class distribution | Platform resource allocation |
| 7 | `countByMaintenanceType()` | Conditional COUNT by type | Maintenance urgency prioritisation |

### 5.4 Module Integration

The `trainID` and `stationID` keys connect all modules in a way that mirrors real railway department communication:

- Adding a train in Module 1 produces `trainID = T101`.
- A journey in Module 3 references `trainID = T101` and `stationID = ST201`.
- The same `trainID = T101` appears in the Route Rotation (Module 4), Cancellation Log (Module 5), and Maintenance Queue (Module 7).
- `stationID = ST201` from the Station Directory is referenced in the Boarding Queue (Module 6).

This referential structure demonstrates how independent subsystems share a common data language in a real enterprise system.

---

## 6. Conclusion

### 6.1 What We Learned

This project deepened our understanding of data structures beyond textbook definitions into **practical, justified application**. Key insights:

1. **Data structure choice must match the problem's natural behaviour.** An array is not "simple" — it is precisely correct when capacity is bounded. A circular linked list is not "complex" — it is the most natural model for a repeating schedule. Choosing the right structure reduces both code complexity and logical errors.

2. **Pointer manipulation requires careful bookkeeping.** The doubly linked list's four-case removal function (head, tail, middle, only node) and the circular linked list's traversal termination condition (`do-while` instead of `while (curr != NULL)`) demonstrated that pointer-based structures require systematic thinking about every possible state the structure can be in.

3. **Sorting algorithms behave differently on different data structures.** Bubble Sort on an array benefits from memory locality. Insertion Sort on a linked list avoids element shifting by re-linking nodes — a fundamentally different operation from its array version. Selection Sort on a doubly linked list preserves structural pointers by swapping data rather than nodes.

4. **Modular design enables parallel development.** With clearly defined interfaces (header files declaring function prototypes and structs) and universal keys (trainID, stationID), seven team members developed independent modules that integrate cleanly.

5. **Boundary conditions are the hardest part.** Every function guards against empty structures, full structures, not-found conditions, and single-element edge cases. Writing robust boundary checks requires more thought than the core logic.

### 6.2 Challenges Faced and How We Overcame Them

| Challenge | Solution |
|-----------|----------|
| **Circular LL termination**: `while (curr != NULL)` loops forever in a circular list. | Switched to bounded `do-while` loops counting exactly `rotationCount` steps, or `do { ... } while (curr != currentTrain)` pattern. |
| **Doubly LL removal edge cases**: Four distinct pointer update scenarios depending on position. | Drew out each case on paper before coding, identified which pointers change in each scenario, then implemented and tested each case independently. |
| **Queue circular indexing**: Rear wrapping to the start of the array when it reaches capacity. | Used modular arithmetic: `rear = (rear + 1) % MAX_SIZE` and `front = (front + 1) % MAX_SIZE`, maintaining a separate `count` field to distinguish empty from full. |
| **Module integration via keys**: Ensuring trainID and stationID are consistent across modules. | Centralised ID generation (Module 1 assigns T101+, Module 2 assigns ST201+) and provided `findTrainByID()` and `findStationByID()` helper functions for cross-module reference. |
| **Memory management**: `malloc` without `free` causes leaks; `free` without re-linking causes dangling pointers. | Adopted the discipline: always re-link neighbours before calling `free`; always `free` after unlinking. Memory correctness was verified during development using Valgrind (`valgrind --leak-check=full ./railway_system`), which confirmed zero memory leaks across all modules. |
| **scanf and input buffering**: `scanf("%d")` leaves a newline in the buffer, causing subsequent `scanf(" %[^\n]")` reads to pick up empty strings. | Used `scanf(" %[^\n]", buf)` with a leading space to skip whitespace including the residual newline from the previous integer read. |

### 6.3 Future Improvements

With more development time, the following enhancements would be valuable:

- **Persistent storage**: Save all module data to binary files on exit and reload on startup, so records survive between sessions.
- **Real-time timetable**: Integrate the system clock so journey departure times and maintenance schedules are validated against actual time.
- **Priority Queue for maintenance**: Emergency maintenance should perhaps preempt routine services — a min-heap or priority queue would implement this.
- **Hash table for fast lookup**: Searching by trainID currently requires O(n) traversal in linked-list modules; a hash table would reduce this to O(1) average case.
- **Graph for route mapping**: The station network is naturally a weighted graph (stations as vertices, rail lines as edges with distances and travel times). Dijkstra's algorithm could compute optimal journeys.

---

## References

1. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
2. Kernighan, B. W., & Ritchie, D. M. (1988). *The C Programming Language* (2nd ed.). Prentice Hall.
3. Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley.
4. Sri Lanka Railways — Official Network Map. *Department of Railways, Sri Lanka.*
5. University of Moratuwa, Department of Computer Science & Engineering — CS2042: Data Structures & Algorithms course materials.
