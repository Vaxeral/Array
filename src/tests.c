#include "array.h"
#include <assert.h>

typedef const char *cstring;
define_array(cstring);
define_array(char);

void print_pastas(array(cstring) *a);

#include <stdio.h>

int main(int argc, char const *argv[])
{
	array(cstring) a = array_alloc(cstring);
	array_push(&a, "Spaghetti", cstring);
	array_push(&a, "Lasagna", cstring);
	array_push(&a, "Rigatoni", cstring);
	array_push(&a, "Tortellini", cstring);
	print_pastas(&a);
	/*
		   Pasta
		0: Spaghetti
		1: Lasagna
		2: Rigatoni
		3: Tortellini
	*/
	
	array_erase(&a, 1, cstring);
	print_pastas(&a);
	/*
		   Pasta
		0: Spaghetti
		1: Rigatoni
		2: Tortellini
	*/

	array_insert(&a, "Macaroni", 0, cstring);
	print_pastas(&a);
	/*
		   Pasta
		0: Macaroni
		1: Spaghetti
		2: Rigatoni
		3: Tortellini
	*/

	array_push(&a, "Ravioli", cstring);
	print_pastas(&a);
	/*
		   Pasta
		0: Macaroni
		1: Spaghetti
		2: Rigatoni
		3: Tortellini
		4: Ravioli
	*/

	printf("   %s\n", "Pasta");
	cstring *begin = array_rbegin(&a, cstring);
	cstring *end = array_rend(&a, cstring);
	for(int i = 0; begin != end; --begin, ++i)
		printf("%d: %s\n", i, *begin);
	printf("%s", "\n");
	/*
	   		Pasta
		0: Ravioli
		1: Tortellini
		2: Rigatoni
		3: Spaghetti
		4: Macaroni
	*/

	while(!array_empty(&a, cstring))
		array_pop(&a, cstring);
	assert(a.ctElem == 0);

	printf("capacity before shrink: %lu\n", a.cpElem);
	array_shrink(&a, cstring);
	printf("capacity after shrink: %lu\n", a.cpElem);
	
	array_free(&a, cstring);


	array(char) buffer = array_alloc(char);
	char greeting[] = "Hello ";
	array_concat(&buffer, greeting, count(greeting) - 1, char);
	char name[] = "Mordor";
	array_concat(&buffer, name, count(name), char);
	printf("%s\n", buffer.data);

	array_free(&buffer, char);
	return 0;
}

void print_pastas(array(cstring) *a)
{
	printf("   %s\n", "Pasta");
	for(int i = 0; i < a->ctElem; ++i)
		printf("%d: %s\n", i, a->data[i]);
	printf("%s", "\n");
}
