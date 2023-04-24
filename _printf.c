#include "main.h"

void print_buffer(char buff[], int *buff_index);

/**
 * _printf - Printing function
 * @format: format
 * Return: Printed input
 */

int _printf(const char *format, ...)
{
	int i, prntd = 0, printed_chars = 0;
	int flag, width, precision, size, buff_index = 0;
	va_list list;
	char buff[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[buff_index++] = format[i];
			if (buff_index == BUFFER_SIZE)
				print_buffer(buff, &buff_index);
			printed_chars++;
		}
		else
		{
			print_buffer(buff, &buff_index);
			flag = get_flag(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			prntd = handler_print(format, &i, list, buff, flag, width, precision, size);
			if (prntd == -1)
				return (-1);
			printed_chars += prntd;
		}
	}

	print_buffer(buff, &buff_index);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the content of the buffer
 * @buff: Array of chars
 * @buff_index: Index of the buffer
 */

void print_buffer(char buff[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buff[0], *buff_index);

	*buff_index = 0;
}
