# Ringbuffer

## Implemented operations
- ringbuffer_pop()
- ringbuffer_push()
- ringbuffer_peek()
- ringbuffer_reset()
- RINGBUFFER_EMPTY()
- RINGBUFFER_FULL()
- RINGBUFFER\_CURR\_SIZE()
- RINGBUFFER_MAXSIZE()
- RINGBUFFER\_FREE\_SIZE()

## Working with buffer
Definded macro *RINGBUFFER_DEFINE(buffer, size)*, the macro creates a static array of defined size and init necessary values. 

How to work with buffer and implemented operations can be found  in ringbuffer_test.c


## Compilation

The program has been compiled and tested under linux system.

It's written for C99 support. 

**Requirements:**
        gcc, make

**How to compile:**
        $ make

After this the "ringbuffer_test" executable file will be created.

## Testing

Unit tests - how to use the ringbuffer and test of implemented operations


