#include "../src/cuckoo_hash_map.h"

#include <assert.h>
#include <stdio.h>

define_cuckoo_hash_map(int, int);

int main() {
	cuckoo_hash_map_int_int hm = cuckoo_hash_map_int_int_new();
	char c;
	while (1) {
		printf("hm.size = %ld\ng = get\ns = set\n", hm.size);
		while ((c = getchar()) <= 32)
			;
		if (c == 'g') {
			int k;
			scanf("%d", &k);
			printf("%d\n", cuckoo_hash_map_int_int_count(&hm, k) ? *cuckoo_hash_map_int_int_at(&hm, k) : -1);
		} else if (c == 's') {
			int k, v;
			scanf("%d%d", &k, &v);
			*cuckoo_hash_map_int_int_at(&hm, k) = v;
		}
	}
}
