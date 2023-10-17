#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a single character.
 * @c: Character to be printed.
 * @buffer: Buffer array to handle printing.
 * @flags: Flag settings.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    // Handle zero-padding if the '0' flag is set
    if (flags & F_ZERO)
        padd = '0';

    // Store the character in the buffer
    buffer[i++] = c;
    buffer[i] = '\0';

    // Apply padding if the width is greater than 1
    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        // Check for left alignment and return the appropriate number of characters printed
        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
    }

    // Return the number of characters printed
    return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a number (integer or float).
 * @is_negative: Flag indicating if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Flag settings.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    // Handle zero-padding if the '0' flag is set
    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    // Determine the extra character ('-', '+', or ' ')
    if (is_negative)
        extra_ch = '-';
    else if (flags & F_PLUS)
        extra_ch = '+';
    else if (flags & F_SPACE)
        extra_ch = ' ';

    // Call a function to handle printing and return the number of characters printed
    return write_num(ind, buffer, flags, width, precision, length, padd, extra_ch);
}

/**
 * write_num - Write a number using a buffer.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Flag settings.
 * @width: Width specifier.
 * @prec: Precision specifier.
 * @length: Length of the number.
 * @padd: Padding character.
 * @extra_c: Extra character ('-', '+', or ' ').
 *
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[], int flags, int width, int prec, int length, char padd, char extra_c)
{
    int i, padd_start = 1;

    // Handle special case for zero precision and '0' as the only character
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return 0; /* printf(".0d", 0) - no character is printed */

    // Handle padding with ' ' if precision is zero and the number is '0'
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        buffer[ind] = padd = ' '; /* Display width with padding ' ' */

    // Add leading zeros for precision
    if (prec > 0 && prec < length)
        padd = ' ';
    while (prec > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    // Check for extra character and calculate the length
    if (extra_c != 0)
        length++;
    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = padd;
        buffer[i] = '\0';

        // Check for left alignment and return the appropriate number of characters printed
        if (flags & F_MINUS && padd == ' ')
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        }
        else if (!(flags & F_MINUS) && padd == ' ')
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
        else if (!(flags & F_MINUS) && padd == '0')
        {
            if (extra_c)
                buffer[--padd_start] = extra_c;
            return (write(1, &buffer[padd_start], i - padd_start) +
                write(1, &buffer[ind], length - (1 - padd_start)));
        }
    }

    // Handle extra character and return the number of characters printed
    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number (integer or float).
 * @is_negative: Flag indicating if the number is negative.
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Flag settings.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    // Initialize variables
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    // Handle special case for zero precision and '0' as the only character
    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return 0; /* printf(".0d", 0) - no character is printed */

    // Handle padding with '0' if the '0' flag is set
    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';


