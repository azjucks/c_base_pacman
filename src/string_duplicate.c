#include <stdlib.h>
#include <stdio.h>
#include "string_length.h"
#include "string_sized_copy.h"


char* string_duplicate(char const* str)
{
	int			size = string_length(str) + 1;
	char*		duplicated;

	if (str == NULL)
		return NULL;

	duplicated = malloc((size + 1) * sizeof(char));

	duplicated[size] = '\0';

	string_sized_copy(duplicated, str, size);

	return duplicated;
}
