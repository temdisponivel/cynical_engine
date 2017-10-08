//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_MEMORY_H
#define CYNICAL_ENGINE_CYNICAL_MEMORY_H

#include <stddef.h>

typedef struct frame_memory_s {
    void* head;
    void* current;
    size_t total_size;
    size_t used_size;
} frame_memory;

void frame_memory_init(size_t total_size);
void frame_memory_release();

void frame_memory_reset_allocator();

void* frame_memory_malloc(size_t size);
void* frame_memory_calloc(size_t size);
void frame_memory_free(void* pointer);

#endif //CYNICAL_ENGINE_CYNICAL_MEMORY_H
