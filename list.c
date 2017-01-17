/** @file list.c
 *  @brief Doubly linked list elm init, insert and remove
 *
 *  This implementation is largely for demonstration purposes. Functions
 *  generally return -1 when the callee gives the function something that its
 *  not expecting. Functions return 0 to indicate false and 1 to indicate
 *  success.
 *
 *  @copyright
 *  MIT License
 *
 *  Copyright (c) 2017 Zach Pfeffer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

#include <stddef.h>
#include <stdio.h>
#include "list.h"

static int list_elm_is_initialized(struct list *list)
{
	if (list == NULL)
		return -1;

	if (list->next == list && list->prev == list)
		return 1;	

	return 0;
}

/** @brief Initialize a list element
 *
 *  @param[in] list Points to the elm you want to initialize
 *
 *  @retval -1 list is NULL (the callee has violated our contract)
 *  @retval 1 list has been initialized
 *
 */
int list_elm_initialize(struct list *list)
{
	if (list == NULL)
		return -1;

	list->prev = list;
	list->next = list;

	return 1;
}

/** @brief Tests if a list is empty
 *
 *  An empty list is a list that points to NULL
 *
 *  @param[in] list Points to the list you want to check is empty
 *
 *  @retval 1 list has no members (is empty)
 *  @retval 0 list is not empty
 */
int list_empty(struct list *list)
{
	if (list == NULL)
		return 1;
	
	return 0;
}

/** @brief Initializes a head (sets it to NULL)
 *
 *  @param[in,out] *list Points to the list you want to initialize
 *
 *  @retval -1 list was NULL (the callee has violated our contract)
 *  @retval 1 *list is initialized (it points to NULL)
 */
int list_init_head(struct list **list)
{
	if (list == NULL)
		return -1;

	*list = NULL;

	return 1;
}

/** @brief Count all nodes in the doubly linked list, will "wrap-around"
 *
 *  @param[in] list Points to the list you want to count the elms of
 *
 *  @retval 0 to n nodes in the list
 */
int list_count_nodes(struct list *list)
{
	if (list == NULL) {
		return 0;
	}

	struct list *cur = list;
	int i = 0;
	do {
		i++;
		cur = cur->next;
	} while (cur != list);

	return i;
}

/** @brief Insert an initialized elm into a list, point list to elm on ret
 *
 *  @param[in,out] *list Points to the place you what to insert the elm
 *  @param[in]     elm   Points to the element to insert
 *
 *  @retval -1 list or elm is NULL or elm not initialized
 *  @retval 1 success
 */
int list_insert(struct list **list, struct list *elm)
{
	/* *list will point to the inserted element */
	if (list == NULL) {
		printf("Error: list is NULL\n");
		return -1;
	}

	if (elm == NULL) {
		printf("Error: elm is NULL\n");
		return -1;
	}

	if (list_elm_is_initialized(elm) != 1) {
		printf("Error: elm not initialized\n");
		return -1;
	}
	
	if (*list == NULL) {
		*list = elm;
		return 1;
	}

	(*list)->prev->next = elm;
	elm->prev = (*list)->prev;
	elm->next = *list;
	(*list)->prev = elm;

	*list = elm;
	return 1;
}

/** @brief Insert an initialized elm into a list, point list to elm on ret
 *
 *  @param[in,out] *list The list to remove the elm from
 *  @param[in,out] *elm The elm to return the removed elm
 *
 *  @retval -1 param is NULL or elm not initialized
 *  @retval 1 success
 */
int list_remove(struct list **list, struct list **elm)
{
	/* *list will point to the "next" element */
	
	if (list == NULL) {
		printf("Error: list is NULL\n");
		return -1;
	}

	if (elm == NULL)  {
		printf("Error: elm is NULL\n");
		return -1;
	}

	/* return false since can't remove anything from an empty list */
	if (*list == NULL) {
		return 0;	
	}

	if (list_count_nodes(*list) == 1) {
		*elm = *list;
		*list = NULL;
		return 1;
	}
	
	(*list)->prev->next = (*list)->next;
	(*list)->next->prev = (*list)->prev;
	
	*elm = *list;
	*list = (*list)->next;

	/* fix up the removed elm */
	list_elm_initialize(*elm); /* can ignore the ret val: *elm is okay */

	return 1;
}
