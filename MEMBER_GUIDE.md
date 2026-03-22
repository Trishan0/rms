# 👥 Member Guide — Sri Lanka Railway Network Management System

> This document is the complete reference for every team member.
> It covers the story behind your data structure, why it was chosen,
> what every function does, and how to test your module.

---

## 🔗 Universal Keys — How All Modules Connect

```
trainID    → created in Module 1 (Train Fleet)
             used in Module 3 (Journey Log)
             used in Module 4 (Route Rotation)
             used in Module 5 (Seat Reservations)
             used in Module 7 (Maintenance Queue)

stationID  → created in Module 2 (Station Directory)
             used in Module 3 (Journey Log)
             used in Module 6 (Boarding Queue)
```

Every module is independent but speaks the same language through these two keys. When you add a journey in Module 3, you reference a `trainID` from Module 1 and a `stationID` from Module 2.

---

---

# 👤 Member 1 — Train Fleet Registry
**File:** `src/train_fleet.c` | **Header:** `include/train_fleet.h`
**Data Structure:** `Array`
**Sort:** `Bubble Sort — by seat capacity`

---

## 📖 The Story

Sri Lanka Railways operates a fixed fleet of trains. The network cannot suddenly run 200 trains if it only owns 50. This hard physical limit — the maximum number of trains the fleet can hold — is exactly what an **Array** models.

Every train gets a slot in the array. When the array is full, the fleet is at capacity. No dynamic resizing, no hidden memory allocation — just a clean, bounded collection of trains that mirrors the real constraint of national rail infrastructure.

Bubble Sort is used here because it works **in-place on the array** — no extra memory needed. It repeatedly compares adjacent trains and swaps them until the highest-capacity trains float to the top, so operations staff always see the most capable trains first.

## 🏗️ Why Array?

| Reason | Explanation |
|--------|-------------|
| Fixed capacity | Railway fleet has a hard maximum — array enforces this naturally |
| Direct access | Find any train by index in O(1) — no traversal needed |
| In-place sort | Bubble Sort needs zero extra memory — sorts the array itself |
| Simple structure | No pointers, no malloc — cleanest possible implementation |

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `addTrain()` | Base | Registers a new train into the next available array slot. Prompts for name, type, capacity, depot and route. Assigns a unique trainID starting from 101. Sets currentLoad to 0 and status to Active by default. |
| `removeTrain()` | Base | Finds a train by ID, prints its name, then shifts all trains after it one position left to close the gap. Decrements trainCount. |
| `updateTrainInfo()` | Base | Finds a train by ID and lets the user update one of four fields — status, seat capacity, depot, or current passenger load. |
| `searchTrain()` | Base | Searches by trainID (exact match, prints full details) or by name (partial match using strstr, lists all matches). |
| `displayFleet()` | Base | Traverses array from index 0 to trainCount-1 and prints each train in a plain row. Shows totals at the bottom. |
| `isFleetEmpty()` | Base | Returns 1 if trainCount is 0. Used as boundary check before any operation. |
| `isFleetFull()` | Base | Returns 1 if trainCount equals MAX_TRAINS. Used before addTrain to prevent overflow. |
| `bubbleSortByCapacity()` | Sort | Compares adjacent pairs, swaps if left train has lower capacity than right. Includes early-exit optimization — stops if a full pass completes with no swaps. Calls displayFleet after sorting. |
| `calculateTotalSeatCapacity()` | **EXTRA** | Traverses the full array summing every train's seatCapacity. Also computes active-only total and average per train. Answers: *"What is the total passenger capacity of the entire SL Railways fleet?"* |
| `displayFleetTable()` | Display | Prints a formatted box-style table using box-drawing characters with columns for ID, name, type, seats, load and status. |

## 🧪 Test Scenario

```
1. Add 3 trains:
   - Udarata Menike,  Express,   460 seats, Colombo Depot
   - Ruhunu Kumari,   Express,   380 seats, Matara Depot
   - Intercity Exp,   Intercity, 320 seats, Colombo Depot

2. Run bubbleSortByCapacity()
   Expected order: Udarata(460) → Ruhunu(380) → Intercity(320)

3. Run calculateTotalSeatCapacity()
   Expected: Total = 1160 seats, Average = 386.7 seats

4. Run searchTrain() by name "Kumari"
   Expected: Ruhunu Kumari appears
```

---

---

# 👤 Member 2 — Station Directory
**File:** `src/station_directory.c` | **Header:** `include/station_directory.h`
**Data Structure:** `Singly Linked List`
**Sort:** `Insertion Sort — by station code`

---

## 📖 The Story

Sri Lanka Railways is always expanding. New stations open, old ones close for renovation, some get reclassified. The list of stations is **never truly fixed** — it grows and shrinks over time.

This is exactly why a **Singly Linked List** is used. Unlike an array, a linked list has no fixed size — it allocates memory for exactly as many stations as currently exist, no more and no less. Each station is a node, and each node points to the next one in the directory.

Insertion Sort works elegantly on linked lists — instead of shifting array elements, it re-links nodes into the correct sorted position. Sorting by station code gives alphabetical order so staff can look up any station quickly.

## 🏗️ Why Singly Linked List?

| Reason | Explanation |
|--------|-------------|
| Dynamic size | Station count changes as network expands — LL handles this naturally |
| No wasted memory | Only allocates memory for stations that actually exist |
| Easy insertion/deletion | Add or remove a node without shifting anything |
| Insertion sort fits | Re-linking nodes for sorting is more elegant than shifting array elements |

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `addStation()` | Base | Allocates a new StationNode using malloc. Fills in name, code, routeID, route name, platform count and district. Sets status to Active. Appends to the end of the list. Assigns stationID starting from 201. |
| `removeStation()` | Base | Handles two cases — removing the head node (updates stationHead pointer) and removing a middle/tail node (re-links prev node's next pointer). Calls free() after unlinking. |
| `updateStationInfo()` | Base | Traverses until matching stationID found. Allows updating platform count, status, or route assignment. |
| `searchStation()` | Base | By ID: exact match, prints full station details in a block. By name: partial match using strstr, prints a summary row for every match. |
| `displayAllStations()` | Base | Traverses from stationHead to NULL printing every node. Shows total count at the bottom. |
| `insertionSortByCode()` | Sort | Builds a new sorted list by taking each node from the original list and inserting it at the correct position by comparing stationCode strings. Sets stationHead to the new sorted list when done. Calls displayAllStations after sorting. |
| `countStationsOnRoute()` | **EXTRA** | Asks for a routeID. Traverses the entire list counting nodes where routeID matches. Also captures the route name from the first match. Prints count and route name. Answers: *"How many stations are on the Colombo-Kandy line?"* |
| `displayStationTable()` | Display | Formatted box table with columns for ID, name, code, platforms, route and status. |
| `findStationByID()` | Helper | Takes a stationID integer and returns a pointer to that StationNode, or NULL. Used by other modules to validate station references. |

## 🧪 Test Scenario

```
1. Add 4 stations on Route 1 (Colombo-Kandy):
   - Colombo Fort  (CMB), Route 1, 6 platforms
   - Ragama        (RGM), Route 1, 2 platforms
   - Ambepussa     (ABP), Route 1, 1 platform
   - Kandy         (KDY), Route 1, 3 platforms

2. Run insertionSortByCode()
   Expected order: ABP → CMB → KDY → RGM (alphabetical)

3. Run countStationsOnRoute(1)
   Expected: 4 stations on Colombo-Kandy route

4. Remove Ambepussa, run countStationsOnRoute(1)
   Expected: 3 stations remaining
```

---

---

# 👤 Member 3 — Journey Log
**File:** `src/journey_log.c` | **Header:** `include/journey_log.h`
**Data Structure:** `Doubly Linked List`
**Sort:** `Selection Sort — by departure time`

---

## 📖 The Story

Every time a train departs it creates a journey record — which train, from where, to where, what time, how far, any delays. Over days and weeks, hundreds of these records accumulate in the log.

A controller investigating a delay needs to **scroll backward** through recent journeys to see when a train first started running late. A planner checking the timetable needs to **scroll forward** to see upcoming departures in chronological order.

This bidirectional navigation — forward through time, backward through history — is the defining capability of a **Doubly Linked List**. Each node has both a `next` pointer (to the newer journey) and a `prev` pointer (to the older one). No other data structure provides both directions natively.

## 🏗️ Why Doubly Linked List?

| Reason | Explanation |
|--------|-------------|
| Bidirectional navigation | Controllers scroll both forward and backward through journey history |
| Dynamic growth | Journey records are added continuously throughout operations |
| Tail pointer | Appending to tail is O(1) — no traversal needed to add new records |
| Selection sort | Sorting DLL by swapping data demonstrates mastery of prev/next pointers |

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `addJourneyRecord()` | Base | Allocates a new JourneyNode and appends it to journeyTail. Sets both prev and next pointers correctly. Updates journeyHead if first node, updates journeyTail for every append. Assigns journeyID starting from 301. |
| `removeJourneyRecord()` | Base | Handles four cases — removing head (update journeyHead), removing tail (update journeyTail), removing middle node (re-link both neighbours), removing the only node (set both to NULL). Calls free after unlinking. |
| `updateJourneyStatus()` | Base | Finds journey by ID and allows updating status, delay minutes, or arrival time. |
| `searchJourneyRecord()` | Base | By journeyID: exact match with full detail block. By trainID: lists all journeys belonging to that train. |
| `displayAllJourneys()` | Base | Forward traversal from journeyHead printing every record. |
| `traverseForward()` | Base | Walks from journeyHead using next pointers, printing each journey as a numbered step. Oldest journey = Step 1. |
| `traverseBackward()` | Base | Walks from journeyTail using prev pointers. This is the key capability of Doubly LL — Singly LL cannot do this. Latest journey = Step 1. |
| `selectionSortByDeparture()` | Sort | In each pass, finds the node with the lexicographically earliest departureTime in the unsorted portion. Swaps all data fields between that node and the current position, leaving prev/next pointers untouched. Calls displayAllJourneys after sorting. |
| `calculateJourneyDistance()` | **EXTRA** | Asks for a trainID. Traverses all DLL nodes summing distanceKm where trainID matches. Also counts trips and computes average distance per trip. Answers: *"What is the total distance covered by this train across all logged journeys?"* |
| `displayJourneyTable()` | Display | Formatted box table with columns for journey ID, train, from, to, departure, distance and status. |

## 🧪 Test Scenario

```
1. Add 3 journeys for Train T101 (Udarata Menike):
   - J301: CMB → KDY, 09:00, 121.0 km, On Time
   - J302: KDY → CMB, 14:00, 121.0 km, Delayed 15min
   - J303: CMB → KDY, 09:00 next day, 121.0 km, On Time

2. Run traverseForward()
   Expected: J301 → J302 → J303

3. Run traverseBackward()
   Expected: J303 → J302 → J301

4. Run calculateJourneyDistance(101)
   Expected: Total = 363.0 km, 3 trips, Avg = 121.0 km
```

---

---

# 👤 Member 4 — Train Route Rotation
**File:** `src/route_rotation.c` | **Header:** `include/route_rotation.h`
**Data Structure:** `Circular Linked List`
**Sort:** None

---

## 📖 The Story

The Colombo-Kandy route runs all day. When Train A completes its morning trip and returns, Train B takes the afternoon slot. When Train B returns, Train C handles the evening. After Train C's last trip — it cycles back to Train A for the next morning.

This rotation **never ends**. There is no "last" train in the schedule. After the final slot, the cycle returns to the beginning. That endless loop is precisely what a **Circular Linked List** models — the last node's `next` pointer points back to the head node instead of NULL.

A regular linked list would stop. An array would need boundary checks. Only a circular linked list naturally and continuously loops — exactly like real train scheduling.

## 🏗️ Why Circular Linked List?

| Reason | Explanation |
|--------|-------------|
| Endless rotation | Train schedules loop forever — circular list has no NULL end point |
| Fair deployment | Each train gets its turn automatically in cycle order |
| No boundary check | nextTrainOnRoute always works — no end-of-list condition |
| Real scheduling model | Actual railway scheduling uses this exact rotation logic |

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `addTrainToRoute()` | Base | If cycle is empty, node points to itself. Otherwise, finds the last node (whose next equals currentTrain) and inserts new node before the head, maintaining the circular link. Increments rotationCount. |
| `removeTrainFromRoute()` | Base | Handles the special case of removing the only node (sets everything to NULL). For multi-node cycles, finds the predecessor node and re-links it to skip the removed node. If removing currentTrain, advances currentTrain first. |
| `updateRouteInfo()` | Base | Traverses cycle for exactly rotationCount steps (to avoid infinite loop) looking for the trainID to update schedule time or direction. |
| `searchTrainInRoute()` | Base | Same bounded traversal — prints full details if found including whether it is currently the active train. |
| `displayRouteRotation()` | Base | Traverses exactly rotationCount steps from currentTrain, marking the current node with an arrow. Prints a message showing the cycle loops back to the top. |
| `nextTrainOnRoute()` | Navigation | Advances currentTrain to currentTrain->next. Increments tripsCompleted for the newly active train. This is the core circular operation. |
| `getCurrentTrain()` | Navigation | Prints full details of the node currentTrain is pointing to without advancing the pointer. |
| `getRouteSize()` | **EXTRA** | Traverses the circular cycle using a do-while loop — starts at currentTrain, counts each node, stops when it loops back to currentTrain. Necessary because circular list has no NULL to detect the end. Returns the count. Answers: *"How many trains are in this route's rotation cycle?"* |
| `displayRotationTable()` | Display | Formatted box table showing all trains in cycle with their schedule, direction and trips completed. Marks active train clearly. |

## 🧪 Test Scenario

```
1. Add 3 trains to Colombo-Kandy route:
   - T101 Udarata Menike,  06:00, Northbound
   - T102 Intercity Exp,   10:00, Northbound
   - T103 Night Mail,      22:00, Northbound

2. Call nextTrainOnRoute() 4 times
   Expected rotation: T102 → T103 → T101 → T102 (cycles back)

3. Call getRouteSize()
   Expected: 3 trains in cycle

4. Remove T102, call getRouteSize()
   Expected: 2 trains remaining in cycle
```

---

---

---

# 👤 Member 5 — Seat Reservation Management
**File:** `src/seat_reservations.c` | **Header:** `include/seat_reservations.h`
**Data Structure:** `Array (2nd use)`
**Sort:** `Bubble Sort — by seat number`

---

## 📖 The Story

A passenger walks up to the ticket counter at Colombo Fort and asks for Seat 24 on the Udarata Menike to Badulla. The booking clerk needs to check instantly — is that seat taken? Who is sitting next to it? How many First Class seats are still open?

Every train has a **fixed, unchanging number of seats**. The Udarata Menike always has exactly 460 seats. Not 459 today and 461 tomorrow — always 460. This hard physical constraint is what makes an **Array** the perfect data structure.

Each seat gets a slot in the array at index `seatNumber - 1`. Checking seat 24 means going directly to `seatMap[23]` — no searching, no traversal, just direct access in O(1). This is exactly how a booking system needs to work when passengers are waiting at the counter.

## 🏗️ Why Array? (And Why Array Twice?)

| Reason | Explanation |
|--------|-------------|
| Fixed seat count | A train's seats never change — array models this physical limit |
| Direct access | `seatMap[seatNum - 1]` is O(1) — no traversal to find a seat |
| In-place sort | Bubble Sort reorders the seat map with no extra memory |
| Different from Module 1 | Module 1 stores trains, Module 5 stores seats — different entity, different size, different purpose |

**Examiner question: "Why Array twice?"**
```
Module 1 [Array]: Fixed number of TRAINS owned by railway
                  One array for the whole system
                  Indexed by trainID
                  Sorted by capacity

Module 5 [Array]: Fixed number of SEATS on one train
                  One array per train loaded
                  Indexed directly by seat number
                  Sorted by seat number

Different entity. Different array size. Different purpose.
Both are genuinely bounded — Array is correct both times.
```

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `loadTrainSeats()` | Base | Initialises a fresh seat map array for a specific train. Takes trainID, name, total seats and first/second class counts. Assigns seatClass to every element based on seat number ranges. Sets all seats to Available. |
| `reserveSeat()` | Base | Takes a seat number, accesses `seatMap[seatNum-1]` directly in O(1). Checks if already reserved. Fills in passenger name, NIC, journey date and reserved time. Sets status to Reserved. |
| `releaseSeat()` | Base | Direct array access by seat number. Checks if the seat is actually reserved first. Clears all passenger fields and sets status back to Available. |
| `updateReservation()` | Base | Direct array access by seat number. Checks seat is Reserved. Updates one of three fields — passenger name, NIC, or journey date. |
| `searchSeat()` | Base | By seat number: direct O(1) access, prints full details. By passenger name: linear scan using strstr across all array elements. |
| `displaySeatMap()` | Base | Linear traversal from index 0 to totalSeats-1 printing every seat's number, class, status and passenger. |
| `isSeatMapEmpty()` | Base | Returns 1 if currentTrainID is -1, meaning no train has been loaded yet. |
| `bubbleSortBySeatNumber()` | Sort | Adjacent comparison and swap until seat array is ordered 1 to N. Includes early-exit if no swaps in a pass. Useful after any manual reordering. |
| `countAvailableSeats()` | **EXTRA** | Scans every element in the array counting those where status equals Available. Reports total available, reserved, occupancy percentage and breakdown by First, Second and Third class. |
| `displaySeatTable()` | Display | Formatted table showing seat number, class, status, passenger name and journey date for every seat in the array. Shows total availability count at the bottom. |

## 🧪 Test Scenario

```
1. Load seat map for T101 Udarata Menike
   Total seats: 10
   First class: 2, Second class: 4, Third: 4

2. Reserve seat 1 for Kamal Perera, 2025-04-15
   Reserve seat 3 for Nimal Silva,  2025-04-15
   Reserve seat 7 for Amali Dias,   2025-04-15

3. Run countAvailableSeats()
   Expected: Available=7, Reserved=3, Occupancy=30%
   First=1 available, Second=4, Third=2

4. Run searchSeat() by name "Silva"
   Expected: Seat 3 Nimal Silva found

5. Release seat 3
   Expected: Seat 3 back to Available

6. Run countAvailableSeats() again
   Expected: Available=8, Reserved=2, Occupancy=20%

7. Run bubbleSortBySeatNumber()
   Expected: Seats ordered 1 -> 10
```

---

# 👤 Member 6 — Passenger Boarding Queue
**File:** `src/boarding_queue.c` | **Header:** `include/boarding_queue.h`
**Data Structure:** `Queue`
**Sort:** None

---

## 📖 The Story

Platform 1 at Colombo Fort Station. The Udarata Menike is arriving in 10 minutes. Passengers line up at the platform gate. The first passenger who joined the queue boards first. The last passenger who arrived boards last.

No cutting in line. No favouritism. **First come, first served.**

This is a **Queue** — First-In First-Out. New passengers join at the rear. Boarding happens from the front. Implemented as a circular array so that when the rear pointer reaches the end of the array it wraps back to the start, reusing slots that were freed when passengers boarded.

## 🏗️ Why Queue?

| Reason | Explanation |
|--------|-------------|
| FIFO fairness | First passenger to queue boards first — no exceptions |
| Circular array | Efficient memory reuse — no shifting needed on dequeue |
| Clear front/rear | Always know who boards next and how many are waiting |
| Real-world model | This is exactly how platform boarding queues work |

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `enqueuePassenger()` | Base | Checks isBoardingQueueFull, advances rear circularly using (rear+1) % MAX_BOARDING, stores the Passenger struct, increments count. Sets status to Waiting. |
| `dequeuePassenger()` | Base | Checks isBoardingQueueEmpty, reads passengers[front], marks status as Boarded, advances front circularly, decrements count. Prints boarding confirmation. |
| `peekNextPassenger()` | Base | Reads passengers[front] without modifying front or count. Shows who boards next. Queue is unchanged. |
| `searchPassenger()` | Base | Iterates through all count entries using index (front+i) % MAX_BOARDING for each position. Finds passenger by ID and prints their queue position and full details. |
| `displayBoardingQueue()` | Base | Same circular iteration printing every passenger with their position. Marks front entry with NEXT label. |
| `cancelBoarding()` | Base | Finds passenger by ID, shifts subsequent entries to fill gap, adjusts rear and count. |
| `isBoardingQueueEmpty()` | Base | Returns 1 if count equals 0. |
| `isBoardingQueueFull()` | Base | Returns 1 if count equals MAX_BOARDING. |
| `getAverageWaitTime()` | **EXTRA** | Counts passengers by ticket class (First, Second, Third) across all queue slots. Computes average queue position. Reports total waiting, class distribution, and capacity utilisation. Answers: *"What is the current boarding queue status and class distribution?"* |
| `displayBoardingTable()` | Display | Formatted box table with columns for position, passenger ID, name, train, station, class and status. |

## 🧪 Test Scenario

```
1. Enqueue 4 passengers:
   - P601 Silva,  T101, First Class,  joined 08:45
   - P602 Perera, T101, Second Class, joined 08:47
   - P603 Nair,   T101, Third Class,  joined 08:50
   - P604 Hassan, T101, Second Class, joined 08:52

2. Call peekNextPassenger()
   Expected: P601 Silva (first in, shown without removal)

3. Call getAverageWaitTime()
   Expected: 4 waiting, 1 First, 2 Second, 1 Third

4. Call dequeuePassenger()
   Expected: P601 Silva boards, queue shrinks to 3

5. Call peekNextPassenger() again
   Expected: P602 Perera is now next
```

---

---

# 👤 Member 7 — Train Maintenance Queue
**File:** `src/maintenance_queue.c` | **Header:** `include/maintenance_queue.h`
**Data Structure:** `Queue (2nd use)`
**Sort:** None

---

## 📖 The Story

Trains need servicing. Routine maintenance keeps them running safely. Unexpected repairs fix mechanical failures. Emergency interventions handle breakdowns. When multiple trains need servicing, the depot processes them in the order they were submitted — the first train submitted is the first one serviced.

This is again a **Queue** — the same FIFO principle as the boarding queue, but serving a completely different purpose with completely different data.

The boarding queue processes **passengers at platforms**. This queue processes **trains at depots**. Same data structure, different domain, different data, different extra function.

## 🏗️ Why Queue (2nd time)?

| Reason | Explanation |
|--------|-------------|
| FIFO fairness | First train submitted for service is first to be serviced |
| Different data | Processes train records not passenger records |
| Different purpose | Depot operations not platform boarding |
| Different extra | countByMaintenanceType vs getAverageWaitTime |

## ⚙️ Function Reference

| Function | Type | What It Does |
|----------|------|-------------|
| `enqueueForMaintenance()` | Base | Checks isMaintenanceQueueFull, advances rear circularly, stores MaintenanceRecord, increments count. Prompts for train ID, type, depot, time and notes. Sets status to Pending. |
| `processNextMaintenance()` | Base | Checks empty, reads records[front], marks In Service, advances front circularly, decrements count. Prints service details. |
| `peekNextMaintenance()` | Base | Reads records[front] without modifying queue. Shows which train is next for service. |
| `searchMaintenance()` | Base | Iterates through queue entries using circular index formula, finds all entries matching the given trainID. |
| `displayMaintenanceQueue()` | Base | Full queue display with position, service ID, train, type, depot and status. Marks front entry as NEXT. |
| `cancelMaintenance()` | Base | Finds by serviceID, shifts entries to fill gap, adjusts rear and count. |
| `isMaintenanceQueueEmpty()` | Base | Returns 1 if count equals 0. |
| `isMaintenanceQueueFull()` | Base | Returns 1 if count equals MAX_MAINTENANCE. |
| `countByMaintenanceType()` | **EXTRA** | Scans all queue entries using strstr to match maintenanceType against Routine, Repair and Emergency. Counts each category and prints the breakdown. Flags if any Emergency entries are present. Answers: *"How many trains need emergency repair right now vs routine service?"* |
| `displayMaintenanceTable()` | Display | Formatted box table with all maintenance entries showing service ID, train, type, depot and status. |

## 🧪 Test Scenario

```
1. Submit 5 trains for maintenance:
   - T101 Udarata Menike  — Routine
   - T102 Intercity Exp   — Emergency
   - T103 Night Mail      — Repair
   - T104 Ruhunu Kumari   — Routine
   - T105 Yal Devi        — Emergency

2. Call countByMaintenanceType()
   Expected: Routine=2, Repair=1, Emergency=2
   Expected: [!] 2 train(s) require EMERGENCY attention!

3. Call processNextMaintenance()
   Expected: T101 processed (first submitted), queue shrinks to 4

4. Call peekNextMaintenance()
   Expected: T102 Intercity Express — Emergency (now at front)
```

---

---

## 📊 Complete Function Count

| Member | DS | Base Ops | Sort / Nav | Extra | Display | Total |
|--------|----|----------|------------|-------|---------|-------|
| 1 | Array | 7 (incl. isEmpty/isFull) | Bubble Sort | `calculateTotalSeatCapacity` | `displayFleetTable` | **10** |
| 2 | Singly LL | 5 | Insertion Sort | `countStationsOnRoute` | `displayStationTable` | **8** |
| 3 | Doubly LL | 7 (incl. traverseF/B) | Selection Sort | `calculateJourneyDistance` | `displayJourneyTable` | **10** |
| 4 | Circular LL | 5 | `nextTrain` `getCurrent` | `getRouteSize` | `displayRotationTable` | **9** |
| 5 | Array (x2) | 7 (incl. isSeatMapEmpty) | Bubble Sort | `countAvailableSeats` | `displaySeatTable` | **10** |
| 6 | Queue | 8 (incl. isEmpty/isFull/cancel) | — | `getAverageWaitTime` | `displayBoardingTable` | **10** |
| 7 | Queue | 8 (incl. isEmpty/isFull/cancel) | — | `countByMaintenanceType` | `displayMaintenanceTable` | **10** |

---

## ❓ Viva Questions — Prepared Answers

```
Q: Why did you use [your DS] for this module?
   → One sentence linking the DS property to the real railway problem.
   → Examples in each member's "Why DS?" table above.

Q: What is the time complexity of your sort?
   → Bubble Sort    O(n²) worst case, O(n) best case with early exit
   → Insertion Sort O(n²) worst case, O(n) best case (already sorted)
   → Selection Sort O(n²) always — always makes n*(n-1)/2 comparisons

Q: What happens when your module is empty and a function is called?
   → Every function checks isEmpty/isFull first and prints a guard message.

Q: Why did you use Array twice?
   → Module 1 stores TRAINS owned by the railway — fixed fleet limit
   → Module 5 stores SEATS on one train — fixed physical seat count
   → Different entity, different array size, different purpose.
   → Both are genuinely bounded collections — Array is correct both times.

Q: Why did you use Queue twice?
   → Module 6 processes PASSENGERS at PLATFORMS — output: passenger boards
   → Module 7 processes TRAINS at DEPOTS — output: train enters service
   → Same FIFO principle, completely different data and purpose.

Q: How does your module connect to other modules?
   → Through trainID (Modules 1,3,4,5,7) and stationID (Modules 2,3,6)

Q: What makes your extra function different from a basic search?
   → Search returns one element by key.
   → My extra function computes an aggregate (SUM/COUNT/AVERAGE)
      across multiple or all elements — it is a different class of operation.
```
