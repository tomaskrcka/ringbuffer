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
	const uint16_t max_length;
};

#define RINGBUFF_DEFINE(buff,size) uint32_t buff##_space[size]; ringbuffer_t buff = { buff##_space,0,0,size}

bool ringbuffer_pop(struct ringbuffer_t *buffer, uint32_t *data);
bool ringbuffer_push(struct ringbuffer_t *buffer, uint32_t data);
int8_t ringbuffer_empty(const struct ringbuffer_t *buffer);
int8_t ringbuffer_full(const struct ringbuffer_t *buffer);
bool ringbuffer_peek(const struct ringbuffer_t *buffer, uint32_t *data);
uint16_t ringbuffer_current_size(const struct ringbuffer_t *buffer);
uint16_t ringbuffer_max_size(const struct ringbuffer_t *buffer);

#endif /* RINGBUFFER_H_ */
