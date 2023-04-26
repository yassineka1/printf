#include "main.h"

/**
 * print_char - Prints a character
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_char(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (write_char_handle(c, buff, flag, width, precision, size));
}

/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_string(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(types, char *);

	NONUSED(buff);
	NONUSED(flag);
	NONUSED(width);
	NONUSED(precision);
	NONUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
	{
		len = precision;
	}
	if (width > len)
	{
		if (flag & FLAG_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/**
 * print_percent - Prints a % sign
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_percent(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	NONUSED(types);
	NONUSED(buff);
	NONUSED(flag);
	NONUSED(width);
	NONUSED(precision);
	NONUSED(size);

	return (write(1, "%%", 1));
}

/**
 * print_int - Prints integer
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_int(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_numb(n, size);

	if (n == 0)
		buff[i--] = '0';

	buff[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buff[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buff, flag, width, precision, size));
}

/**
 * print_binary: Prints an unsigned number
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_binary(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	NONUSED(buff);
	NONUSED(flag);
	NONUSED(width);
	NONUSED(precision);
	NONUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* m = (2 ^ 31) */
	a[0] = n / m;

	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}

	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];

		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}

	return (count);
}
