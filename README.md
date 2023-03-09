# Array
Header only library that contains template like macros for creating dynamic arrays.

## Usage
```c
#include "array.h"

define_array(int);

#include <stdio.h>

int main(int argc, char const *argv[])
{
	array(int) integers = array_alloc(int);

	array_push(&integers, 0, int);
	array_push(&integers, 1, int);
	array_push(&integers, 2, int);
	array_push(&integers, 3, int);

	int buffer[] = {
		0, 1, 2, 3
	};

	array_concat(&integers, buffer, count(buffer), int);

	for(int i = 0; i < integers.ctElem; ++i)
		printf("%d\n", integers.data[i]);

	array_free(&integers, int);

	return 0;
}

```

## const char *
To define an array of `const char *` you must use a typedef.
```c
typedef const char *cstring;
define_array(cstring);
```
