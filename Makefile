##
# Project Title
#
# @file
# @version 0.1

CC = gcc

CFLAGS = -g -Wall

LIBS = -lm

SRCS = main.c rubik_logic.c solver.c

OBJS = $(SRCS:.c=.o)

TARGET = rubik_solver

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# end
