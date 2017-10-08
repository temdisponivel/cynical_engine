//
// Created by Morpheus on 07-Oct-17.
//

#include <cynical_memory.h>
#include <malloc.h>
#include <cynical_debug.h>
#include <mem.h>

frame_memory_t* main_frame_memory;

void frame_memory_init(size_t total_size) {
    frame_memory_t* memory = malloc(sizeof(frame_memory_t));
    void* head = calloc(total_size, sizeof(char));;
    memory->head = head;
    memory->current = memory->head;
    memory->total_size = total_size;
    memory->used_size = 0;

    main_frame_memory = memory;
}

void frame_memory_release() {
    free(main_frame_memory->head);
    main_frame_memory->used_size = 0;
    main_frame_memory->total_size = 0;
}

void frame_memory_reset_allocator() {
    main_frame_memory->used_size = 0;
}

void* frame_memory_malloc(size_t size) {

    {
        size_t resulting_size = main_frame_memory->used_size + size + sizeof(size_t);
        ASSERT(resulting_size <= main_frame_memory->total_size);
    }

    void* malloc_start = main_frame_memory->current;
    *(size_t*) malloc_start = size;
    void* result = malloc_start + sizeof(size_t);

    main_frame_memory->current = result + size;
    main_frame_memory->used_size += size + sizeof(size_t);

    return result;
}

void* frame_memory_calloc(size_t size) {
    void* result = frame_memory_malloc(size);
    memset(result, 0, size);
    return result;
}

void frame_memory_free(void* pointer) {
    // the true address of the allocation is the adress less one size_t because we used
    // the first size to store the size of the allocation and returned the next address
    void* true_address = pointer - sizeof(size_t);
    size_t size = *(size_t*) true_address;
    main_frame_memory->used_size -= size + sizeof(size_t);
    main_frame_memory->current = true_address;
}