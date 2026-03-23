# ================================================================
# Makefile — Supermarket / Grocery Store Management System
# ================================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = supermarket
SRCDIR  = src
INCDIR  = include

SRCS = main.c \
       $(SRCDIR)/product.c \
       $(SRCDIR)/supplier.c \
       $(SRCDIR)/purchase_history.c \
       $(SRCDIR)/restock_req_queue.c \
       $(SRCDIR)/bill_stack.c \
       $(SRCDIR)/promo_cycle.c \
       $(SRCDIR)/sales_report.c


all:
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCS) -o $(TARGET)
	@echo ""
	@echo "  [OK] Compiled successfully -> ./$(TARGET)"
	@echo ""

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
	@echo "  [OK] Build cleaned."
output:
	mkdir -p output
