#include "main.h"

/**
 * get_flags - This calculate active flags.
 * @format: This formatted string in which to print the arguments.
 * @i: This take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int m, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (m = 0; FLAGS_CH[j] != '\0'; m++)
			if (format[curr_i] == FLAGS_CH[m])
			{
				flags |= FLAGS_ARR[m];
				break;
			}

		if (FLAGS_CH[m] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
