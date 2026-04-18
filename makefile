# Simple Makefile for MessSystem
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -g
SRCS := main.c student.c auth.c meal.c billing.c file_handler.c
OBJS := $(SRCS:.c=.o)
TARGET := system

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Generic rule: compile .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TARGET)
	@echo "Cleaned."

# convenience: build then run
run: $(TARGET)
	./$(TARGET)
