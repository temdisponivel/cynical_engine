//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_COLLECTIONS_H
#define CYNICAL_ENGINE_CYNICAL_COLLECTIONS_H

#include <stddef.h>
#include <stdlib.h>
#include <mem.h>
#include "cynical_math.h"

#define CREATE_LIST(DATA) \
typedef bool (* item_comparer_t)(DATA a, DATA b);\
\
typedef int (* sort_comparer_t)(DATA a, DATA b);\
\
typedef struct list_##DATA##_t##_s {\
    size_t length;\
    size_t capacity;\
    DATA* items;\
    item_comparer_t default_comparer;\
} list_##DATA##_t;\
\
list_##DATA##_t* make_list_##DATA##_t(size_t capacity, const item_comparer_t default_comparer);\
\
void free_list_##DATA##_t(list_##DATA##_t* list);\
\
void list_##DATA##_t##_add(list_##DATA##_t* list, DATA item);\
\
void list_##DATA##_t##_remove(list_##DATA##_t* list, DATA item);\
\
void list_##DATA##_t##_delete(list_##DATA##_t* list, DATA item, item_comparer_t comparer);\
\
void list_##DATA##_t##_remove_at(list_##DATA##_t* list, size_t index) ;\
\
int list_##DATA##_t##_index_of(list_##DATA##_t* list, DATA item) ;\
\
int list_##DATA##_t##_find_index(list_##DATA##_t* list, DATA item, item_comparer_t comparer) ;\
\
void list_##DATA##_t##_expand(list_##DATA##_t* list, size_t new_capacity) ;\
\
void list_##DATA##_t##_left_shift(list_##DATA##_t* list, size_t start_index) ;\
\
void list_##DATA##_t##_clear(list_##DATA##_t* list);\
\
void swap(list_##DATA##_t* list, int a, int b) ;\
\
int partition(list_##DATA##_t* list, int low, int high, sort_comparer_t comparison);\
\
void inner_quick_sort(list_##DATA##_t* list, int low, int high, sort_comparer_t comparison);\
\
void quick_sort(list_##DATA##_t* list, sort_comparer_t comparison) ;\
\
list_##DATA##_t* make_list_##DATA##_t(size_t capacity, const item_comparer_t default_comparer) {\
    list_##DATA##_t* list = malloc(sizeof(list_##DATA##_t));\
    list->items = calloc(capacity, sizeof(DATA));\
    list->length = 0;\
    list->capacity = capacity;\
    list->default_comparer = default_comparer;\
    return list;\
}\
\
void free_list_##DATA##_t(list_##DATA##_t* list) {\
    free(list->items);\
    free(list);\
}\
\
void list_##DATA##_t##_add(list_##DATA##_t* list, DATA item) {\
    if (list->length >= list->capacity) {\
        list_##DATA##_t##_expand(list, list->capacity * 2);\
    }\
\
    list->items[list->length++] = item;\
}\
\
void list_##DATA##_t##_remove(list_##DATA##_t* list, DATA item) {\
    size_t index = list_##DATA##_t##_index_of(list, item);\
    list_##DATA##_t##_remove_at(list, index);\
}\
\
void list_##DATA##_t##_delete(list_##DATA##_t* list, DATA item, item_comparer_t comparer) {\
    size_t index = list_##DATA##_t##_find_index(list, item, comparer);\
    list_##DATA##_t##_remove_at(list, index);\
}\
\
void list_##DATA##_t##_remove_at(list_##DATA##_t* list, size_t index) {\
    if (index < 0 || index >= list->length)\
        return;\
\
    list_##DATA##_t##_left_shift(list, index);\
    list->length--;\
}\
\
int list_##DATA##_t##_index_of(list_##DATA##_t* list, DATA item) {\
    return list_##DATA##_t##_find_index(list, item, list->default_comparer);\
}\
\
int list_##DATA##_t##_find_index(list_##DATA##_t* list, DATA item, item_comparer_t comparer) {\
    size_t len = list->length;\
    for (int i = 0; i < len; ++i) {\
        if (comparer(list->items[i], item)) {\
            return i;\
        }\
    }\
\
    return -1;\
}\
\
void list_##DATA##_t##_expand(list_##DATA##_t* list, size_t new_capacity) {\
    DATA* temp = calloc(new_capacity, sizeof(DATA));\
    memcpy(temp, list->items, list->length);\
    free(list->items);\
    list->items = temp;\
    list->capacity = new_capacity;\
}\
\
void list_##DATA##_t##_left_shift(list_##DATA##_t* list, size_t start_index) {\
    int len = list->length;\
    for (int i = start_index; i < len - 1; ++i) {\
        list->items[i] = list->items[i + 1];\
    }\
}\
\
void list_##DATA##_t##_clear(list_##DATA##_t* list) {\
    memset(list->items, 0, list->capacity);\
}\
\
void swap(list_##DATA##_t* list, int a, int b) {\
    DATA temp = list->items[a];\
    list->items[a] = list->items[b];\
    list->items[b] = temp;\
}\
\
int partition(list_##DATA##_t* list, int low, int high, sort_comparer_t comparison) {\
    DATA pivot = list->items[high];\
    int i = low - 1;\
    for (int j = low; j <= high - 1; j++) {\
\
        int diff = comparison(list->items[j], pivot);\
        if (diff <= 0) {\
            i++;\
            swap(list, i, j);\
        }\
    }\
    swap(list, i + 1, high);\
    return (i + 1);\
}\
\
void inner_quick_sort(list_##DATA##_t* list, int low, int high, sort_comparer_t comparison) {\
    if (low < high) {\
        int partition_index = partition(list, low, high, comparison);\
        inner_quick_sort(list, low, partition_index - 1, comparison);\
        inner_quick_sort(list, partition_index + 1, high, comparison);\
    }\
}\
\
void quick_sort(list_##DATA##_t* list, sort_comparer_t comparison) {\
    inner_quick_sort(list, 0, list->length, comparison);\
}\

#endif //CYNICAL_ENGINE_CYNICAL_COLLECTIONS_H
