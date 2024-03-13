.PHONY:clean all

CC=gcc
CFLAGS=-Wall -Werror -g -O3 -fsanitize=address -fsanitize=undefined
LFLAGS=-lm
CPPFLAGS=-I./

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

EXEC=main

all:$(EXEC)

$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)
