/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#ifndef LISTH 
#define LISTH 

#include "util.h"

struct list_node {
	void *data;
	size_t sz_data;

	void *key;
	size_t sz_key;
	struct list_node *prev;
	struct list_node *next;
};

#define LIST_NEW_NODE zalloc(sizeof(struct list_node))
#define LIST_INIT_HEAD(head) \
	do { \
		(head)->next = (head); \
		(head)->prev = (head); \
	} while (0);

#define list_for_each(i, head) \
	for (i = (head)->next; i != (head); i = i->next)

extern void list_node_add(struct list_node *new, 
		struct list_node *prev, struct list_node *next);

extern void list_node_append(struct list_node *at, struct list_node *new);

extern void list_node_prepend(struct list_node *at, struct list_node *new);

extern void list_node_rm(struct list_node *target);

#endif
