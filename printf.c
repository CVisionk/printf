#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int _strlen(const char *str);

/**
 * _printf - Custom printf function
 * @format: Format string containing conversion specifiers
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (format && format[count])
    {
        if (format[count] == '%' && format[count + 1])
        {
            count++; /* Move past '%' */
            switch (format[count])
            {
                case 'c':
                {
                    char c = (char)va_arg(args, int);
                    count += write(1, &c, 1);
                    break;
                }
                case 's':
                {
                    char *str = va_arg(args, char *);
                    count += write(1, str, _strlen(str));
                    break;
                }
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    count += write(1, &format[count - 1], 2); /* Print '%' and the unknown specifier */
            }
        }
        else
        {
            write(1, &format[count], 1);
            count++;
        }
    }

    va_end(args);
    return count;
}

/**
 * _strlen - Custom strlen function
 * @str: String to calculate the length of
 *
 * Return: Length of the string
 */
int _strlen(const char *str)
{
    int len = 0;
    while (str && str[len])
        len++;
    return len;
}