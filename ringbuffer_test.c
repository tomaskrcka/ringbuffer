#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "ringbuffer.h"

#define BUFFER_SIZE	128

#define START_NEW_TEST(test_num, name) \
    fprintf(stderr, "Test %d (%s) ... ", (++test_num), name);

#define END_TEST(test_num) \
    fprintf(stderr, "pass.\n");

static bool fill_buffer_to_full(struct ringbuffer_t *buf) {
	uint32_t i;

	uint16_t free_size = RINGBUFFER_FREE_SIZE(buf);

	for (i = 0; i < free_size; i++) {
		if (!ringbuffer_push(buf, i)) {
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
	uint32_t test_arr[] = { 4, 3, 5, 6, 1, 12, 345, 4, 5, 1, 5 };
	uint16_t test_arr_size = (uint16_t) sizeof(test_arr) / sizeof(uint32_t);

	RINGBUFFER_DEFINE(buff, BUFFER_SIZE);
	/**
	 * Init buffer and test it
	 */
	START_NEW_TEST(test_num, "Buffer init");
	{
		assert(RINGBUFFER_MAXSIZE(&buff) == BUFFER_SIZE);
		assert(RINGBUFFER_FULL(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		assert(RINGBUFFER_FREE_SIZE(&buff) == BUFFER_SIZE);
		assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
	}
	END_TEST(test_num);

	/**
	 * Push one item and pop it
	 */
	START_NEW_TEST(test_num, "Push one item and pop it");
	{
		assert(ringbuffer_push(&buff, 10) == true);
		assert(RINGBUFFER_EMPTY(&buff) == 0);
		assert(RINGBUFFER_FREE_SIZE(&buff) == (BUFFER_SIZE - 1));
		assert(RINGBUFFER_CURR_SIZE(&buff) == 1);

		assert(ringbuffer_pop(&buff, &tmp) == true);
		assert(tmp == 10);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		assert(RINGBUFFER_FREE_SIZE(&buff) == BUFFER_SIZE);
		assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
	}
	END_TEST(test_num);

	/**
	 * Fill buffer with test data
	 */
	START_NEW_TEST(test_num, "Fill buffer with test data");
	{
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		for (i = 0; i < test_arr_size; i++) {
			assert(ringbuffer_push(&buff, test_arr[i]) == true);
			assert(RINGBUFFER_EMPTY(&buff) == 0);
			assert(RINGBUFFER_CURR_SIZE(&buff) == (i + 1));
		}

		assert(RINGBUFFER_FREE_SIZE(&buff) == BUFFER_SIZE - test_arr_size);
		assert(RINGBUFFER_FULL(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 0);
	}
	END_TEST(test_num);

	/**
	 * Pop test data
	 */
	START_NEW_TEST(test_num, "Pop test data");
	{
		assert(RINGBUFFER_FULL(&buff) == 0);

		i = 0;
		for (; ringbuffer_pop(&buff, &tmp) == true;) {
			assert(tmp == test_arr[i++]);
		}

		assert(RINGBUFFER_FULL(&buff) == 0);
		assert(RINGBUFFER_FREE_SIZE(&buff) == BUFFER_SIZE);
		assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
	}
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Test current size");
	{
		ringbuffer_reset(&buff);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		assert(fill_buffer_to_full(&buff) == true);
		assert(RINGBUFFER_FREE_SIZE(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 0);

		i = RINGBUFFER_MAXSIZE(&buff);
		for (; ringbuffer_pop(&buff, &tmp) == true;) {
			assert(RINGBUFFER_CURR_SIZE(&buff) == --i);
		}

		assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
	}
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Fill buffer to full and empty it then");
	{
		ringbuffer_reset(&buff);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		assert(fill_buffer_to_full(&buff) == true);
		assert(RINGBUFFER_FREE_SIZE(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 0);

		i = 0;
		for (; ringbuffer_pop(&buff, &tmp) == true;) {
			assert(tmp == i++);
		}
		assert(RINGBUFFER_FULL(&buff) == 0);
		assert(RINGBUFFER_FREE_SIZE(&buff) == BUFFER_SIZE);
		assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
	}
	END_TEST(test_num);

	/**
	 * 
	 */
	START_NEW_TEST(test_num, "Reset buffer and fill again");
	{
		ringbuffer_reset(&buff);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		assert(fill_buffer_to_full(&buff) == true);
		assert(RINGBUFFER_FREE_SIZE(&buff) == 0);
		assert(RINGBUFFER_EMPTY(&buff) == 0);

		ringbuffer_reset(&buff);
		assert(RINGBUFFER_EMPTY(&buff) == 1);
		assert(fill_buffer_to_full(&buff) == true);
	}
	END_TEST(test_num);

	START_NEW_TEST(test_num, "Test peek");
	{
		ringbuffer_reset(&buff);
		assert(ringbuffer_push(&buff, 10) == true);
		assert(ringbuffer_push(&buff, 11) == true);

		assert(ringbuffer_peek(&buff, &tmp) == true);
		assert(tmp == 10);
		assert(ringbuffer_pop(&buff, &tmp) == true);
		assert(tmp == 10);

		assert(ringbuffer_peek(&buff, &tmp) == true);
		assert(tmp == 11);
		assert(RINGBUFFER_CURR_SIZE(&buff) == 1);

		assert(fill_buffer_to_full(&buff) == true);
		assert(RINGBUFFER_FREE_SIZE(&buff) == 0);
		assert(ringbuffer_pop(&buff, &tmp) == true);
		assert(tmp == 11);
		assert(ringbuffer_peek(&buff, &tmp) == true);
		assert(tmp == 0);

		i = 0;
		for (; ringbuffer_pop(&buff, &tmp) == true;) {
			assert(tmp == i++);
		}
		assert(tmp == (BUFFER_SIZE - 2));
	}
	END_TEST(test_num);

	START_NEW_TEST(test_num, "Test buffer size");
	{
		RINGBUFFER_DEFINE(buff, 0);
		assert(RINGBUFFER_CURR_SIZE(&buff) == 0);
		assert(RINGBUFFER_MAXSIZE(&buff) == 0);
		assert(ringbuffer_push(&buff, 10) == false);
		assert(ringbuffer_pop(&buff, &tmp) == false);
	}
	END_TEST(test_num);
}
