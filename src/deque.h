#ifndef C_MACRO_STL_DEQUE_HEADER
#define C_MACRO_STL_DEQUE_HEADER

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define define_deque(T)                                                                                                                                                                                \
	typedef struct {                                                                                                                                                                                     \
		size_t capacity;                                                                                                                                                                                   \
		size_t size;                                                                                                                                                                                       \
		size_t l;                                                                                                                                                                                          \
		T *data;                                                                                                                                                                                           \
	} deque_##T;                                                                                                                                                                                         \
	deque_##T deque_##T##_new() {                                                                                                                                                                        \
		deque_##T res;                                                                                                                                                                                     \
		res.capacity = 1;                                                                                                                                                                                  \
		res.size = 0;                                                                                                                                                                                      \
		res.l = 0;                                                                                                                                                                                         \
		res.data = (T *)malloc(res.capacity * sizeof(T));                                                                                                                                                  \
		return res;                                                                                                                                                                                        \
	}                                                                                                                                                                                                    \
	void deque_##T##_enlarge(deque_##T *dq) {                                                                                                                                                            \
		size_t oldc = dq->capacity;                                                                                                                                                                        \
		dq->capacity *= 2;                                                                                                                                                                                 \
		dq->data = (T *)realloc(dq->data, dq->capacity * sizeof(T));                                                                                                                                       \
		if (dq->size > oldc - dq->l) {                                                                                                                                                                     \
			size_t nleft = dq->size - (oldc - dq->l);                                                                                                                                                        \
			memcpy(dq->data + oldc, dq->data, nleft * sizeof(T));                                                                                                                                            \
		}                                                                                                                                                                                                  \
	}                                                                                                                                                                                                    \
	void deque_##T##_reduce(deque_##T *dq) {                                                                                                                                                             \
		size_t nleft = 0;                                                                                                                                                                                  \
		if (dq->size > dq->capacity - dq->l) {                                                                                                                                                             \
			nleft = dq->size - (dq->capacity - dq->l);                                                                                                                                                       \
		}                                                                                                                                                                                                  \
		memmove(dq->data + nleft, dq->data + dq->l, (dq->size - nleft) * sizeof(T));                                                                                                                       \
		dq->l = nleft;                                                                                                                                                                                     \
		dq->capacity /= 2;                                                                                                                                                                                 \
		dq->data = (T *)realloc(dq->data, dq->capacity * sizeof(T));                                                                                                                                       \
	}                                                                                                                                                                                                    \
	void deque_##T##_push_back(deque_##T *dq, T val) {                                                                                                                                                   \
		if (dq->size == dq->capacity)                                                                                                                                                                      \
			deque_##T##_enlarge(dq);                                                                                                                                                                         \
		dq->data[(dq->l + dq->size) % dq->capacity] = val;                                                                                                                                                 \
		dq->size++;                                                                                                                                                                                        \
	}                                                                                                                                                                                                    \
	void deque_##T##_push_front(deque_##T *dq, T val) {                                                                                                                                                  \
		if (dq->size == dq->capacity)                                                                                                                                                                      \
			deque_##T##_enlarge(dq);                                                                                                                                                                         \
		dq->l = (dq->l + dq->capacity - 1) % dq->capacity;                                                                                                                                                 \
		dq->data[dq->l] = val;                                                                                                                                                                             \
		dq->size++;                                                                                                                                                                                        \
	}                                                                                                                                                                                                    \
	void deque_##T##_pop_back(deque_##T *dq) {                                                                                                                                                           \
		assert(dq->size);                                                                                                                                                                                  \
		dq->size--;                                                                                                                                                                                        \
		if (dq->capacity / 4 > dq->size) {                                                                                                                                                                 \
			deque_##T##_reduce(dq);                                                                                                                                                                          \
		}                                                                                                                                                                                                  \
	}                                                                                                                                                                                                    \
	void deque_##T##_pop_front(deque_##T *dq) {                                                                                                                                                          \
		assert(dq->size);                                                                                                                                                                                  \
		dq->l = (dq->l + 1) % dq->capacity;                                                                                                                                                                \
		dq->size--;                                                                                                                                                                                        \
		if (dq->capacity / 4 > dq->size) {                                                                                                                                                                 \
			deque_##T##_reduce(dq);                                                                                                                                                                          \
		}                                                                                                                                                                                                  \
	}                                                                                                                                                                                                    \
	T *deque_##T##_at(deque_##T *dq, size_t ind) {                                                                                                                                                       \
		assert(ind < dq->size);                                                                                                                                                                            \
		return dq->data + ((dq->l + ind) % dq->capacity);                                                                                                                                                  \
	}                                                                                                                                                                                                    \
	T *deque_##T##_back(deque_##T *dq) {                                                                                                                                                                 \
		assert(dq->size);                                                                                                                                                                                  \
		return dq->data + ((dq->l + dq->size - 1) % dq->capacity);                                                                                                                                         \
	}                                                                                                                                                                                                    \
	T *deque_##T##_front(deque_##T *dq) {                                                                                                                                                                \
		assert(dq->size);                                                                                                                                                                                  \
		return dq->data + dq->l;                                                                                                                                                                           \
	}

#endif
