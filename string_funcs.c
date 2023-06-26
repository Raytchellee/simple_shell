#include "main.h"

/**
 * _strcat - concat strings
 * @dest: where to copy to
 * @src: pointer to copy from
 * Return: pointer to concatenated string
 */

char *_strcat(char *dest, const char *src)
{
	int length1, length2;

	length1 = length2 = 0;

	while (*(dest + length1) != '\0')
	{
		length1++;
	}
	while (*(src + length2) != '\0')
	{
		*(dest + length1) = *(src + length2);
		length1++;
		length2++;
	}
	*(dest + length1) = *(src + length2);

	return (dest);
}

/**
 * *_strcpy - copy string from on pointer to another
 * @dest: destination pointer
 * @src: where string will be copied from
 * Return: pointer to copied string
 */

char *_strcpy(char *dest, char *src)
{

	size_t idx = 0;

	for (; src[idx] != '\0'; idx++)
	{
		dest[idx] = src[idx];
	}
	dest[idx] = '\0';
	return (dest);
}

/**
 * _strcmp - check if two strings are equal
 * @s1: first string
 * @s2: second string
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int idx = 0;

	while (s1[idx] == s2[idx] && s1[idx])
		idx++;

	if (s1[idx] < s2[idx])
		return (-1);
	if (s1[idx] > s2[idx])
		return (1);
	return (0);
}

/**
 * _strspn - gets substring length
 * @a:byte count
 * @s: input string
 * Return: last index of s
 */

int _strspn(char *s, char *a)
{
	int idx, idy, check;

	for (idx = 0; *(s + idx) != '\0'; idx++)
	{
		check = 1;
		for (idy = 0; *(a + idy) != '\0'; idy++)
		{
			if (*(s + idx) == *(a + idy))
			{
				check = 0;
				break;
			}
		}
		if (check == 1)
		{
			break;
		}
	}
	return (idx);
}

/**
 * _strchr - finds char in string
 * @s: string to check
 * @c: the character to look for
 * Return: first char loaction
 */

char *_strchr(char *s, char c)
{
	unsigned int idx;

	for (idx = 0; *(s + idx) != '\0'; idx++)
	{
		if (*(s + idx) ==  c)
		{
			return (s + idx);
		}
	}
	if (*(s + idx) ==  c)
	{
		return (s + idx);
	}
	return ('\0');
}

