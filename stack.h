/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#ifndef STACKH
#define STACKH

#include "sll.h"
#include "util.h"

struct stack_struct {
	size_t count;
	size_t capacity;

	struct sll_node *top;
};

#define STACK_NEW zalloc(sizeof(struct stack_struct));

#define STACK_IS_EMPTY(ss) 	(!(ss)->count)
#define STACK_IS_FULL(ss)	((ss)->count == (ss)->capacity)

extern struct sll_node *stack_push(struct stack_struct *ss);
extern struct sll_node *stack_pop(struct stack_struct *ss);

#endif
