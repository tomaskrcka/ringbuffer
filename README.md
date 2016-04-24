# Ringbuffer

## Implemented operations
- ringbuffer_pop()
- ringbuffer_push()
- ringbuffer_peek()
- ringbuffer_reset()

### Macros:
- RINGBUFFER_DEFINE() - create and initialize buffer
- RINGBUFFER_EMPTY() - if empty then return non zero value
- RINGBUFFER_FULL() - if full then return non zero value
- RINGBUFFER\_CURR\_SIZE() - number of items in the buffer 
- RINGBUFFER_MAXSIZE() - max size of the buffer
- RINGBUFFER\_FREE\_SIZE() - free size of the buffer


## Working with buffer
Defined macro *RINGBUFFER_DEFINE(buffer, size)*, the macro creates a static array of defined size and init necessary values. 

How to work with buffer and implemented operations can be found in ringbuffer_test.c


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

#### Run the test

```
krcka@krcka-GA-MA785GMT-UD2H ~/workspace/ringbuffer $ ./ringbuffer_test 
Test 1 (Buffer init) ... pass.
Test 2 (Push one item and pop it) ... pass.
Test 3 (Fill buffer with test data) ... pass.
Test 4 (Test reset buffer) ... pass.
Test 5 (Test current size) ... pass.
Test 6 (Fill buffer to full and empty it then) ... pass.
Test 7 (Reset buffer and fill again) ... pass.
Test 8 (Test peek) ... pass.
Test 9 (Test buffer size 0) ... pass.
Test 10 (Fill buffer two times) ... pass.
```

