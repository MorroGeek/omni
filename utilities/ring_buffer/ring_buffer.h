/**
  * @file    omni_ring_buffer.h
  * @author  MorroMaker
  * @brief   Provide a class to implement ring buffer
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_RING_BUFFER_H
#define OMNI_RING_BUFFER_H

/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#include <cstddef>

namespace omni {
    template<typename T, size_t SIZE>
    class Ring_Buffer {

    public:
        /**
         * @brief  Constructor
         */
        Ring_Buffer() : head(0), tail(0)
        {
        }

        /*
         * @brief  Get the empty status of the buffer
         * @retval true: buffer is empty
         *         false: buffer is not empty
         * @note   This is constance function
         */
        bool is_empty() const
        {
            return head == tail;
        }

        /*
         * @brief  Get the full status of the buffer
         * @retval true: buffer is full
         *         false: buffer is not full
         * @note   This is constance function
         */
        bool is_full() const
        {
            return ((tail + 1) % SIZE) == head;
        }

        /*
         * @brief  Get the size of the buffer
         * @retval size of the buffer
         * @note   This is constance function
         */
        size_t size() const
        {
            return (tail - head + SIZE) % SIZE;
        }

        /*
         * @brief  Enqueue the buffer
         * @param  value: value to enqueue
         * @retval true: enqueue success
         *         false: enqueue fail
         */
        bool enqueue(const T& value)
        {
            if (is_full())
            {
                return false;
            }

            data[tail] = value;         // Copy value to the buffer
            tail = (tail + 1) % SIZE;   // Update tail

            return true;
        }

        /*
         * @brief  Dequeue the buffer
         * @retval true: dequeue success
         *         false: dequeue fail
         */
        bool dequeue(T& value)
        {
            if (is_empty())
            {
                return false;
            }

            value = data[head];         // Copy value from the buffer
            head = (head + 1) % SIZE;   // Update head

            return true;
        }

    private:
        T data[SIZE];
        size_t head;
        size_t tail;
    };
} // namespace omni

#endif /* OMNI_RING_BUFFER_H */
