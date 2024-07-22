/**
  * @file    command.c
  * @author  MorroMaker
  * @brief   Command class
  * @attention
  *
  * Copyright (c) 2024 MorroMaker
  * All rights reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

/* Includes ------------------------------------------------------------------*/
#include "components/ring_buffer/ring_buffer.h"

#if defined(CONFIG_OMNI_COMPONENTS_RING_BUFFER)

static int rb_init(ring_buffer_t *rb, uint16_t size);
static int rb_deinit(ring_buffer_t *rb);
static bool rb_is_empty(ring_buffer_t *rb);
static bool rb_is_full(ring_buffer_t *rb);
static size_t rb_get_size(ring_buffer_t *rb);
static int rb_enqueue(ring_buffer_t *rb, uint8_t value);
static int rb_dequeue(ring_buffer_t *rb, uint8_t *value);

struct ring_buffer_api ring_buffer = {
    .init = rb_init,
    .deinit = rb_deinit,
    .is_empty = rb_is_empty,
    .is_full = rb_is_full,
    .get_size = rb_get_size,
    .enqueue = rb_enqueue,
    .dequeue = rb_dequeue,
};

/**
 * @brief Initialize the ring buffer
 * 
 * @param rb Pointer to the ring buffer
 * @param size Size of the buffer
 * @return Operation status
 */
static int rb_init(ring_buffer_t *rb, uint16_t size) {
    rb->buffer = (uint8_t *)OMNI_MALLOC(size * sizeof(uint8_t));
    if (rb->buffer == NULL) {
        return OMNI_FAIL;
    }

    rb->head = 0;
    rb->tail = 0;
    rb->size = size;

    return OMNI_OK;
}

/**
 * @brief Deinitialize the ring buffer
 * 
 * @param rb Pointer to the ring buffer
 * @return Operation status
 */
static int rb_deinit(ring_buffer_t *rb) {
    if (rb->buffer != NULL) {
        OMNI_FREE(rb->buffer);
        rb->buffer = NULL;
    }

    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;

    return OMNI_OK;
}

/**
 * @brief Check if the buffer is empty
 * 
 * @param rb Pointer to the ring buffer
 * @return Result
 */
static bool rb_is_empty(ring_buffer_t *rb) {
    return (rb->head == rb->tail);
}

/**
 * @brief Check if the buffer is full
 * 
 * @param rb Pointer to the ring buffer
 * @return Result
 */
static bool rb_is_full(ring_buffer_t *rb) {
    return ((rb->tail + 1) % rb->size == rb->head);
}

/**
 * @brief Get the size of the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @return Size of the buffer
 */
static size_t rb_get_size(ring_buffer_t *rb) {
    return (rb->tail - rb->head + rb->size) % rb->size;
}

/**
 * @brief Enqueue the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @param value Value to enqueue
 * @return Operation status
 */
static int rb_enqueue(ring_buffer_t *rb, uint8_t value) {
    if (rb_is_full(rb) == true) {
        return OMNI_FAIL;
    }

    rb->buffer[rb->tail] = value;
    rb->tail = (rb->tail + 1) % rb->size;

    return OMNI_OK;
}

/**
 * @brief Dequeue the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @param value Value to dequeue
 * @return Operation status
 */
static int rb_dequeue(ring_buffer_t *rb, uint8_t *value) {
    if (rb_is_empty(rb) == true) {
        return OMNI_FAIL;
    }

    *value = rb->buffer[rb->head];
    rb->head = (rb->head + 1) % rb->size;

    return OMNI_OK;
}

#endif /* CONFIG_OMNI_COMPONENTS_RING_BUFFER */
