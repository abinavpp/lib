/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#include "util.h"
#include "sll.h"
#include "stack.h"

struct sll_node *stack_push(struct stack_struct *ss)
{
	ss->count++;
	return sll_add(&(ss->top));
}

struct sll_node *stack_pop(struct stack_struct *ss)
{
	ss->count--;
	return sll_rm(&(ss->top));
}
