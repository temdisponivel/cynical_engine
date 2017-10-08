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
typedef bool (* item_comparer)(DATA a, DATA b);\
\
typedef int (* sort_comparer)(DATA a, DATA b);\
\
typedef struct list_##DATA##_s {\
    size_t length;\
    size_t capacity;\
    DATA* items;\
    item_comparer default_comparer;\
} list_##DATA;\
\
list_##DATA* make_list_##DATA(size_t capacity, const item_comparer default_comparer);\
\
void free_list_##DATA(list_##DATA* list);\
\
void list_##DATA##_add(list_##DATA* list, DATA item);\
\
void list_##DATA##_remove(list_##DATA* list, DATA item);\
\
void list_##DATA##_delete(list_##DATA* list, DATA item, item_comparer comparer);\
\
void list_##DATA##_remove_at(list_##DATA* list, size_t index) ;\
\
int list_##DATA##_index_of(list_##DATA* list, DATA item) ;\
\
int list_##DATA##_find_index(list_##DATA* list, DATA item, item_comparer comparer) ;\
\
void list_##DATA##_expand(list_##DATA* list, size_t new_capacity) ;\
\
void list_##DATA##_left_shift(list_##DATA* list, size_t start_index) ;\
\
void list_##DATA##_clear(list_##DATA* list);\
\
void swap(list_##DATA* list, int a, int b) ;\
\
int partition(list_##DATA* list, int low, int high, sort_comparer comparison);\
\
void inner_quick_sort(list_##DATA* list, int low, int high, sort_comparer comparison);\
\
void quick_sort(list_##DATA* list, sort_comparer comparison) ;\
\
list_##DATA* make_list_##DATA(size_t capacity, const item_comparer default_comparer) {\
    list_##DATA* list = malloc(sizeof(list_##DATA));\
    list->items = calloc(capacity, sizeof(DATA));\
    list->length = 0;\
    list->capacity = capacity;\
    list->default_comparer = default_comparer;\
    return list;\
}\
\
void free_list_##DATA(list_##DATA* list) {\
    free(list->items);\
    free(list);\
}\
\
void list_##DATA##_add(list_##DATA* list, DATA item) {\
    if (list->length >= list->capacity) {\
        list_##DATA##_expand(list, list->capacity * 2);\
    }\
\
    list->items[list->length++] = item;\
}\
\
void list_##DATA##_remove(list_##DATA* list, DATA item) {\
    size_t index = list_##DATA##_index_of(list, item);\
    list_##DATA##_remove_at(list, index);\
}\
\
void list_##DATA##_delete(list_##DATA* list, DATA item, item_comparer comparer) {\
    size_t index = list_##DATA##_find_index(list, item, comparer);\
    list_##DATA##_remove_at(list, index);\
}\
\
void list_##DATA##_remove_at(list_##DATA* list, size_t index) {\
    if (index < 0 || index >= list->length)\
        return;\
\
    list_##DATA##_left_shift(list, index);\
    list->length--;\
}\
\
int list_##DATA##_index_of(list_##DATA* list, DATA item) {\
    return list_##DATA##_find_index(list, item, list->default_comparer);\
}\
\
int list_##DATA##_find_index(list_##DATA* list, DATA item, item_comparer comparer) {\
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
void list_##DATA##_expand(list_##DATA* list, size_t new_capacity) {\
    DATA* temp = calloc(new_capacity, sizeof(DATA));\
    memcpy(temp, list->items, list->length);\
    free(list->items);\
    list->items = temp;\
    list->capacity = new_capacity;\
}\
\
void list_##DATA##_left_shift(list_##DATA* list, size_t start_index) {\
    int len = list->length;\
    for (int i = start_index; i < len - 1; ++i) {\
        list->items[i] = list->items[i + 1];\
    }\
}\
\
void list_##DATA##_clear(list_##DATA* list) {\
    memset(list->items, 0, list->capacity);\
}\
\
void swap(list_##DATA* list, int a, int b) {\
    DATA temp = list->items[a];\
    list->items[a] = list->items[b];\
    list->items[b] = temp;\
}\
\
int partition(list_##DATA* list, int low, int high, sort_comparer comparison) {\
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
void inner_quick_sort(list_##DATA* list, int low, int high, sort_comparer comparison) {\
    if (low < high) {\
        int partition_index = partition(list, low, high, comparison);\
        inner_quick_sort(list, low, partition_index - 1, comparison);\
        inner_quick_sort(list, partition_index + 1, high, comparison);\
    }\
}\
\
void quick_sort(list_##DATA* list, sort_comparer comparison) {\
    inner_quick_sort(list, 0, list->length, comparison);\
}\

CREATE_LIST(vector2)

#endif //CYNICAL_ENGINE_CYNICAL_COLLECTIONS_H
