#include "main.h"
/**
 * handler_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @index: index.
 * @buff: Buffer array to handle print.
 * @flag: Calculates active flag
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handler_print(const char *format, int *index, va_list list, char buff[],
	int flag, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	format_t format_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_up_hexad}, {'p', print_ptr}, {'S', print_nonprintable},
		{'r', print_rev}, {'R', print_rot13str}, {'\0', NULL}
	};
	for (i = 0; format_types[i].format != '\0'; i++)
		if (format[*index] == format_types[i].format)
			return (format_types[i].fn(list, buff, flag, width, precision, size));

	if (format_types[i].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		unknow_len += write(1, &format[*index], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
