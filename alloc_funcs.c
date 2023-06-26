#include "main.h"

/**
 * realloc_dptr - double pointer reallocation
 * @old_ptr: pointer previous memory(double)
 * @size1: ptr space in byte
 * @size2: new meory space in byte
 * Return: ptr or NULL if failed
 */

char **realloc_dptr(char **old_ptr, unsigned int size1, unsigned int size2)
{
	char **to_ptr;
	unsigned int idx;

	if (old_ptr == NULL)
		return (malloc(size2 * sizeof(char *)));
	if (size2 == size1)
		return (old_ptr);

	to_ptr = malloc(size2 * sizeof(char *));
	if (to_ptr == NULL)
		return (NULL);
	for (idx = 0; idx < size1; idx++)
		to_ptr[idx] = old_ptr[idx];

	free(old_ptr);
	return (to_ptr);
}

/**
 * _realloc - reallocates mem
 * @old_ptr: pointer previous memory
 * @size1: ptr space in byte
 * @size2: new meory space in byte
 * Return: ptr or NULL if failed
 */

void *_realloc(void *old_ptr, unsigned int size1, unsigned int size2)
{
	void *to_ptr;

	if (old_ptr == NULL)
		return (malloc(size2));
	if (size2 == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	if (size2 == size1)
		return (old_ptr);

	to_ptr = malloc(size2);
	if (to_ptr == NULL)
		return (NULL);
	if (size2 < size1)
		_memcpy(to_ptr, old_ptr, size2);
	else
		_memcpy(to_ptr, old_ptr, size1);

	free(old_ptr);

	return (to_ptr);
}


/**
 * _memcpy - copies info from on pointer to the other
 * @to_ptr: new pointer
 * @old_ptr: old pointer
 * @ptr_size: size of destination pointer
 * Return: none
 */

void _memcpy(void *to_ptr, const void *old_ptr, unsigned int ptr_size)
{
	unsigned int idx;
	char *old = (char *)old_ptr, *new = (char *)to_ptr;

	for (idx = 0; idx < ptr_size; idx++)
		new[idx] = old[idx];
}
