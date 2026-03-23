#ifndef CHECKOUT_QUEUE_H
#define CHECKOUT_QUEUE_H

void restockQueueMenu(void);
void initQueue(void);
void enqueueRestockRequest(void);
void dequeueRestockRequest(void);
void frontRestockRequest(void);
void displayRestockRequests(void);
void searchRestockRequest(void);
void countPendingRestockRequests(void);
void totalRequestedQuantity(void);

#endif
