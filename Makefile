# ================================================================
# Makefile — Sri Lanka Railway Network Management System
# ================================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = railway_system
SRCDIR  = src
INCDIR  = include

SRCS = main.c \
       $(SRCDIR)/train_fleet.c \
       $(SRCDIR)/station_directory.c \
       $(SRCDIR)/journey_log.c \
       $(SRCDIR)/route_rotation.c \
       $(SRCDIR)/seat_reservations.c \
       $(SRCDIR)/boarding_queue.c \
       $(SRCDIR)/maintenance_queue.c \
	   $(SRCDIR)/shared_types.c 


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
