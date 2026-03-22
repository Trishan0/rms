# 🚂 Sri Lanka Railway Network Management System

A CLI-based railway network management system built in **C**, implementing **7 data structures** across 7 independent modules. Developed as a semester group assignment for a Data Structures & Algorithms course at the University of Moratuwa.

---

## 👥 Team

| Member | Module | Data Structure | Sort Algorithm |
|--------|--------|---------------|----------------|
| Member 1 | Train Fleet Registry | Array | Bubble Sort |
| Member 2 | Station Directory | Singly Linked List | Insertion Sort |
| Member 3 | Journey Log | Doubly Linked List | Selection Sort |
| Member 4 | Train Route Rotation | Circular Linked List | — |
| Member 5 | Seat Reservation Management | Array (2nd use) | Bubble Sort |
| Member 6 | Passenger Boarding Queue | Queue | — |
| Member 7 | Train Maintenance Queue | Queue (2nd use) | — |

---

## 📋 System Overview

This system models the full operational flow of a national railway network — from train fleet management and station directory to journey logging, seat reservations, passenger boarding and depot maintenance. Every module solves a real railway operations problem and maps to a specific data structure for a justified reason.

```
Train Added to Fleet
        │
        ▼
[Array]          Train registered → trainID assigned
        │
        ├──► [Singly LL]    Station added to route directory
        │
        ├──► [Circular LL]  Train added to route rotation cycle
        │         │
        │         └──► nextTrainOnRoute() → train departs
        │
        ├──► [Queue]        Passengers queue up to board at platform
        │
        ├──► [Doubly LL]    Journey logged with distance & departure time
        │         (navigate backward = older trips, forward = latest)
        │
        ├──► [Array]        Seat reserved or released on a specific train
        │         (direct O(1) access by seat number)
        │
        └──► [Queue]        Train submitted for depot maintenance
                    (processed in submission order — FIFO)
```

---

## 🗂️ Project Structure

```
railway-network-management/
│
├── main.c                          ← Master menu & entry point
│
├── include/                        ← Header files
│   ├── shared_types.h              ← Common constants & macros
│   ├── train_fleet.h               ← Member 1
│   ├── station_directory.h         ← Member 2
│   ├── journey_log.h               ← Member 3
│   ├── route_rotation.h            ← Member 4
│   ├── seat_reservations.h         ← Member 5
│   ├── boarding_queue.h            ← Member 6
│   └── maintenance_queue.h         ← Member 7
│
├── src/                            ← Implementation files
│   ├── train_fleet.c               ← Member 1
│   ├── station_directory.c         ← Member 2
│   ├── journey_log.c               ← Member 3
│   ├── route_rotation.c            ← Member 4
│   ├── seat_reservations.c         ← Member 5
│   ├── boarding_queue.c            ← Member 6
│   └── maintenance_queue.c         ← Member 7
│
├── Makefile                        ← Build configuration
└── README.md
```

---

## ⚙️ How to Build & Run

### Prerequisites
- GCC compiler
- VS Code (recommended) or any terminal

### Compile & Run

**Using Makefile:**
```bash
make          # compile only
make run      # compile and run
make clean    # remove compiled output
```

**Using GCC directly:**
```bash
gcc -Wall -std=c99 -Iinclude main.c src/*.c -o railway_system
./railway_system
```

---

## 🖥️ Main Menu

```
  ╔══════════════════════════════════════════════════════════╗
  ║   🚂  SRI LANKA RAILWAY NETWORK MANAGEMENT SYSTEM       ║
  ║        Colombo Fort Operations Centre                    ║
  ╚══════════════════════════════════════════════════════════╝

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
```

---

## 📦 Module Details

### 1. 🚂 Train Fleet Registry — `Array`
Stores all trains in the Sri Lanka Railways fleet in a fixed-capacity array, modelling the real constraint of a national rail network.

**Base Operations:** `addTrain` `removeTrain` `updateTrainInfo` `searchTrain` `displayFleet` `isFleetEmpty` `isFleetFull`

**Sort:** `bubbleSortByCapacity` — sorts trains from highest to lowest seat count

**Extra:** `calculateTotalSeatCapacity` — SUM of all seat counts across the entire fleet array

---

### 2. 🏢 Station Directory — `Singly Linked List`
Dynamically manages all railway stations. Stations are added and removed as the network expands — a linked list grows and shrinks naturally.

**Base Operations:** `addStation` `removeStation` `updateStationInfo` `searchStation` `displayAllStations`

**Sort:** `insertionSortByCode` — sorts stations alphabetically by station code by relinking nodes

**Extra:** `countStationsOnRoute` — FILTERED COUNT of nodes matching a specific routeID

---

### 3. 📋 Journey Log — `Doubly Linked List`
Logs every train journey. Controllers scroll **forward** to see latest journeys and **backward** to investigate past delays. Only a Doubly LL supports both directions natively.

**Base Operations:** `addJourneyRecord` `removeJourneyRecord` `updateJourneyStatus` `searchJourneyRecord` `displayAllJourneys` `traverseForward` `traverseBackward`

**Sort:** `selectionSortByDeparture` — sorts journeys chronologically by departure time

**Extra:** `calculateJourneyDistance` — SUM of distanceKm fields across all journeys for a specific train

---

### 4. 🔄 Train Route Rotation — `Circular Linked List`
Cycles trains through route deployments endlessly. After the last train's trip the rotation loops back to the first — no NULL terminator, just a continuous cycle.

**Base Operations:** `addTrainToRoute` `removeTrainFromRoute` `updateRouteInfo` `searchTrainInRoute` `displayRouteRotation`

**Navigation:** `nextTrainOnRoute` `getCurrentTrain` — the defining operations of a Circular LL

**Extra:** `getRouteSize` — manually COUNT nodes via circular traversal since there is no NULL end point

---

### 5. 🎫 Ticket Cancellation Log — `Stack`
Records every ticket cancellation in LIFO order. If a cancellation was made by mistake, pop it to reinstate the ticket. The top of the stack is always the most recent cancellation.

**Base Operations:** `loadTrainSeats` `reserveSeat` `releaseSeat` `updateReservation` `searchSeat` `displaySeatMap` `isSeatMapEmpty`

**Extra:** `countAvailableSeats` — CONDITIONAL COUNT scanning array for Available seats, reports occupancy % and class breakdown

---

### 6. 🧍 Passenger Boarding Queue — `Queue`
Manages passengers waiting to board at the platform. First passenger to join is first to board — strictly FIFO, exactly how real platform boarding works.

**Base Operations:** `enqueuePassenger` `dequeuePassenger` `peekNextPassenger` `searchPassenger` `displayBoardingQueue` `cancelBoarding` `isBoardingQueueEmpty` `isBoardingQueueFull`

**Extra:** `getAverageWaitTime` — AVERAGE position metric and class distribution across all queue slots

---

### 7. 🔧 Train Maintenance Queue — `Queue`
Manages trains waiting for depot servicing in submission order. Ensures no train skips its scheduled maintenance regardless of type or importance.

**Base Operations:** `enqueueForMaintenance` `processNextMaintenance` `peekNextMaintenance` `searchMaintenance` `displayMaintenanceQueue` `cancelMaintenance` `isMaintenanceQueueEmpty` `isMaintenanceQueueFull`

**Extra:** `countByMaintenanceType` — CONDITIONAL COUNT of entries by type: Routine / Repair / Emergency

---

## 🔗 Module Integration

All modules are linked through two universal keys:

```c
trainID    →  assigned in Train Fleet Registry (Module 1)
              used in Journey Log, Route Rotation, Maintenance Queue, Seat Reservations

stationID  →  assigned in Station Directory (Module 2)
              used in Journey Log, Boarding Queue
```

---

## 🎯 Extra Function Summary — Why Each Is Valid

| Member | Extra Function | Type | What It Computes |
|--------|---------------|------|-----------------|
| 1 | `calculateTotalSeatCapacity()` | Aggregate SUM | Total seats across entire fleet array |
| 2 | `countStationsOnRoute()` | Filtered COUNT | Stations matching a given routeID |
| 3 | `calculateJourneyDistance()` | Aggregate SUM | Total km travelled by a specific train |
| 4 | `getRouteSize()` | Structural COUNT | Nodes in circular cycle via manual traversal |
| 5 | `countAvailableSeats()` | Conditional COUNT | Available seats on loaded train, by class |
| 6 | `getAverageWaitTime()` | Aggregate AVERAGE | Queue depth metric and class distribution |
| 7 | `countByMaintenanceType()` | Conditional COUNT | Entries per maintenance type in queue |

> Every extra function is a **computation or aggregate on DS data** — not a search, not a display, not a boundary check.

---

## 📌 DS Rule Verification

```
Array           → used 2 times ✅  (max allowed: 3)
Singly LL       → used 1 time  ✅  (max allowed: 3)
Doubly LL       → used 1 time  ✅  (max allowed: 3)
Circular LL     → used 1 time  ✅  (max allowed: 3)
Queue           → used 2 times ✅  (max allowed: 3)
Stack           → not used      (no genuinely honest use case in this domain)
```

---

## 🛠️ Tech Stack

- **Language:** C (C99 standard)
- **Compiler:** GCC
- **IDE:** VS Code
- **Version Control:** Git & GitHub

---

## 📌 Assignment Context

- **Course:** Data Structures & Algorithms
- **Institution:** University of Moratuwa
- **Requirement:** 7 data structures, base operations per module, sorting algorithms, at least 1 genuine extra function per member
- **Data Structures Used:** Array (×2), Singly LL, Doubly LL, Circular LL, Queue (×2)
- **Sorting Algorithms:** Bubble Sort, Insertion Sort, Selection Sort
