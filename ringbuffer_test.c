#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "ringbuffer.h"


#define START_NEW_TEST(test_num, name) \
    fprintf(stderr, "Test (%s) %d...", name, (++test_num));

#define END_TEST(test_num) \
    fprintf(stderr, "pass.\n");


bool fill_buffer(struct ringbuffer_t *buf, const uint32_t *test_pattern, uint16_t size)
{
    uint16_t i;
    
    if (size > (RINGBUFFER_FREE_SIZE((*buf))))
    {
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
	
	START_NEW_TEST(test_num, "Buffer init");
	
	RINGBUFFER_DEFINE(buff, 32);
	assert(RINGBUFFER_MAXSIZE(buff) == 32);
	assert(RINGBUFFER_FULL(buff) == 0);
	assert(RINGBUFFER_EMPTY(buff) == 1);
	assert(RINGBUFFER_FREE_SIZE(buff) == 32);
	assert(RINGBUFFER_CURR_SIZE(buff) == 0);
	
	END_TEST(test_num);
	
	START_NEW_TEST(test_num, "Push one item and pop it");
	END_TEST(test_num);
	
	START_NEW_TEST(test_num, "Push item if buffer full ");
	END_TEST(test_num);
		
	START_NEW_TEST(test_num, "Pop item if buffer empty");
	END_TEST(test_num);
	
	START_NEW_TEST(test_num, "Test current size");
	END_TEST(test_num);
	
	START_NEW_TEST(test_num, "Fill buffer to full and empty it then");
	END_TEST(test_num);
	
	START_NEW_TEST(test_num, "Clear buffer and fill again");
	END_TEST(test_num);
	
}
