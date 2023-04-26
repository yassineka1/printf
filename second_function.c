#include "main.h"

/*
 * print_ptr - Prints the valueof a pointer
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_ptr(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	char xtra_c = 0, pad = ' ';
	int index = BUFFER_SIZE - 2, len = 2, pad_start = 1;
	/* len=2, for '0x'*/
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	NONUSED(width);
	NONUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFFER_SIZE - 1] = '\0';

	NONUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buff[index--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flag & FLAG_ZERO) && !(flag & FLAG_MINUS))
		pad = '0';

	if (flag & FLAG_PLUS)
		xtra_c = '+', len++;
	else if (flag & FLAG_SPACE)
		xtra_c = ' ', len++;

	index++;

	return (write_ptr(buff, index, len, width, flag, pad, xtra_c, pad_start));
}

/**
 * print_nonprintable - Prints ASCII codes for non printable char
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_nonprintable(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	NONUSED(flag);
	NONUSED(width);
	NONUSED(precision);
	NONUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buff[i + offset] = str[i];
		else
		offset += append_hexadecimal(str[i], buff, i + offset);

		i++;
	}

	buff[i + offset] = '\0';

	return (write(1, buff, i + offset));
}

/**
 * print_rev - Prints a reversed string
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_rev(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	NONUSED(buff);
	NONUSED(flag);
	NONUSED(width);
	NONUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		NONUSED(precision);

		str = ")Null(";
	}

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}

	return (count);
}

/**
 * print_rot13str - Prints a string in rot13
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_rot13str(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);

	NONUSED(buff);
	NONUSED(flag);
	NONUSED(width);
	NONUSED(precision);
	NONUSED(size);

	if (str == NULL)
		str = "(AHYY)";

	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}

		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}

	return (count);
}
