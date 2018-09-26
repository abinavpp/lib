/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#ifndef HASHH
#define HASHH

#include "sll.h"
#include "util.h"

struct ht_struct {
	/* size will be mod for hash_fn */
	size_t size;

	/* return hash % mod for n bytes */
	long (*hash_fn) 
		(const void *bytes, size_t n, size_t mod);

	struct sll_node **table;
};

#define HT_NEW_STRUCT \
	(struct ht_struct *)zalloc(sizeof(struct ht_struct));

#define HT_INIT_TABLE(hs, _size) \
	(hs)->size = (_size); \
	(hs)->table = (struct sll_node **) \
	zalloc((hs)->size * sizeof(void *));

#define HT_INIT_HASHFN(hs, fn) \
	(hs)->hash_fn = (fn);

extern long ht_geti(struct ht_struct *hs, const void *key, size_t sz_key);

extern struct sll_node *ht_add(struct ht_struct *hs, 
		const void *key, size_t sz_key);

extern struct sll_node *ht_addk(struct ht_struct *hs, 
		void *key, size_t sz_key);

extern struct sll_node *ht_repl(struct ht_struct *hs, 
		const void *key, size_t sz_key);

extern struct sll_node **ht_find(struct ht_struct *hs, 
		const void *key, size_t sz_key);

extern void ht_rm(struct ht_struct *hs, struct sll_node **node);

extern void ht_rm_all_entries(struct ht_struct *hs,
		void (*free_data)(void *), void (*free_key)(void *));

extern struct ht_struct *ht_resize(struct ht_struct *hs_old, size_t new_size);
#endif
