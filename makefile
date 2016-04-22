
CC      = $(CROSS_COMPILE)gcc -std=c99

DEPS    = ringbuffer.h 
CFILES    = ringbuffer.c
OBJ = ringbuffer.o ringbuffer_test.o


.PHONY: clean
.PHONY: all

all: ringbuffer_test

ringbuffer.o: ringbuffer.c ringbuffer.h
	$(CC) -c -o $@ $<

ringbuffer_test.o: ringbuffer_test.c
	$(CC) -c -o $@ $<

ringbuffer_test: $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	rm -f *.o ringbuffer_test
