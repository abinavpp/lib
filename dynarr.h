/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#ifndef DYNARRH
#define DYNARRH

#include "util.h"

struct dynarr {
	void *data;
	size_t sz_data;

	size_t capacity;
};

#define DYNARR_INIT(da, _capacity) \
	(da)->capacity = _capacity; \
	(da)->data = umalloc((da)->capacity); \
	(da)->sz_data = 0;

extern void dynarr_resize(struct dynarr *da, size_t new_capacity);
extern void dynarr_append(struct dynarr *da, void *data, size_t sz_data);
#endif
