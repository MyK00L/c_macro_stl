#include "../src/vector.h"
#include <stdio.h>

define_vector(int);
define_vector(vector_int);

int main() {
	vector_int v = vector_int_new();
	for (int i = 0; i < 18; ++i)
		vector_int_push_back(&v, i);
	printf("%lx %lu %lu\n", v.data, v.size, v.capacity);
	for (int i = 0; i < vector_int_size(&v); ++i) {
		printf("%d ", *vector_int_at(&v, i));
	}
	printf("\n");
	for (int i = 2; i < 13; ++i)
		vector_int_erase(&v, i);
	printf("%lx %lu %lu\n", v.data, v.size, v.capacity);
	for (int i = 0; i < vector_int_size(&v); ++i) {
		printf("%d ", *vector_int_at(&v, i));
	}
	printf("\n");
	for (int i = 69; i < 73; ++i)
		vector_int_insert(&v, 1, i);
	printf("%lx %lu %lu\n", v.data, v.size, v.capacity);
	for (int i = 0; i < vector_int_size(&v); ++i) {
		printf("%d ", *vector_int_at(&v, i));
	}
	printf("\n");
	return 0;
}
