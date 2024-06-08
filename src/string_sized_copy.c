#include <stdio.h>
#include "string_sized_copy.h"
#include "string_length.h"


char* string_sized_copy(char* dest, char const* src, unsigned int size_max)
{
//	int src_len = string_length(src);

	if (dest == NULL)
		return NULL;

	if (src == NULL)
		return dest;

	for (unsigned int i = 0; i < size_max; ++i)
	{
		dest[i] = src[i];
	}

	return dest;
}
