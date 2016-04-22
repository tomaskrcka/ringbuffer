#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ringbuffer.h"


#define START_NEW_TEST(test_num, name) \
    fprintf(stderr, "Test (%s) %d...", name, (++test_num));

#define END_TEST(test_num) \
    fprintf(stderr, "pass.\n");


bool fill_buffer(struct ringbuffer_t *buf, const uint32_t *test_pattern, uint16_t size)
{
    uint16_t i;
    
    if (size > (RINGBUFFER_MAXSIZE(buf)))
    {
    	return false;
    }
    
    for (i = 0; i < size; i++) {
    	if (!ringbuffer_push(buf, test_pattern[i])) {
    		ringbuffer_clear(buf);
    		return false;
    	}
    }
    
    return true;
}


int main() {
	int test_num = 0;
	
	START_NEW_TEST(test_num, "Buffer init");
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