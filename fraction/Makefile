CFILES=$(wildcard *.cpp)
OBJS=$(CFILES:.c=.o)
CC=g++
CFLAGS=-s -O3

TARGET = test

${TARGET}:${OBJS}
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
clean:${OBJS} test
	rm $^
