CFILES=$(wildcard *.c)
OBJS=$(CFILES:.c=.o)
CC=gcc
CFLAGS=-s -O3 -Wunused-result

TARGET = Monitor

${TARGET}:${OBJS}
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:${OBJS} Monitor
	rm $^
