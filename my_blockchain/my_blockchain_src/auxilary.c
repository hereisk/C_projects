#include "header.h"

// extracts bid and nid from "add block bid nid\0"
int get_bid_nid(char *input, char *bid, char *nid)
{
    int space_count = 0;
    int input_index = 0;
    int bid_index = 0;
    int nid_index = 0;

    while(input[input_index] != '\0')
    {
        if(input[input_index] == ' ')
        {
            space_count++;
            input_index++;
        }

        if(space_count == 2)
        {
            bid[bid_index] = input[input_index];
            bid_index++;
        }

        if(space_count == 3)
        {
            nid[nid_index] = input[input_index];
            nid_index++;
        }
        input_index++;
    }

    bid[bid_index] = '\0';
    nid[nid_index] = '\0';

    return 0;

}

// converts string to an intiger
int _atoi(char *str)
{
    int sign;
    int val;
    int index;

    sign = 1;
    val = 0;
    index = 0;
    if (!str[index])
        return (0);
    while (str[index] == 32 || (str[index] >= 9 && str[index] <= 13))
        index++;
    if (str[index] == '-' || str[index] == '+')
    {
        if (str[index] == '-')
            sign = -1;
        index++;
    }
    while (str[index] >= '0' && str[index] <= '9')
        val = (10 * val) + ((str[index++]) - '0');
    return (sign * val);
}

// returns the total length of a string
int _strlen(char *string) {
    int i = 0;
    while(string[i] != '\0')
    {
      i++;
    }
    return i;
}

void print_itoa(long number, int base)
// to prints out a numbers as a string
{
    char *conversion_string = "0123456789abcdef";
    if (number >= base)
    {
        print_itoa(number / base, base);
        write(1, &conversion_string[number % base], (sizeof(char)));

    } else
    {
        write(1, &conversion_string[number % base], (sizeof(char)));
    }
}

int _printf(char* string, ...)
{
    char *s;
    int i;
    int index;
    va_list args;
    va_start(args, string);
    for(index = 0; string[index] != '\0'; index++)
    {
        if(string[index] != '%')
        {
            // the string is getting printed out until it reaches the flag %
            write(1, &string[index], sizeof(char));
        }
        if(string[index] == '%')
        // once the flag is reached a special case is evaluated
        {
            index++;
            switch(string[index])
            {
                case 's':// a handle to print a string
                    s = va_arg(args, char *);
                    if(s)
                    {
                        write(1, s, sizeof(char)*_strlen(s));
                    } else
                    {
                        write(1, "(null)", 6);
                    }
                    break;

                case 'c':// a handle to print a character
                    i = va_arg(args, int);
                    if(i)
                    {
                        write(1, &i, sizeof(char));
                    } else
                    {
                        write(1, "(null)", 6);
                    }
                    break;

                case 'i':// a handle to print an int
                    i = va_arg(args, int);
                    if (i < 0)
                    {
                        write(1, "-", sizeof(char));
                        i *= -1;
                    }
                    print_itoa(i, 10);
                    break;
            }
        }
    }
    va_end(args);
    return 0;
}

int _strcmp(char *string1, char *string2)
{
    for(; *string1 && *string2 && *string1 == *string2; string1++, string2++);
    return *string1 - *string2;
}

char* _strcpy(char *dest, const char *src) {
	int index = 0;

	while (src[index] != '\0') {
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char* _strdup(char *s1) {
	char *dup;

	dup = (char*)malloc(sizeof(*dup) * ((_strlen(s1)) + 1));
	if (dup == NULL)
		return (NULL);
	else
		_strcpy(dup, s1);
	return (dup);
}