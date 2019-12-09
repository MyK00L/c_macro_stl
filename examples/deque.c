
#include "../src/deque.h"
#include <stdio.h>

define_deque(int)

		int main() {
	deque_int q = deque_int_new();
	while (1) {
		char c;
		while ((c = getchar()) <= 32)
			;
		if (c == 'F') {
			deque_int_pop_front(&q);
		} else if (c == 'B') {
			deque_int_pop_back(&q);
		} else if (c == 'f') {
			int val;
			scanf("%d", &val);
			deque_int_push_front(&q, val);
		} else if (c == 'b') {
			int val;
			scanf("%d", &val);
			deque_int_push_back(&q, val);
		}
		printf("%lu %lu -- ", q.size, q.capacity);
		for (size_t i = 0; i < q.size; ++i) {
			printf("%d ", *deque_int_at(&q, i));
		}
		printf("\n");
	}
}
