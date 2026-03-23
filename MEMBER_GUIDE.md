# Member Guide — Supermarket / Grocery Store Management System

This document explains each member’s module, the chosen data structure, why it fits the supermarket context, the main functions.

---

## Module Allocation

| Member | Module | Data Structure |
|--------|--------|---------------|
| Member 1 | Product Inventory | Array |
| Member 2 | Supplier Management | Singly Linked List |
| Member 3 | Customer Purchase History | Doubly Linked List |
| Member 4 | Restocking Request Management | Queue |
| Member 5 | Undo Last Item in Current Bill | Stack |
| Member 6 | Promotional Banner Rotation | Circular Linked List |
| Member 7 | Sales Reports | Array |

---

# Member 1 — Product Inventory
**Files:** `include/product.h`, `src/product.c`  
**Data Structure:** Array  
**Sort:** Selection Sort

## Why Array?
A supermarket has a stock list of products that can be stored and accessed by index. Arrays are simple and efficient for storing products in a structured list.

## Functions
- `addProduct()`
- `searchProduct()`
- `updateProduct()`
- `deleteProduct()`
- `displayProducts()`
- `selectionSortProductsByPrice()`
- `totalItemsInStock()`
- `totalInventoryValue()`

## Extra Function
`totalInventoryValue()`  
Calculates the total value of all products using:

```text
price × quantity
```

---

# Member 2 — Supplier Management
**Files:** `include/supplier.h`, `src/supplier.c`  
**Data Structure:** Singly Linked List

## Why Singly Linked List?
Suppliers can be added or removed dynamically, so a linked list is better than a fixed-size array.

## Functions
- `addSupplier()`
- `searchSupplier()`
- `updateSupplier()`
- `deleteSupplier()`
- `displaySuppliers()`
- `countSuppliers()`

## Extra Function
`countSuppliers()`  
Counts the total number of supplier nodes in the linked list.

---

# Member 3 — Customer Purchase History
**Files:** `include/purchase_history.h`, `src/purchase_history.c`  
**Data Structure:** Doubly Linked List

## Why Doubly Linked List?
Purchase records need forward and backward traversal. A doubly linked list supports both directions naturally.

## Functions
- `addPurchaseRecord()`
- `searchPurchaseRecord()`
- `updatePurchaseRecord()`
- `deletePurchaseRecord()`
- `traversePurchasesForward()`
- `traversePurchasesBackward()`
- `totalPurchasesByCustomer()`

## Extra Function
`totalPurchasesByCustomer()`  
Calculates the total spending of one customer by scanning all their purchase records.

---

# Member 4 — Restocking Request Management
**Files:** `include/restock_req_queue.h`, `src/restock_req_queue.c`  
**Data Structure:** Queue

## Why Queue?
Restocking requests are processed in the same order they are added. This is a FIFO process, so queue is the best fit.

## Functions
- `enqueueRestockRequest()`
- `dequeueRestockRequest()`
- `frontRestockRequest()`
- `displayRestockRequests()`
- `searchRestockRequest()`
- `countPendingRestockRequests()`
- `totalRequestedQuantity()`

## Extra Function
`totalRequestedQuantity()`  
Calculates the total quantity requested across all pending restock requests.


---

# Member 5 — Undo Last Item in Current Bill
**Files:** `include/bill_stack.h`, `src/bill_stack.c`  
**Data Structure:** Stack

## Why Stack?
The last scanned item is the easiest one to remove first. This is a LIFO process, so stack fits perfectly.

## Functions
- `pushScannedItem()`
- `popLastItem()`
- `peekLatestItem()`
- `displayCurrentBillStack()`
- `currentBillTotal()`

## Extra Function
`currentBillTotal()`  
Calculates the total value of the current bill using all items in the stack.

---

# Member 6 — Promotional Banner Rotation
**Files:** `include/promo_cycle.h`, `src/promo_cycle.c`  
**Data Structure:** Circular Linked List

## Why Circular Linked List?
Promotions rotate continuously. After the last promo, it should return to the first promo again. That behavior matches a circular linked list.

## Functions
- `addPromo()`
- `displayNextPromo()`
- `searchPromo()`
- `updatePromo()`
- `deletePromo()`
- `displayAllPromos()`
- `countActivePromos()`

## Extra Function
`countActivePromos()`  
Counts how many promotion nodes currently exist in the circular list.

---

# Member 7 — Sales Reports
**Files:** `include/sales_report.h`, `src/sales_report.c`  
**Data Structure:** Array  
**Sort:** Bubble Sort

## Why Array?
Sales records can be stored in a simple linear structure and sorted easily by amount.

## Functions
- `addSalesRecord()`
- `searchSalesRecord()`
- `updateSalesRecord()`
- `deleteSalesRecord()`
- `displaySalesRecords()`
- `bubbleSortSalesByAmount()`
- `totalDailySales()`
- `averageSales()`
- `highestSaleDay()`

## Extra Functions
- `totalDailySales()`
- `averageSales()`
- `highestSaleDay()`

---

## Suggested Demo Order

1. Show Product Inventory
2. Show Supplier Management
3. Show Purchase History forward/backward
4. Show Restocking Request Queue
5. Show Bill Stack and undo operation
6. Show Promo Rotation
7. Show Sales Reports and sorting

---

### Why these data structures?
Because each one matches the real behavior of the supermarket process:
- Array → fixed structured records
- SLL → dynamic supplier list
- DLL → forward/backward purchase history
- Queue → FIFO restocking
- Stack → undo latest scanned item
- CLL → repeating promotions

### Why extra functions?
Because the assignment requires more than CRUD.  
So each member has at least one meaningful extra function such as:
- sum
- count
- average
- highest value

### Why use Array twice?
Because:
- Product Inventory stores products
- Sales Reports stores sales records

These are two different real-world collections with different purposes.

---