/*
 * SPDX-License-Identifier: GPL-2.0+
 * Copyright (C) 2018 Abinav Puthan Purayil
 * */

#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "sll.h"
#include "util.h"
#include "hash.h"

/* Returns hash index for key of size sz_key by using hs->hash_fn */
long ht_geti(struct ht_struct *hs, const void *key, size_t sz_key)
{
	long index;

	index = hs->hash_fn(key, sz_key, hs->size);
	return index;
}

/* Returns a new sll_node entry for key of size sz_key */
struct sll_node *ht_add(struct ht_struct *hs, 
		const void *key, size_t sz_key)
{
	long index;

	index = ht_geti(hs, key, sz_key);

	return sll_add(&(hs->table[index]));
}

/* calls ht_add and assigns the new node's key and sz_key */
struct sll_node *ht_addk(struct ht_struct *hs, 
		 void *key, size_t sz_key)
{
	struct sll_node *new;

	new = ht_add(hs, key, sz_key);
	SLL_SET_KEY(new, key, sz_key);
	
	return new;
}

/* Does the same as ht_add except if the key is occupied then it returns
 * that sll_node instead of creating a new one */ 
struct sll_node *ht_repl(struct ht_struct *hs, 
		const void *key, size_t sz_key)
{
	long index;

	index = ht_geti(hs, key, sz_key);

	return sll_repl(&(hs->table[index]), key, sz_key);
}


/* Returns ref to node with its key=key of size sz_key, only returns for
 * one node, hence it works as expected with ht_repl() but not with
 * ht_add(). Returns NULL if not found */
struct sll_node **ht_find(struct ht_struct *hs, 
		const void *key, size_t sz_key)
{
	struct sll_node **walk;
	long index;

	index = ht_geti(hs, key, sz_key);

	return sll_find(&hs->table[index], key, sz_key);
}

void ht_rm(struct ht_struct *hs, struct sll_node **node)
{
	sll_rm(node);
}

/* Removes all hs->size buckets using free_data and free_key 
 * functions from hs */
void ht_rm_all_entries(struct ht_struct *hs,
		void (*free_data)(void *), void (*free_key)(void *))
{
	size_t i;

	for (i = 0; i < hs->size; i++) {
		if (hs->table[i]) {
			sll_rmall(&hs->table[i], free_data, free_key);
		}
	}
}

struct ht_struct *ht_resize(struct ht_struct *hs_old, size_t new_size)
{
	size_t i;
	struct ht_struct *hs_new = HT_NEW_STRUCT;
	struct sll_node *walk, *new_node;

	HT_INIT_TABLE(hs_new, new_size);
	HT_INIT_HASHFN(hs_new, hs_old->hash_fn);

	for (i = 0; i < hs_old->size; i++) {
		sll_for_node(walk, hs_old->table[i]) {
			/* printf("rehashing %s %d to %d\n", */ 
					/* walk->key, i, ht_geti(new, walk->key, walk->sz_key)); */
			new_node = ht_addk(hs_new, walk->key, walk->sz_key);
			new_node->data = walk->data;
			new_node->sz_data = walk->sz_data;
		}
	}

	return hs_new;
}
