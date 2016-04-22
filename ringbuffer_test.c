#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "ringbuffer.h"

#define START_NEW_TEST(test_num, name) \
    fprintf(stderr, "Test %d (%s) ... ", (++test_num), name);

#define END_TEST(test_num) \
    fprintf(stderr, "pass.\n");

bool fill_buffer(struct ringbuffer_t *buf, const uint32_t *test_pattern,
		uint16_t size) {
	uint16_t i;

	if (size > (RINGBUFFER_FREE_SIZE(buf))) {
		return false;
	}

	for (i = 0; i < size; i++) {
		if (!ringbuffer_push(buf, test_pattern[i])) {
			ringbuffer_reset(buf);
			return false;
		}
	}

	return true;
}

int main() {
	int test_num = 0;
	uint32_t tmp;
	uint32_t i;

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Buffer init");

	RINGBUFFER_DEFINE(buff, 32);
	assert(RINGBUFFER_MAXSIZE(&buff) == 32);
	assert(RINGBUFFER_FULL(&buff) == 0);
	assert(RINGBUFFER_EMPTY(&buff) == 1);
	assert(RINGBUFFER_FREE_SIZE(&buff) == 32);
	assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Push one item and pop it");
	assert(ringbuffer_push(&buff, 10) == true);
	assert(RINGBUFFER_EMPTY(&buff) == 0);
	assert(RINGBUFFER_FREE_SIZE(&buff) == 31);
	assert(RINGBUFFER_CURR_SIZE(&buff) == 1);

	assert(ringbuffer_pop(&buff, &tmp) == true);
	assert(tmp == 10);
	assert(RINGBUFFER_EMPTY(&buff) == 1);
	assert(RINGBUFFER_FREE_SIZE(&buff) == 32);
	assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Push item if buffer full");

	assert(RINGBUFFER_EMPTY(&buff) == 1);
	for (i = 0; i < RINGBUFFER_MAXSIZE(&buff); i++) {
		assert(ringbuffer_push(&buff, i) == true);
		assert(RINGBUFFER_EMPTY(&buff) == 0);
		assert(RINGBUFFER_CURR_SIZE(&buff) == (i + 1));
	}

	assert(RINGBUFFER_FREE_SIZE(&buff) == 0);
	assert(RINGBUFFER_FULL(&buff) == 1);
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Pop item if buffer empty");
	assert(RINGBUFFER_FULL(&buff) == 1);

	i = 0;
	RINGBUFFER_FOREACH(&buff, &tmp)
	{
		assert(RINGBUFFER_FREE_SIZE(&buff) == (i + 1));
		assert(tmp == i++);
	}

	assert(RINGBUFFER_FULL(&buff) == 0);
	assert(RINGBUFFER_FREE_SIZE(&buff) == 32);
	assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
	assert(RINGBUFFER_EMPTY(&buff) == 1);
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Test current size");
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Fill buffer to full and empty it then");
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Reset buffer and fill again");

	ringbuffer_reset (&buff);
	assert(RINGBUFFER_EMPTY(&buff) == 1);
	for (i = 0; i < RINGBUFFER_MAXSIZE(&buff); i++) {
		assert(ringbuffer_push(&buff, i) == true);
		assert(RINGBUFFER_EMPTY(&buff) == 0);
		assert(RINGBUFFER_CURR_SIZE(&buff) == (i + 1));
	}

	assert(RINGBUFFER_FREE_SIZE(&buff) == 0);
	assert(RINGBUFFER_EMPTY(&buff) == 0);
	
	ringbuffer_reset(&buff);
	assert(RINGBUFFER_EMPTY(&buff) == 1);
	for (i = 0; i < RINGBUFFER_MAXSIZE(&buff); i++) {
		assert(ringbuffer_push(&buff, i) == true);
		assert(RINGBUFFER_EMPTY(&buff) == 0);
		assert(RINGBUFFER_CURR_SIZE(&buff) == (i + 1));
	}

	END_TEST(test_num);

}
