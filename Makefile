.PHONY:clean all

CC=clang
CFLAGS=-Wall -Werror -O3 #-g -O3 #-fsanitize=address -fsanitize=undefined
LFLAGS=-lm #-fsanitize=address -fsanitize=undefined
CPPFLAGS=-I./

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

EXEC=main

all:$(EXEC)

$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
	@echo "Linking "$^" successfully!"

%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo "Compiled "$<" successfully!"

clean:
	rm -f $(OBJS) $(EXEC)
