/*
	Copyright © 2023 Vaxeral

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the “Software”), to
	deal in the Software without restriction, including without limitation the
	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

#ifndef ARRAY_HEADER_INCLUDED
#define ARRAY_HEADER_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define count(a) (sizeof(a) / sizeof *(a))
#define array(T) T##_Array_Header

#define array_alloc(T) T##_array_alloc()
#define array_reserve(a, cpElem, T) T##_array_reserve(a, cpELem)
#define array_resize(a, ctElem, T) T##_array_resize(a, ctElem)
#define array_shrink(a, T) T##_array_shrink(a)
#define array_free(a, T) T##_array_free(a)
#define array_push(a, value, T) T##_array_push(a, value)
#define array_pop(a, T) T##_array_pop(a)
#define array_clear(a, T) T##_array_clear(a)
#define array_erase(a, index, T) T##_array_erase(a, index)
#define array_insert(a, value, index, T) T##_array_insert(a, value, index)
#define array_concat(a, values, ctElem, T) T##_array_concat(a, values, ctElem)
#define array_front(a, T) T##_array_front(a)
#define array_back(a, T) T##_array_back(a)
#define array_begin(a, T) T##_array_begin(a)
#define array_end(a, T) T##_array_end(a)
#define array_rbegin(a, T) T##_array_rbegin(a)
#define array_rend(a, T) T##_array_rend(a)
#define array_empty(a, T) T##_array_empty(a)

#define define_array_header(T)\
typedef struct T##_Array_Header {\
	size_t ctElem;\
	size_t cpElem;\
	T *data;\
} T##_Array_Header;
#define define_array_alloc(T)\
static T##_Array_Header T##_array_alloc(void) {\
	return (T##_Array_Header) {\
		.ctElem = 0,\
		.cpElem = 0,\
		.data = NULL\
	};\
}
#define define_array_reserve(T)\
static void T##_array_reserve(T##_Array_Header *this, size_t cpElem) {\
	if(cpElem > this->cpElem) {\
		void *p = realloc(this->data, cpElem * sizeof *this->data);\
		if(p == NULL) return;\
		this->data = p;\
		this->cpElem = cpElem;\
	}\
}
#define define_array_resize(T)\
static void T##_array_resize(T##_Array_Header *this, size_t ctElem) {\
	if(ctElem > this->cpElem) {\
		void *p = realloc(this->data, ctElem * sizeof *this->data);\
		if(p == NULL) return;\
		this->data = p;\
		this->cpElem = ctElem;\
	}\
	this->ctElem = ctElem;\
}
#define define_array_shrink(T)\
static void T##_array_shrink(T##_Array_Header *this) {\
	size_t cpElem = this->ctElem;\
	void *p = realloc(this->data, cpElem * sizeof *this->data);\
	if(p == NULL) return;\
	this->data = p;\
	this->cpElem = cpElem;\
}
#define define_array_free(T)\
static void T##_array_free(T##_Array_Header *this) {\
	free(this->data);\
	this->data = NULL;\
	this->ctElem = 0;\
	this->cpElem = 0;\
}
#define define_array_push(T)\
static void T##_array_push(T##_Array_Header *this, T value) {\
	if(this->ctElem + 1 > this->cpElem) {\
		size_t cpElem = (this->cpElem + 1) * 2;\
		void *p = realloc(this->data, cpElem * sizeof *this->data);\
		if(p == NULL) return;\
		this->data = p;\
		this->cpElem = cpElem;\
	}\
	this->data[this->ctElem] = value;\
	this->ctElem = this->ctElem + 1;\
}
#define define_array_push_s(T)\
static void T##_array_push_s(T##_Array_Header *this, T *value) {\
	if(this->ctElem + 1 > this->cpElem) {\
		size_t cpElem = (this->cpElem + 1) * 2;\
		void *p = realloc(this->data, cpElem * sizeof *this->data);\
		if(p == NULL) return;\
		this->data = p;\
		this->cpElem = cpElem;\
	}\
	this->data[this->ctElem] = *value;\
	this->ctElem = this->ctElem + 1;\
}
#define define_array_pop(T)\
static void T##_array_pop(T##_Array_Header *this) {\
	this->ctElem = this->ctElem - 1;\
}
#define define_array_clear(T)\
static void T##_array_clear(T##_Array_Header *this) {\
	this->ctElem = 0;\
}
#define define_array_erase(T)\
static void T##_array_erase(T##_Array_Header *this, size_t index) {\
	memmove(&this->data[index], &this->data[index + 1], (this->ctElem - 1 - index) * sizeof *this->data);\
	this->ctElem = this->ctElem - 1;\
}
#define define_array_insert(T)\
static void T##_array_insert(T##_Array_Header *this, T value, size_t index) {\
	if(this->ctElem + 1 > this->cpElem) {\
		size_t cpElem = this->ctElem + 1;\
		void *p = realloc(this->data, cpElem * sizeof *this->data);\
		if(p == NULL) return;\
		this->data = p;\
		this->cpElem = cpElem;\
	}\
	this->ctElem = this->ctElem + 1;\
	memmove(&this->data[index + 1], &this->data[index], (this->ctElem - 1 - index) * sizeof *this->data);\
	this->data[index] = value;\
}
#define define_array_concat(T)\
static void T##_array_concat(T##_Array_Header *this, T *values, size_t ctElem) {\
	if(this->ctElem + ctElem > this->cpElem) {\
		size_t cpElem = (this->cpElem + ctElem) * 2;\
		void *p = realloc(this->data, cpElem * sizeof *this->data);\
		if(p == NULL) return;\
		this->data = p;\
		this->cpElem = cpElem;\
	}\
	T *begin = this->data + this->ctElem;\
	T *end = begin + ctElem;\
	for(; begin != end; ++begin, ++values)\
		*begin = *values;\
	this->ctElem = this->ctElem + ctElem;\
}
#define define_array_front(T)\
static T *T##_array_front(T##_Array_Header *this) {\
	return this->data;\
}
#define define_array_back(T)\
static T *T##_array_back(T##_Array_Header *this) {\
	return this->data + this->ctElem - 1;\
}
#define define_array_begin(T)\
static T *T##_array_begin(T##_Array_Header *this) {\
	return this->data;\
}
#define define_array_end(T)\
static T *T##_array_end(T##_Array_Header *this) {\
	return this->data + this->ctElem;\
}
#define define_array_rbegin(T)\
static T *T##_array_rbegin(T##_Array_Header *this) {\
	return this->data + this->ctElem - 1;\
}
#define define_array_rend(T)\
static T *T##_array_rend(T##_Array_Header *this) {\
	return this->data - 1;\
}
#define define_array_empty(T)\
static bool T##_array_empty(T##_Array_Header *this) {\
	return this->ctElem == 0;\
}

#define define_array(T)\
define_array_header(T);\
define_array_alloc(T);\
define_array_reserve(T);\
define_array_resize(T);\
define_array_shrink(T);\
define_array_free(T);\
define_array_push(T);\
define_array_push_s(T);\
define_array_pop(T);\
define_array_clear(T);\
define_array_erase(T);\
define_array_insert(T);\
define_array_concat(T);\
define_array_front(T);\
define_array_back(T);\
define_array_begin(T);\
define_array_end(T);\
define_array_rbegin(T);\
define_array_rend(T);\
define_array_empty(T);\

#endif /* ARRAY_HEADER_INCLUDED */
