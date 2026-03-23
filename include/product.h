#ifndef PRODUCT_H
#define PRODUCT_H

#include "types.h"

void productMenu(void);
void initProducts(void);
void addProduct(void);
int searchProductIndexById(int id);
void searchProduct(void);
void updateProduct(void);
void deleteProduct(void);
void displayProducts(void);
void selectionSortProductsByPrice(void);
void totalItemsInStock(void);
void totalInventoryValue(void);

#endif
