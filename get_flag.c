#include "main.h"

/**
 * get_flag - Finds active flags
 * @format: Format of the string
 * @i: parameter
 * Return: All active Flags
 */

int get_flag(const char *format, int *i)
{
	int j, curr_i;
	int flag = 0;

	const char FLAGSIZE_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGSIZE_ARR[] = {FLAG_MINUS, FLAG_PLUS,
		FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGSIZE_CH[j] != '\0'; j++)
			if (format[curr_i] == FLAGSIZE_CH[j])
			{
				flag |= FLAGSIZE_ARR[j];
				break;
			}

		if (FLAGSIZE_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flag);
}
