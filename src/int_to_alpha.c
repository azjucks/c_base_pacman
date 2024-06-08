#include <stdio.h>
#include <stdlib.h>

int abs(int n)
{
	if (n < 0)
		return -n;
	return n;
}

char* int_to_alpha(int num)
{
	char*	alpha;
	char*	buffer;
	int		i = 0, is_negative = 0;

	alpha = malloc(12 * sizeof(int));
	buffer = malloc(12 * sizeof(int));

	if (num < 0)
	{
		num = -num;
		is_negative = 1;
	}

	do
	{
		buffer[i++] = abs(num % 10) + '0';
		num /= 10;
	}
	while(num != 0);

	if (is_negative)
	{
		buffer[i++]  = '-';
	}
	int j;

	for(j = 0; i > 0; j++)
		alpha[j] = buffer[--i];

	alpha[j] = '\0';

	free(buffer);

	return alpha;
}
