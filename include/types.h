#ifndef TYPES_H
#define TYPES_H

#define MAX_PRODUCTS 200
#define MAX_SALES 200
#define MAX_QUEUE 100
#define MAX_STACK 100
#define NAME_LEN 50
#define DESC_LEN 100

typedef struct {
    int id;
    char name[NAME_LEN];
    float price;
    int quantity;
} Product;

typedef struct Supplier {
    int id;
    char name[NAME_LEN];
    char phone[20];
    struct Supplier* next;
} Supplier;

typedef struct Purchase {
    int recordId;
    int customerId;
    char customerName[NAME_LEN];
    float amount;
    struct Purchase* prev;
    struct Purchase* next;
} Purchase;

typedef struct {
    int productId;
    char productName[NAME_LEN];
    int requestedQty;
} RestockRequest;

typedef struct {
    RestockRequest items[MAX_QUEUE];
    int front;
    int rear;
} RestockQueue;

typedef struct {
    int productId;
    char productName[NAME_LEN];
    float price;
    int qty;
} BillItem;

typedef struct {
    BillItem items[MAX_STACK];
    int top;
} BillStack;

typedef struct Promo {
    int id;
    char title[DESC_LEN];
    struct Promo* next;
} Promo;

typedef struct {
    int day;
    float amount;
} SaleRecord;

#endif