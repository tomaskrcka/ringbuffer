/*
 * ringbuffer.c
 *
 *  Created on: Apr 21, 2016
 *      Author: krcka
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ringbuffer.h"

#ifndef __STDC_VERSION__ >= 199901L
/* C99 code */
#error "Compiler must support C99"
#endif


static inline bool ringbuffer_check_validity(struct ringbuffer_t *buffer) {
	if (buffer == NULL || buffer->data == NULL)
		return false;

	if ((buffer->head >= buffer->max_length)
			|| (buffer->tail >= buffer->max_length))
		return false;

	if (buffer->count >= buffer->max_length)
		return false;

	return true;
}

bool ringbuffer_clear(struct ringbuffer_t *buffer)
{
	if (buffer == NULL)
		return false;

	buffer->count = 0;
	buffer->head = 0;
	buffer->tail = 0;

	return true;
}

bool ringbuffer_pop(struct ringbuffer_t *buffer, uint32_t *data) {
	if ((data == NULL) || (!ringbuffer_check_validity(buffer)))
		return false;

	if (RINGBUFFER_EMPTY(buffer) >= 1)
		return false;

	*data = buffer->data[buffer->tail];

	int next = buffer->tail + 1;
	if (next >= buffer->max_length)
		next = 0;

	buffer->tail = next;
	buffer->count--;

	return true;
}

bool ringbuffer_push(struct ringbuffer_t *buffer, uint32_t data) {
	if (!ringbuffer_check_validity(buffer))
		return false;

	if (RINGBUFFER_FULL(buffer) >= 1)
		return false;

	buffer->data[buffer->head] = data;

	int next = buffer->head + 1;
	if (next >= buffer->max_length)
		next = 0;

	buffer->head = next;
	buffer->count++;

	return true;
}

bool ringbuffer_peek(const struct ringbuffer_t *buffer, uint32_t *data) {
	if ((data == NULL) || (!ringbuffer_check_validity(buffer)))
		return false;

	if (RINGBUFFER_EMPTY(buffer) >= 1)
		return false;


	*data = buffer->data[buffer->tail];

	return true;
}

