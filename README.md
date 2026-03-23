# 🛒 Supermarket / Grocery Store Management System

A CLI-based supermarket management system built in **C**, implementing **7 data structures** across 7 independent modules. Developed as a semester group assignment for a Data Structures & Algorithms course at the University of Moratuwa.

---

## 👥 Team

| Member | Module | Data Structure | Sort Algorithm |
|--------|--------|---------------|----------------|
| Member 1 | Product Inventory | Array | Selection Sort |
| Member 2 | Supplier Management | Singly Linked List | — |
| Member 3 | Customer Purchase History | Doubly Linked List | — |
| Member 4 | Restocking Request Queue | Queue | — |
| Member 5 | Checkout Bill (Undo Scan) | Stack | — |
| Member 6 | Promotional Banner Rotation | Circular Linked List | — |
| Member 7 | Sales Reports | Array | Bubble Sort |

---

## 📋 System Overview

This system models the full operational flow of a supermarket — from managing product inventory and supplier records to processing customer bills, tracking purchase history, handling restocking requests, rotating promotional banners on display screens, and generating daily sales reports.

```
Product added to Inventory
        |
        v
[Array]          Product registered -> productID assigned
        |
        |-> [Singly LL]    Supplier linked to product source
        |
        |-> [Queue]        Low stock triggers restock request (FIFO)
        |
        |-> [Stack]        Customer scans items at checkout
        |       |          Wrong scan? Pop to undo last item
        |       v
        |   Bill confirmed -> Purchase recorded
        |
        |-> [Doubly LL]    Purchase record added to history
        |       (traverse forward = oldest, backward = latest)
        |
        |-> [Circular LL]  Promo banners cycle on display screen
        |
        v
[Array]          Daily sales amount recorded -> Sales Report
```

---

## 🗂️ Project Structure

```
supermarket-system/
|
|-- main.c                        <- Master menu & entry point
|
|-- include/                      <- Header files
|   |-- types.h                   <- All struct definitions & constants
|   |-- product.h                 <- Member 1
|   |-- supplier.h                <- Member 2
|   |-- purchase_history.h        <- Member 3
|   |-- restock_req_queue.h       <- Member 4
|   |-- bill_stack.h              <- Member 5
|   |-- promo_cycle.h             <- Member 6
|   |-- sales_report.h            <- Member 7
|
|-- src/                          <- Implementation files
|   |-- product.c                 <- Member 1
|   |-- supplier.c                <- Member 2
|   |-- purchase_history.c        <- Member 3
|   |-- restock_req_queue.c       <- Member 4
|   |-- bill_stack.c              <- Member 5
|   |-- promo_cycle.c             <- Member 6
|   |-- sales_report.c            <- Member 7
```

---

## ⚙️ How to Build & Run

### Prerequisites
- GCC compiler
- VS Code (recommended) or any terminal

### Compile & Run

```bash
gcc -Wall -std=c99 main.c src/*.c -Iinclude -o supermarket
./supermarket
```

**On Windows (PowerShell):**
```powershell
gcc -Wall -std=c99 main.c src/*.c -Iinclude -o supermarket.exe
./supermarket.exe
```

---

## 🖥️ Main Menu

```
========================================
   SUPERMARKET / GROCERY STORE SYSTEM
========================================
1. Product Inventory         (Array)
2. Supplier Management       (SLL)
3. Customer Purchase History (DLL)
4. Restocking Request Queue  (Queue)
5. Undo Last Item in Bill    (Stack)
6. Promotional Banner        (CLL)
7. Sales Reports             (Array)
8. Show Demo Guide
0. Exit
```

---

## 📦 Module Details

### 1. 🛍️ Product Inventory — `Array`
Stores all products in a fixed-capacity array. The supermarket stocks a bounded catalog of products — an array models this naturally with direct access by index.

**Base Operations:** `addProduct` `searchProduct` `updateProduct` `deleteProduct` `displayProducts`

**Sort:** `selectionSortProductsByPrice` — sorts products cheapest to most expensive

**Extra:**
- `totalItemsInStock()` — total quantity of all products combined
- `totalInventoryValue()` — total monetary value of current stock (price × quantity)

---

### 2. 🏭 Supplier Management — `Singly Linked List`
Manages the list of suppliers dynamically. Suppliers are added and removed as business relationships change — a linked list grows and shrinks without wasted memory.

**Base Operations:** `addSupplier` `searchSupplier` `updateSupplier` `deleteSupplier` `displaySuppliers`

**Extra:**
- `countSuppliers()` — total number of active suppliers in the list

---

### 3. 🧾 Customer Purchase History — `Doubly Linked List`
Logs every customer purchase. Staff browse **forward** to see oldest records and **backward** to see most recent transactions. Only a Doubly LL supports both directions natively.

**Base Operations:** `addPurchaseRecord` `searchPurchaseRecord` `updatePurchaseRecord` `deletePurchaseRecord` `traversePurchasesForward` `traversePurchasesBackward`

**Extra:**
- `totalPurchasesByCustomer()` — sum of all purchase amounts for a given customer ID

---

### 4. 📦 Restocking Request Queue — `Queue`
When a product runs low, a restock request is submitted. The warehouse processes requests strictly in submission order — first submitted, first fulfilled. Pure FIFO.

**Base Operations:** `enqueueRestockRequest` `dequeueRestockRequest` `frontRestockRequest` `displayRestockRequests` `searchRestockRequest`

**Extra:**
- `countPendingRestockRequests()` — how many restock requests are waiting
- `totalRequestedQuantity()` — total units requested across all pending requests

---

### 5. 🧮 Checkout Bill — `Stack`
Every item scanned at the checkout counter is pushed onto the bill stack. If the cashier scans the wrong item, they pop it off to undo the last scan. The most recently scanned item is always the one removed — pure LIFO.

**Base Operations:** `pushScannedItem` `popLastItem` `peekLatestItem` `displayCurrentBillStack`

**Extra:**
- `currentBillTotal()` — running total of all items currently on the bill (price × quantity for each)

---

### 6. 📢 Promotional Banner Rotation — `Circular Linked List`
The store's digital display screen cycles through promotional banners endlessly. After the last promotion is shown, it loops back to the first — no end point, just a continuous cycle.

**Base Operations:** `addPromo` `displayNextPromo` `searchPromo` `updatePromo` `deletePromo`

**Extra:**
- `countActivePromos()` — how many promotional banners are currently in the rotation cycle

---

### 7. 📊 Sales Reports — `Array`
Records daily sales amounts in a fixed-size array. Managers review, sort and analyse sales data to spot trends and identify the best performing days.

**Base Operations:** `addSalesRecord` `searchSalesRecord` `updateSalesRecord` `deleteSalesRecord` `displaySalesRecords`

**Sort:** `bubbleSortSalesByAmount` — sorts sales records from lowest to highest amount

**Extra:**
- `totalDailySales()` — sum of all sales amounts recorded
- `averageSales()` — average daily sales across all records
- `highestSaleDay()` — which day had the highest sales amount

---

## 🔗 Key Linking Fields

```c
productId   ->  links Product Inventory to Restock Queue and Bill Stack
customerId  ->  links Purchase History records to a specific customer
supplierId  ->  links Supplier records to supply chain operations
```

---

## 🎯 Extra Functions — Why Each Is Genuinely Useful

| Module | Extra Function | Real Operational Value |
|--------|---------------|----------------------|
| Product | `totalItemsInStock()` | Know total stock count before placing a bulk order |
| Product | `totalInventoryValue()` | Accounting — what is the current stock worth in rupees |
| Supplier | `countSuppliers()` | How many active supplier relationships exist |
| Purchase | `totalPurchasesByCustomer()` | Loyalty programme — how much has a customer spent |
| Restock | `countPendingRestockRequests()` | How backed up is the warehouse team |
| Restock | `totalRequestedQuantity()` | How many total units need to be ordered today |
| Bill | `currentBillTotal()` | Cashier shows running total to customer while scanning |
| Promo | `countActivePromos()` | How many banners are in current rotation cycle |
| Sales | `totalDailySales()` | End of week total revenue |
| Sales | `averageSales()` | Is today above or below average performance |
| Sales | `highestSaleDay()` | Which day was most profitable this period |

---

## 📌 DS Rule Verification

```
Array           -> used 2 times  (Products + Sales)       max allowed: 3  OK
Singly LL       -> used 1 time   (Suppliers)               max allowed: 3  OK
Doubly LL       -> used 1 time   (Purchase History)        max allowed: 3  OK
Circular LL     -> used 1 time   (Promo Rotation)          max allowed: 3  OK
Stack           -> used 1 time   (Checkout Bill)           max allowed: 3  OK
Queue           -> used 1 time   (Restock Requests)        max allowed: 3  OK
```

---

## 🎮 Demo Guide

Suggested flow to demonstrate all modules quickly:

```
1 -> 5 : Display all products
1 -> 6 : Sort products by price (Selection Sort)
2 -> 5 : Display all suppliers
3 -> 5 : Browse purchase history forward
3 -> 6 : Browse purchase history backward
3 -> 7 : Total purchases by customer 1
4 -> 4 : Display pending restock requests
4 -> 7 : Show total requested quantity
5 -> 4 : Display current bill (preloaded items)
5 -> 5 : Show current bill total
5 -> 2 : Pop last item (undo scan)
6 -> 2 : Show next promo (click multiple times to see rotation)
6 -> 6 : Count active promos
7 -> 5 : Display sales records
7 -> 6 : Sort sales by amount (Bubble Sort)
7 -> 9 : Show highest sale day
```

---

## 🛠️ Tech Stack

- **Language:** C (C99 standard)
- **Compiler:** GCC
- **IDE:** VS Code
- **Version Control:** Git & GitHub

---

## 📌 Assignment Context

- **Course:** Data Structures & Algorithms I
- **University:** University of Moratuwa
- **Data Structures Used:** Array (×2), Singly LL, Doubly LL, Circular LL, Stack, Queue
- **Sorting Algorithms:** Selection Sort (Products), Bubble Sort (Sales)
