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

static inline bool ringbuffer_check_validity(struct ringbuffer_t *buffer)
{
	if (buffer == NULL || buffer->data == NULL)
		return false;

	if ((buffer->head >= buffer->max_length) || (buffer->tail >= buffer->max_length))
		return false;

	return true;
}

bool ringbuffer_pop(struct ringbuffer_t *buffer, uint32_t *data)
{
	if (ringbuffer_empty(buffer) <= 0)
		return false;

	if (data == NULL)
		return false;

	*data = buffer->data[buffer->head];

	int next = buffer->head + 1;
	if(next >= buffer->max_length)
		next = 0;

	buffer->head = next;


	return true;
}

bool ringbuffer_push(struct ringbuffer_t *buffer, uint32_t data)
{
	if (!ringbuffer_check_validity(buffer))
		return false;

	if (ringbuffer_full(buffer))
		return false;


	int next = buffer->tail + 1;
	if(next >= buffer->max_length)
		next = 0;

	buffer->data[next] = data;
	buffer->tail = next;

	return true;
}

int8_t ringbuffer_empty(const struct ringbuffer_t *buffer)
{
	if (!ringbuffer_check_validity((struct ringbuffer_t *) buffer))
		return -1;

	return (int8_t) (ringbuffer_current_size(buffer) == 0);
}

int8_t ringbuffer_full(const struct ringbuffer_t *buffer)
{
	if (!ringbuffer_check_validity((struct ringbuffer_t *) buffer))
			return -1;

	return (int8_t) ((buffer->max_length - ringbuffer_current_size(buffer)) == 0);
}

bool ringbuffer_peek(const struct ringbuffer_t *buffer, uint32_t *data)
{
	if (ringbuffer_empty(buffer) <= 0)
		return false;

	if (data == NULL)
		return false;

	*data = buffer->data[buffer->head];

	return true;
}

uint16_t ringbuffer_current_size(const struct ringbuffer_t *buffer)
{
	if (!ringbuffer_check_validity((struct ringbuffer_t *) buffer))
		return 0;

    if (buffer->head > buffer->tail)
        return (buffer->max_length - (buffer->head - buffer->tail));
    else
        return (buffer->tail - buffer->head);
}

uint16_t ringbuffer_max_size(const struct ringbuffer_t *buffer)
{
	if (!ringbuffer_check_validity((struct ringbuffer_t *) buffer))
		return 0;

	return (int32_t) buffer->max_length;
}
