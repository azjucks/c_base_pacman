#include "string_sized_concatenate.h"
#include "string_length.h"
#include <stdio.h>


char* string_sized_concatenate(char* dest, char const* src, unsigned int size_max)
{
	int dest_len = string_length(dest);

	if (dest == NULL)
		return NULL;
	
	if (src == NULL)
		return dest;

	for (unsigned int i = 0; i < size_max; ++i)
	{
		dest[dest_len + i] = src[i];
	}
	
	dest[dest_len + size_max] = '\0';

	return dest;
}
