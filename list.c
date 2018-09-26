/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#include <stdio.h>

#include "util.h"
#include "list.h"

void list_node_add(struct list_node *new, 
		struct list_node *prev, struct list_node *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

void list_node_append(struct list_node *at, struct list_node *new)
{
	list_node_add(new, at, at->next);
}

void list_node_prepend(struct list_node *at, struct list_node *new)
{
	list_node_add(new, at->prev, at);
}

void list_node_rm(struct list_node *target)
{
	target->prev->next = target->next;
	target->next->prev = target->prev;
}
