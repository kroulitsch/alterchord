CC = gcc
INCDIR = include
SRCDIR = src
CFLAGS = -Wall -Wextra -g -I$(INCDIR)
PROG = main

C_FILES = main.c $(wildcard $(SRCDIR)/*.c)
OBJS = $(C_FILES:.c=.o)
H_FILES = $(wildcard $(INCDIR)/*.h)

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(H_FILES)

v: $(PROG)
	valgrind --show-leak-kinds=all --leak-check=full ./$(PROG)

clone:
	cd .. && rm -rf simulog && git clone https://github.com/kroulitsch/alterchord.git --branch main

pull:
	git pull

clean:
	rm -f $(PROG) $(OBJS)

run: $(PROG)
	./$(PROG)

.PHONY: all v clone pull clean run