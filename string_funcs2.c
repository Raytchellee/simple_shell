#include "main.h"

/**
 * _strlen - gets length of string
 * @s: input string
 * Return: 0
 */

int _strlen(const char *s)
{
	int length = 0;

	while (s[length] != 0)
	{
		length++;
	}
	return (length);
}

/**
 * _strdup - duplicates string in memory
 * @str: string pointer
 * Return: pointer to duplicated string
 */

char *_strdup(const char *str)
{
	size_t length;
	char *copy;

	length = _strlen(str);
	copy = malloc((1 + length) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	_memcpy(copy, str, length + 1);
	return (copy);
}

/**
 * _isdigit - checks if a string is a number
 * @s: string to check
 * Return: 1 if true 0 otherwise
 */

int _isdigit(const char *s)
{
	unsigned int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] <= 47 || s[idx] >= 58)
			return (0);
	}

	return (1);
}

/**
 * str_compare - compare string characters
 * @in: strng to check
 * @sep: string to compare
 * Return: if equal, 1 else 0
 */

int str_compare(char in[], const char *sep)
{
	unsigned int idx, idy, idz;

	for (idx = 0, idz = 0; in[idx]; idx++)
	{
		for (idy = 0; sep[idy]; idy++)
		{
			if (in[idx] == sep[idy])
			{
				idz++;
				break;
			}
		}
	}

	if (idx == idz)
	{
		return (1);
	}
	return (0);
}

/**
 * _strtok - uses delimiter to split string
 * @in: string to split
 * @sep: the string delim
 * Return: split value
 */

char *_strtok(char in[], const char *sep)
{
	char *begin;
	unsigned int idx, check;
	static char *temp, *stop;

	if (in != NULL)
	{
		if (str_compare(in, sep))
			return (NULL);
		temp = in;
		idx = _strlen(in);
		stop = &in[idx];
	}
	begin = temp;
	if (begin == stop)
		return (NULL);
	for (check = 0; *temp; temp++)
	{
		if (temp != begin)
			if (*temp && *(temp - 1) == '\0')
				break;
		for (idx = 0; sep[idx]; idx++)
		{
			if (*temp == sep[idx])
			{
				*temp = '\0';
				if (temp == begin)
				{
					begin++;
				}
				break;
			}
		}
		if (check == 0 && *temp)
		{
			check = 1;
		}
	}
	if (check == 0)
		return (NULL);
	return (begin);
}

