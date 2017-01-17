/** @file test_list.c
 *  @brief Test doubly linked list
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

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*a))

#define CONTAINER_OF(in_p, out_name, in_name) \
((out_name *) ((void *) in_p - ((void *) (&((out_name *)(0))->in_name))))

static char util_test_desc_0[] = "Test ARRAY_SIZE";
int util_test_0(void)
{
	struct test {
		int test_inner;
	} test[4];

	if (ARRAY_SIZE(test) != 4) {
		printf("ARRAY_SIZE did not return num elems\n");
		return 0;
	}

	return 1;
}

static char util_test_desc_1[] = "Test CONTAINER_OF";
int util_test_1(void)
{
	struct test {
		int test_inner;
		int test_inner2;
	} test;

	int *test_inner_p = &(test.test_inner);
	int *test_inner2_p = &(test.test_inner2);
	struct test *test_p = &test;

	if (test_p != CONTAINER_OF(test_inner2_p, struct test, test_inner2)) {
		printf("CONTAINER_OF did not return pointer to outter\n");
		return 0;
	}
	
	if (test_p != CONTAINER_OF(test_inner_p, struct test, test_inner)) {
		printf("CONTAINER_OF did not return pointer to outter\n");
		return 0;
	}
	
	return 1;
}

static char list_test_desc_0[] = "Test remove elm from an empty list";
int list_test_0(void)
{
	struct list *list = NULL;
	struct list e;
	struct list *elm = &e;

	if (list_elm_initialize(elm) != 1) {
		printf("Failed: expected 1 ret when init elm\n");
		return 0;
	}

	if (list_count_nodes(list) != 0) {
		printf("Failed: expected count to return 0");
		return 0;
	}

	if (list_remove(&list, &elm) != 0) {
		printf("Failed: expected 0 ret when remov an elm from emp\n");
		return 0;
	}
	
	return 1;
}

static char list_test_desc_1[] = "Test insert and rem one stack elm from list";
int list_test_1(void)
{
	struct list *list = NULL;
	struct list e;
	struct list *in_elm = &e;
	struct list *out_elm = NULL;

	if (list_elm_initialize(in_elm) != 1) {
		printf("Failed: expected 0 ret when init elm\n");
		return 0;
	}

	if (list_insert(&list, in_elm) != 1) {
		printf("Failed: expected 1 ret when inserting inited elm \n");
		return 0;
	}

	if (list_remove(&list, &out_elm) != 1) {
		printf("Failed: expected 0 ret when remov an elm from emp\n");
		return 0;
	}

	if (in_elm != out_elm) {
		printf("Failed to get the first item inserted\n");
		return 0;
	}

	return 1;
}

static char list_test_desc_2[] = "Test insert and rem 2 stack elms";
int list_test_2(void)
{
	struct list *list = NULL;
	struct list in_es[2];
	struct list *in_elms[2] = {&in_es[0], &in_es[1]};
	struct list *out_elm = NULL;
	int i;
	
	for (i = 0; i < 2; i++) {
		if (list_elm_initialize(in_elms[i]) != 1) {
			printf("Failed: expected 0 ret when init elm %i\n", i);
			return 0;
		}
	}

	for (i = 0; i < 2; i++) {
		if (list_insert(&list, in_elms[i]) != 1) {
			printf("Failed: expct 1 ret whn insert inited elm \n");
			return 0;
		}
	}

	if (list_count_nodes(list) != 2) {
		printf("Failed: expected count to return 2");
		return 0;
	}

	if (list_remove(&list, &out_elm) != 1) {
		printf("Failed: expected 0 ret when remov an elm from emp\n");
		return 0;
	}

	if (list_count_nodes(list) != 1) {
		printf("Failed: expected count to return 1");
		return 0;
	}

	if (out_elm != in_elms[1]) {
		printf("Failed to get the last item inserted\n");
		return 0;
	}
	
	if (list_remove(&list, &out_elm) != 1) {
		printf("Failed: expected 0 ret when remov an elm from emp\n");
		return 0;
	}
	
	if (list_count_nodes(list) != 0) {
		printf("Failed: expected count to return 0");
		return 0;
	}

	if (out_elm != in_elms[0]) {
		printf("Failed to get the last item inserted\n");
		return 0;
	}

	return 1;
}

static char list_test_desc_3[] = "Test insert and rem 1 malloc'd elm";
int list_test_3(void)
{
	struct list *list_head;
	struct list *list_elm;

	if (list_init_head(&list_head) != 1) {
		printf("Failed: expected ret 1 from list_head_init\n");
		return 0;
	}

	list_elm = (struct list *) malloc(sizeof(*list_elm));
	if (list_elm == NULL) {
		printf("Failed: could not alloc list_elm");
		return 0;
	}

	if (list_elm_initialize(list_elm)  != 1) {
		printf("Failed: expected 0 ret when init elm\n");
		return 0;
	}
	
	if (list_insert(&list_head, list_elm) != 1) {
		printf("Failed: expct 1 ret whn insert inited elm \n");
		return 0;
	}
	
	if (list_remove(&list_head, &list_elm) != 1) {
		printf("Failed: expected 0 ret when remov an elm from emp\n");
		return 0;
	}

	free(list_elm);

	if (list_count_nodes(list_head) != 0) {
		printf("Failed: expected count to return 0\n");
		return 0;
	}

	return 1;
}

static char list_test_desc_4[] = "Test insert and rem 100 malloc'd elms";
int list_test_4(void)
{
	struct list *list = NULL;
	struct list *in;
	struct list *out = NULL;
	int i;
	
	for (i = 0; i < 100; i++) {
		in = (struct list *) malloc(sizeof(*list));
		if (in == NULL) {
			printf("Failed: could not alloc a device\n");
			return 0;
		}
		if (list_elm_initialize(in) != 1) {
			printf("Failed: expected 0 ret when init elm\n");
			return 0;
		}

		if (list_insert(&list, in) != 1) {
			printf("Failed: expect 1 ret when insrt init elm \n");
			return 0;
		}
	}

	i = 0;
	int ret;
	do {
		ret = list_remove(&list, &out);
		if (ret == 1) {	
			free(out);
			i++;
		}
	} while (ret == 1);

	if (i != 100) {
		printf("Failed: expected 100 items, got %i\n", i);
		return 0;
	}

	return 1;
}

static char list_test_desc_5[] = "Use malloc and CONTAINER_OF, 1 elm";
int list_test_5(void)
{
	struct list *list_head;

	struct thing {
		int x;
		struct list list_elm;
	};

	struct thing *thing;

	if (list_init_head(&list_head) != 1) {
		printf("Failed: expected ret 1 from list_head_init\n");
		return 0;
	}

	thing = (struct thing *) malloc(sizeof(*thing));
	if (thing == NULL) {
		printf("Failed: could not alloc thing\n");
		return 0;
	}
	thing->x = 3;

	if (list_elm_initialize(&thing->list_elm)  != 1) {
		printf("Failed: expected 0 ret when init elm\n");
		return 0;
	}
	
	if (list_insert(&list_head, &thing->list_elm) != 1) {
		printf("Failed: expct 1 ret whn insert inited elm \n");
		return 0;
	}

	struct list *out_list;
	if (list_remove(&list_head, &out_list) != 1) {
		printf("Failed: expected 0 ret when remov an elm from emp\n");
		return 0;
	}

	struct thing *out_thing =
		CONTAINER_OF(out_list, struct thing, list_elm);

	if (out_thing->x != 3) {
		printf("Failed: expected 3, got %i\n", out_thing->x);
		return 0;
	}
	free(out_thing);

	if (list_count_nodes(list_head) != 0) {
		printf("Failed: expected count to return 0\n");
		return 0;
	}

	return 1;
}

static char list_test_desc_6[] = "Use malloc and CONTAINER_OF, 9 elms";
int list_test_6(void)
{
	struct list *list_head;

	struct thing {
		int x;
		struct list list_elm;
	};

	struct thing *thing;

	if (list_init_head(&list_head) != 1) {
		printf("Failed: expected ret 1 from list_head_init\n");
		return 0;
	}

	int i;
	for (i = 0; i < 10; i++) {
		thing = (struct thing *) malloc(sizeof(*thing));
		if (thing == NULL) {
			printf("Failed: could not alloc thing\n");
			return 0;
		}
		thing->x = i;

		if (list_elm_initialize(&thing->list_elm)  != 1) {
			printf("Failed: expected 0 ret when init elm\n");
			return 0;
		}
		
		if (list_insert(&list_head, &thing->list_elm) != 1) {
			printf("Failed: expct 1 ret whn insert inited elm \n");
			return 0;
		}
	}

	for (i = 0; i < 10; i++) {
		struct list *out_list;
		if (list_remove(&list_head, &out_list) != 1) {
			printf("Failed: exp 0 ret when remov an elm frm emp\n");
			return 0;
		}

		struct thing *out_thing = CONTAINER_OF(out_list,
							struct thing,
							list_elm);
		if (out_thing->x != 9-i) {
			printf("Failed: exp %i, got %i\n", 9-i, out_thing->x);
			return 0;
		}
		free(out_thing);
	}

	if (list_count_nodes(list_head) != 0) {
		printf("Failed: expected count to return 0\n");
		return 0;
	}

	return 1;
}

struct test {
	int (*test_func) (void);
	char *test_desc;
} tests[] = {
	{util_test_0, util_test_desc_0},
	{util_test_1, util_test_desc_1},
	{list_test_0, list_test_desc_0},
	{list_test_1, list_test_desc_1},
	{list_test_2, list_test_desc_2},
	{list_test_3, list_test_desc_3},
	{list_test_4, list_test_desc_4},
	{list_test_5, list_test_desc_5},
	{list_test_6, list_test_desc_6},
};


int main(int argc, char *argv[])
{
	int ret,i;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		ret = tests[i].test_func();
		switch (ret) {
			case -1:
				printf("%s: ", "SYSERR");
				break;
			case 0:
				printf("%s: ", "FAILED");
				break;
			case 1:
				printf("%s: ", "PASSED");
				break;
			default:
				printf("%s: ", "UNEXPE");
				break;
		}
		printf("%s", tests[i].test_desc);
		printf("\n");
	}

	return 0;
}
