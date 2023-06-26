#include "main.h"

/**
 * num_len - number length
 * @n: input num
 * Return: number length
 */

int num_len(int n)
{
	int count = 1;
	unsigned int num;

	if (n <= -1)
	{
		count++;
		num = n * -1;
	}
	else
	{
		num = n;
	}
	while (num >= 10)
	{
		count++;
		num = num / 10;
	}

	return (count);
}

/**
 * _to_string - integer to string conversion
 * @n: input num
 * Return: value of string conversion
 */

char *_to_string(int n)
{
	unsigned int num;
	int count = num_len(n);
	char *s;

	s = malloc((1 + count) * sizeof(char));
	if (s == 0)
		return (NULL);

	*(s + count) = '\0';

	if (n < 0)
	{
		num = n * -1;
		s[0] = '-';
	}
	else
	{
		num = n;
	}

	count--;
	do {
		*(s + count) = (num % 10) + '0';
		num = num / 10;
		count--;
	}
	while (num >= 1)
		;

	return (s);
}

/**
 * _atoi - str to int conversion
 * @c: string to convert
 * Return: converted int
 */

int _atoi(char *c)
{
	unsigned int total = 0;
	unsigned int curr = 0, res = 0, is_neg = 1;
	unsigned int idx, mod = 1;

	while (*(c + total) != '\0')
	{
		if (curr > 0 && (*(c + total) < '0' || *(c + total) > '9'))
			break;

		if (*(c + total) == '-')
		{
			is_neg *= -1;
		}

		if ((*(c + total) >= '0') && (*(c + total) <= '9'))
		{
			if (curr > 0)
			{
				mod *= 10;
			}
			curr++;
		}
		total++;
	}
	for (idx = total - curr; idx < total; idx++)
	{
		res = res + ((*(c + idx) - 48) * mod);
		mod /= 10;
	}

	return (res * is_neg);
}

/**
 * str_revrse - string reverse
 * @str: string to reverse
 * Return: none
 */

void str_revrse(char *str)
{
	char *res, curr;
	int len = 0, idx, idy;

	while (len >= 0)
	{
		if (str[len] == '\0')
			break;
		len++;
	}
	res = str;

	for (idx = 0; idx < (len - 1); idx++)
	{
		for (idy = idx + 1; idy > 0; idy--)
		{
			curr = *(res + idy);
			*(res + idy) = *(res + (idy - 1));
			*(res + (idy - 1)) = curr;
		}
	}
}
