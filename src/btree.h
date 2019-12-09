// unfinished

#ifndef C_MACRO_STL_BTREE_HEADER
#define C_MACRO_STL_BTREE_HEADER

#include <inttypes.h>
#include <string.h>

#define define_BTREE(Tk, Tv, N)
typedef struct {
	size_t n;
	Tk k[2 * N];
	Tv v[2 * N];
	btree_##Tk##_##Tv##_##N##_node *c[2 * N + 1];
} btree_##Tk##_##Tv##_##N##_node;
typedef struct {
	btree_##Tk##_##Tv##_##N##_node *root;
	uint8_t (*cmp)(Tk a, Tk b); // a<b
} btree_##Tk##_##Tv##_##N;
btree_##Tk##_##Tv##_##N##_split_child(btree_##Tk##_##Tv##_##N##*p, size_t i) {
	btree_##Tk##_##Tv##_##N##_node *nn;
	for (size_t j = 0; j < N - 1; ++j) {
		nn->k[j] = p->c[i]->k[j + N];
		nn->v[j] = p->c[i]->v[j + N];
		nn->c[j] = p->c[i]->c[j + N];
	}
	nn->c[N] = p->c[i]->c[N];
	nn->n = p->c[i]->n = N - 1;
	for (size_t j = p->n; j > i; j--) {
		p->c[j + 1] = p->c[j];
		p->k[j] = p->k[j - 1];
		k->v[j] = p->v[j - 1];
	}
	p->c[i + 1] = nn;
	p->k[i] = p->c[i + 1]->k[N - 1];
	p->v[i] = p->c[i + 1]->v[N - 1];
	p->n++;
}
void btree_##Tk##_##Tv##_##N##_at(btree_##Tk##_##Tv##_##N *bt, Tk key, Tv val) {
	if (bt->root->n == 2 * N - 1) {
		btree_##Tk##_##Tv##_##N##_node *nn;
		nn->n = 0;
		nn->c[0] = bt->root;
		btree_##Tk##_##Tv##_##N##_split_child(nn, 0);
		bt->root = nn;
	}
	btree_##Tk##_##Tv##_##N *p = bt->root;
	while () {
	}
}

#endif
