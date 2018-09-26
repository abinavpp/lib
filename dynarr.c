/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#include <stdio.h>

#include "util.h"
#include "dynarr.h"

void dynarr_resize(struct dynarr *da, size_t new_capacity)
{
	da->capacity = new_capacity;
	da->data = urealloc(da->data, da->capacity);
}

void dynarr_append(struct dynarr *da, void *data, size_t sz_data)
{
	if (da->capacity < (da->sz_data + sz_data)) {
		dynarr_resize(da, da->capacity * 2);
	 }

	memcpy(da->data + da->sz_data, data, sz_data);
	da->sz_data += sz_data;
}
