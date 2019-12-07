#ifndef C_MACRO_STL_VECTOR_HEADER
#define C_MACRO_STL_VECTOR_HEADER

#include <assert.h>
#include <stdlib.h>

#define define_vector(T)                                                                                                                                                                               \
	typedef struct {                                                                                                                                                                                     \
		T *data;                                                                                                                                                                                           \
		size_t size;                                                                                                                                                                                       \
		size_t capacity;                                                                                                                                                                                   \
	} vector_##T;                                                                                                                                                                                        \
	vector_##T vector_##T##_new() {                                                                                                                                                                      \
		vector_##T res;                                                                                                                                                                                    \
		res.size = 0;                                                                                                                                                                                      \
		res.capacity = 2;                                                                                                                                                                                  \
		res.data = (T *)malloc(sizeof(T) * res.capacity);                                                                                                                                                  \
		return res;                                                                                                                                                                                        \
	}                                                                                                                                                                                                    \
	void vector_##T##_delete(vector_##T *v) { free(v->data); }                                                                                                                                           \
	size_t vector_##T##_size(vector_##T *v) { return v->size; }                                                                                                                                          \
	T *vector_##T##_at(vector_##T *v, size_t ind) {                                                                                                                                                      \
		assert(ind < v->size);                                                                                                                                                                             \
		return v->data + ind;                                                                                                                                                                              \
	}                                                                                                                                                                                                    \
	void vector_##T##_push_back(vector_##T *v, T val) {                                                                                                                                                  \
		if (v->size == v->capacity) {                                                                                                                                                                      \
			v->capacity *= 2;                                                                                                                                                                                \
			assert(v->data = realloc(v->data, sizeof(T) * v->capacity));                                                                                                                                     \
		}                                                                                                                                                                                                  \
		v->data[v->size++] = val;                                                                                                                                                                          \
	}                                                                                                                                                                                                    \
	void vector_##T##_insert(vector_##T *v, size_t ind, T val) {                                                                                                                                         \
		vector_##T##_push_back(v, val);                                                                                                                                                                    \
		for (size_t i = v->size - 1; i > ind; --i) {                                                                                                                                                       \
			v->data[i] = v->data[i - 1];                                                                                                                                                                     \
		}                                                                                                                                                                                                  \
		v->data[ind] = val;                                                                                                                                                                                \
	}                                                                                                                                                                                                    \
	void vector_##T##_pop_back(vector_##T *v) {                                                                                                                                                          \
		v->size--;                                                                                                                                                                                         \
		if (v->size < v->capacity / 4) {                                                                                                                                                                   \
			v->capacity /= 2;                                                                                                                                                                                \
			assert(v->data = realloc(v->data, sizeof(T) * v->capacity));                                                                                                                                     \
		}                                                                                                                                                                                                  \
	}                                                                                                                                                                                                    \
	void vector_##T##_erase(vector_##T *v, size_t ind) {                                                                                                                                                 \
		for (; ind < v->size - 1; ++ind) {                                                                                                                                                                 \
			v->data[ind] = v->data[ind + 1];                                                                                                                                                                 \
		}                                                                                                                                                                                                  \
		vector_##T##_pop_back(v);                                                                                                                                                                          \
	}                                                                                                                                                                                                    \
	void vector_##T##_clear(vector_##T *v) {                                                                                                                                                             \
		v->size = 0;                                                                                                                                                                                       \
		if (v->size < v->capacity / 4) {                                                                                                                                                                   \
			v->capacity = 2;                                                                                                                                                                                 \
			assert(v->data = realloc(v->data, sizeof(T) * v->capacity));                                                                                                                                     \
		}                                                                                                                                                                                                  \
	}                                                                                                                                                                                                    \
	void vector_##T##_resize(vector_##T *v, size_t new_size, T val) {                                                                                                                                    \
		if (new_size > v->size) {                                                                                                                                                                          \
			if (new_size >= v->capacity) {                                                                                                                                                                   \
				v->capacity = new_size * 2;                                                                                                                                                                    \
				assert(v->data = realloc(v->data, sizeof(T) * v->capacity));                                                                                                                                   \
			}                                                                                                                                                                                                \
			for (; v->size < new_size; ++v->size) {                                                                                                                                                          \
				v->data[v->size] = val;                                                                                                                                                                        \
			}                                                                                                                                                                                                \
		} else {                                                                                                                                                                                           \
			if (new_size < v->capacity / 4) {                                                                                                                                                                \
				v->capacity = new_size * 2;                                                                                                                                                                    \
				if (v->capacity == 0)                                                                                                                                                                          \
					v->capacity = 2;                                                                                                                                                                             \
				assert(v->data = realloc(v->data, sizeof(T) * v->capacity));                                                                                                                                   \
			}                                                                                                                                                                                                \
			v->size = new_size;                                                                                                                                                                              \
		}                                                                                                                                                                                                  \
	}

#endif
