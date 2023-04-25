#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_unsigned(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convrt_size_unsignd(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsignd(0, i, buff, flag, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_octal(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num;

	NONUSED(width);

	num = convrt_size_unsignd(num, size);

	if (num == 0)
		buff[i--] = '\0';

	while (num > 0)
	{
		buff[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flag & FLAG_HASH && init_num != 0)
		buff[i--] = '0';

	i++;

	return (write_unsignd(0, i, buff, flag, width, precision, size));
}

/**
 * print_hexadecimal -Prints an unsigned number in hexadecimal
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_hexadecimal(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buff,
			flag, 'x', width, precision, size));
}

/**
 * print_up_hexad - Prints an unsigned num in upper hexadecimal
 * @types: List of arguments
 * @buff: Buffer
 * @flag: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_up_hexad(va_list types, char buff[],
		int flag, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buff,
			flag, "X", width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buff: Buffer
 * @flag: Flags
 * @flag_ch: Calculates active flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters
 */

int print_hexa(va_list types, char map_to[], char buff[],
	int flag, char flag_ch, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	NONUSED(width);

	num = convrt_size_unsignd(num, size);

	if (num == 0)
		buff[i--] = '\0';

	buff[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flag & FLAG_HASH && init_num != 0)
	{
		buff[i--] = flag_ch;
		buff[i--] = '0';
	}

	i++;

	return (write_unsignd(0, i, buff, flag, width, precision, size));
}
