/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _BH_LIST_H
#define _BH_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "korp_types.h" /*For bool type*/
#include "bh_platform.h"

/* List user should embedded bh_list_link into list elem data structure
 * definition. And bh_list_link data field should be the first field.
 * For example, if we would like to use bh_list for our own data type A,
 * A must be defined as a structure like below:
 *     struct A {
 *         bh_list_link l;
 *         ...
 *     };
 *
 * bh_list_link is defined as a structure (not typedef void*).
 * It will make extend list into bi-direction easy.
 */
typedef struct _bh_list_link {
    struct _bh_list_link *next;
} bh_list_link;

typedef struct _bh_list {
    bh_list_link head;
    uint32 len;
} bh_list;

/* Beihai list operation return value */
typedef enum _bh_list_status {
    BH_LIST_SUCCESS = 0, BH_LIST_ERROR = -1
} bh_list_status;

/**
 * Initialize a list.
 *
 * @param list    pointer to list.
 * @return        <code>BH_LIST_ERROR</code> if OK;
 *                <code>BH_LIST_ERROR</code> if list pointer is NULL.
 */
bh_list_status bh_list_init(bh_list *list);

/**
 * Insert an elem pointer into list. The list node memory is maintained by list while
 * elem memory is the responsibility of list user.
 *
 * @param list    pointer to list.
 * @param elem    pointer to elem that will be inserted into list.
 * @return        <code>BH_LIST_ERROR</code> if OK;
 *                <code>BH_LIST_ERROR</code> if input is invalid or no memory available.
 */
extern bh_list_status _bh_list_insert(bh_list *list, void *elem);

#ifdef _INSTRUMENT_TEST_ENABLED
extern bh_list_status bh_list_insert_instr(bh_list *list, void *elem, const char*func_name);
#define bh_list_insert(list, elem) bh_list_insert_instr(list, elem, __FUNCTION__)
#else
#define bh_list_insert _bh_list_insert
#endif

/**
 * Remove an elem pointer from list. The list node memory is maintained by list while
 * elem memory is the responsibility of list user.
 *
 * @param list    pointer to list.
 * @param elem    pointer to elem that will be inserted into list.
 * @return        <code>BH_LIST_ERROR</code> if OK;
 *                <code>BH_LIST_ERROR</code> if element does not exist in given list.
 */
bh_list_status bh_list_remove(bh_list *list, void *elem);

/**
 * Get the list length.
 *
 * @param list    pointer to list.
 * @return        the length of the list.
 */
uint32 bh_list_length(bh_list *list);

/**
 * Get the first elem in the list.
 *
 * @param list    pointer to list.
 * @return        pointer to the first node.
 */
void* bh_list_first_elem(bh_list *list);

/**
 * Get the next elem of given list input elem.
 *
 * @param node    pointer to list node.
 * @return        pointer to next list node.
 */
void* bh_list_elem_next(void *node);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _BH_LIST_H */

