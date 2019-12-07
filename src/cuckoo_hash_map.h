#ifndef C_MACRO_STL_CUCKOO_HASH_MAP
#define C_MACRO_STL_CUCKOO_HASH_MAP

#include <inttypes.h>
#include <stdlib.h>

uint64_t cchmh1(uint8_t *p, size_t key_size) {
	uint64_t res = 0;
	for (size_t i = 0; i < key_size; ++i) {
		res = (727 * res) ^ (uint64_t) * (p + i);
	}
	return res;
}
uint64_t cchmh2(uint8_t *p, size_t key_size) {
	uint64_t res = 0;
	for (size_t i = 0; i < key_size; ++i) {
		res = (257 * res) ^ (uint64_t) * (p + i);
	}
	return res;
}
#define define_cuckoo_hash_map(Tk, Tv)                                                                                                                                                                 \
	typedef struct {                                                                                                                                                                                     \
		Tk k;                                                                                                                                                                                              \
		Tv v;                                                                                                                                                                                              \
		uint8_t present;                                                                                                                                                                                   \
	} cuckoo_hash_map_##Tk##_##Tv##_element;                                                                                                                                                             \
	typedef struct {                                                                                                                                                                                     \
		cuckoo_hash_map_##Tk##_##Tv##_element *_1;                                                                                                                                                         \
		cuckoo_hash_map_##Tk##_##Tv##_element *_2;                                                                                                                                                         \
		size_t size;                                                                                                                                                                                       \
	} cuckoo_hash_map_##Tk##_##Tv;                                                                                                                                                                       \
	cuckoo_hash_map_##Tk##_##Tv cuckoo_hash_map_##Tk##_##Tv##_new() {                                                                                                                                    \
		cuckoo_hash_map_##Tk##_##Tv res;                                                                                                                                                                   \
		res.size = 127;                                                                                                                                                                                    \
		res._1 = (cuckoo_hash_map_##Tk##_##Tv##_element *)calloc(res.size, sizeof(cuckoo_hash_map_##Tk##_##Tv##_element));                                                                                 \
		res._2 = (cuckoo_hash_map_##Tk##_##Tv##_element *)calloc(res.size, sizeof(cuckoo_hash_map_##Tk##_##Tv##_element));                                                                                 \
		return res;                                                                                                                                                                                        \
	}                                                                                                                                                                                                    \
	cuckoo_hash_map_##Tk##_##Tv cuckoo_hash_map_##Tk##_##Tv##_new_with_size(size_t siz) {                                                                                                                \
		cuckoo_hash_map_##Tk##_##Tv res;                                                                                                                                                                   \
		res.size = siz;                                                                                                                                                                                    \
		res._1 = (cuckoo_hash_map_##Tk##_##Tv##_element *)calloc(res.size, sizeof(cuckoo_hash_map_##Tk##_##Tv##_element));                                                                                 \
		res._2 = (cuckoo_hash_map_##Tk##_##Tv##_element *)calloc(res.size, sizeof(cuckoo_hash_map_##Tk##_##Tv##_element));                                                                                 \
		return res;                                                                                                                                                                                        \
	}                                                                                                                                                                                                    \
	uint8_t cuckoo_hash_map_##Tk##_##Tv##_count(cuckoo_hash_map_##Tk##_##Tv *chm, Tk key) {                                                                                                              \
		return (chm->_1[cchmh1((uint8_t *)&key, sizeof(Tk)) % chm->size].k == key || chm->_2[cchmh2((uint8_t *)&key, sizeof(Tk)) % chm->size].k == key);                                                   \
	}                                                                                                                                                                                                    \
	Tv *cuckoo_hash_map_##Tk##_##Tv##_at(cuckoo_hash_map_##Tk##_##Tv *chm, Tk key) {                                                                                                                     \
		uint32_t h1 = cchmh1((uint8_t *)&key, sizeof(Tk)) % chm->size;                                                                                                                                     \
		if (chm->_1[h1].present && chm->_1[h1].k == key)                                                                                                                                                   \
			return &(chm->_1[h1].v);                                                                                                                                                                         \
		uint32_t h2 = cchmh2((uint8_t *)&key, sizeof(Tk)) % chm->size;                                                                                                                                     \
		if (chm->_2[h2].present && chm->_2[h2].k == key)                                                                                                                                                   \
			return &(chm->_2[h2].v);                                                                                                                                                                         \
		if (!chm->_1[h1].present) {                                                                                                                                                                        \
			chm->_1[h1].present = 1;                                                                                                                                                                         \
			chm->_1[h1].k = key;                                                                                                                                                                             \
			return &(chm->_1[h1].v);                                                                                                                                                                         \
		}                                                                                                                                                                                                  \
		if (!chm->_2[h2].present) {                                                                                                                                                                        \
			chm->_2[h2].present = 1;                                                                                                                                                                         \
			chm->_2[h2].k = key;                                                                                                                                                                             \
			return &(chm->_2[h2].v);                                                                                                                                                                         \
		}                                                                                                                                                                                                  \
		cuckoo_hash_map_##Tk##_##Tv##_element tmp = chm->_1[h1];                                                                                                                                           \
		chm->_1[h1].k = key;                                                                                                                                                                               \
		chm->_1[h1].present = 1;                                                                                                                                                                           \
		uint8_t looped = 1;                                                                                                                                                                                \
		while (tmp.k != key) {                                                                                                                                                                             \
			h2 = cchmh2((uint8_t *)&tmp.k, sizeof(Tk)) % chm->size;                                                                                                                                          \
			cuckoo_hash_map_##Tk##_##Tv##_element tmptmp = chm->_2[h2];                                                                                                                                      \
			chm->_2[h2] = tmp;                                                                                                                                                                               \
			if (tmptmp.present == 0) {                                                                                                                                                                       \
				looped = 0;                                                                                                                                                                                    \
				break;                                                                                                                                                                                         \
			}                                                                                                                                                                                                \
			h1 = cchmh1((uint8_t *)&tmptmp.k, sizeof(Tk)) % chm->size;                                                                                                                                       \
			tmp = chm->_1[h1];                                                                                                                                                                               \
			chm->_1[h1] = tmptmp;                                                                                                                                                                            \
			if (tmp.present == 0) {                                                                                                                                                                          \
				looped = 0;                                                                                                                                                                                    \
				break;                                                                                                                                                                                         \
			}                                                                                                                                                                                                \
		}                                                                                                                                                                                                  \
		if (!looped)                                                                                                                                                                                       \
			return &(chm->_1[cchmh1((uint8_t *)&key, sizeof(Tk)) % chm->size].v);                                                                                                                            \
		cuckoo_hash_map_##Tk##_##Tv nchm = cuckoo_hash_map_##Tk##_##Tv##_new_with_size((chm->size << 1) | 1);                                                                                              \
		for (size_t i = 0; i < chm->size; ++i) {                                                                                                                                                           \
			if (chm->_1[i].present) {                                                                                                                                                                        \
				*cuckoo_hash_map_##Tk##_##Tv##_at(&nchm, chm->_1[i].k) = chm->_1[i].v;                                                                                                                         \
			}                                                                                                                                                                                                \
			if (chm->_2[i].present) {                                                                                                                                                                        \
				*cuckoo_hash_map_##Tk##_##Tv##_at(&nchm, chm->_2[i].k) = chm->_2[i].v;                                                                                                                         \
			}                                                                                                                                                                                                \
		}                                                                                                                                                                                                  \
		*cuckoo_hash_map_##Tk##_##Tv##_at(&nchm, tmp.k) = tmp.v;                                                                                                                                           \
		free(chm->_1);                                                                                                                                                                                     \
		free(chm->_2);                                                                                                                                                                                     \
		*chm = nchm;                                                                                                                                                                                       \
		return cuckoo_hash_map_##Tk##_##Tv##_at(chm, key);                                                                                                                                                 \
	}                                                                                                                                                                                                    \
	void cuckoo_hash_map_##Tk##_##Tv##_erase(cuckoo_hash_map_##Tk##_##Tv *chm, Tk key) {                                                                                                                 \
		uint32_t h1 = cchmh1((uint8_t *)&key, sizeof(Tk)) % chm->size;                                                                                                                                     \
		if (chm->_1[h1].present && chm->_1[h1].k == key) {                                                                                                                                                 \
			chm->_1[h1].present = 0;                                                                                                                                                                         \
			return;                                                                                                                                                                                          \
		}                                                                                                                                                                                                  \
		uint32_t h2 = cchmh2((uint8_t *)&key, sizeof(Tk)) % chm->size;                                                                                                                                     \
		if (chm->_2[h2].present && chm->_2[h2].k == key) {                                                                                                                                                 \
			chm->_1[h2].present = 0;                                                                                                                                                                         \
			return;                                                                                                                                                                                          \
		}                                                                                                                                                                                                  \
	}

#endif
