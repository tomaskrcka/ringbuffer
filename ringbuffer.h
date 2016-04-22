/*
 * ringbuffer.h
 *
 *  Created on: Apr 21, 2016
 *      Author: krcka
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>

struct ringbuffer_t {
	uint32_t * const data;
	uint16_t head;
	uint16_t tail;
	uint16_t count;
	const uint16_t max_length;
};

#define RINGBUFFER_DEFINE(buff,size) uint32_t buff##_space[size]; ringbuffer_t buff = { buff##_space,0,0,0,size}

#define RINGBUFFER_EMPTY(buffer) (buffer->count == 0)
#define RINGBUFFER_FULL(buffer) ((buffer->max_length - buffer->count) == 0)
#define RINGBUFFER_CURR_SIZE(buffer) buffer->count
#define RINGBUFFER_MAXSIZE(buffer) buffer->max_length

bool ringbuffer_pop(struct ringbuffer_t *buffer, uint32_t *data);
void ringbuffer_reset(struct ringbuffer_t *buffer);
bool ringbuffer_push(struct ringbuffer_t *buffer, uint32_t data);
bool ringbuffer_peek(const struct ringbuffer_t *buffer, uint32_t *data);


#endif /* RINGBUFFER_H_ */
