#ifndef C_MACRO_STL_CMSTLSTRING_HEADER
#define C_MACRO_STL_CMSTLSTRING_HEADER

#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

define_vector(char)

		typedef struct {
	vector_char vc;
} cmstlstring;
cmstlstring cmstlstring_new() {
	cmstlstring res;
	res.vc = vector_char_new();
	vector_char_push_back(&res.vc, 0);
}
cmstlstring cmstlstring_new_from_input(FILE *f, unsigned char space_is_separator) {
	cmstlstring res;
	res.vc = vector_char_new();
	char c;
	while ((c = fgetc(f)) <= 32 && (c < 32 || !space_is_separator))
		;
	do {
		vector_char_push_back(&res.vc, c);
	} while ((c = fgetc(f)) > 32);
	vector_char_push_back(&res.vc, 0);
}
void cmstlstring_append(cmstlstring *s, cmstlstring *to_append) {
	for (size_t i = 0; i < to_append->vc.size - 1; ++i) {
		vector_char_push_back(&s->vc, to_append->vc.data[i]);
	}
}
void cmstlstring_push_back(cmstlstring *s, char c) { vector_char_insert(&s->vc, s->vc.size - 2, c); }
void cmstlstring_pop_back(cmstlstring *s) { vector_char_erase(&s->vc, s->vc.size - 2); }
char *cmstlstring_at(cmstlstring *s, size_t ind) {
	assert(ind < s->vc.size - 1);
	return s->vc.data + ind;
}

#endif
