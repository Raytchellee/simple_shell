#include "main.h"

/**
 * append_sep - appends seperator to end of list
 * @hd: linkeed list head
 * @sep: input separator
 * Return: the linked list address
 */

separators_t *append_sep(separators_t **head, char sep)
{
	separators_t *copy, *curr;

	copy = malloc(sizeof(separators_t));
	if (copy == NULL)
		return (NULL);

	copy->sep_value = sep;
	copy->next = NULL;
	curr = *head;

	if (curr == NULL)
	{
		*head = copy;
	}
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = copy;
	}
	return (*head);
}

/**
 * free_separators_t - frees separators_t
 * @hd: linked list head
 * Return: none
 */

void free_separators_t(separators_t **hd)
{
	separators_t *copy, *node;

	if (hd != NULL)
	{
		node = *hd;
		while (node != NULL)
		{
			copy = node;
			node = node->next;
			free(copy);
		}
		*hd = NULL;
	}
}

/**
 * append_cmdl - appends cod line to linked list
 * @hd: linked list head
 * @cmdl: command line.
 * Return: the linked list address
 */

command_lines_t *append_cmdl(command_lines_t **hd, char *cmdl)
{
	command_lines_t *copy, *curr;

	copy = malloc(sizeof(command_lines_t));
	if (copy == NULL)
		return (NULL);

	copy->curr_line = cmdl;
	copy->next = NULL;
	curr = *hd;

	if (curr == NULL)
	{
		*hd = copy;
	}
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = copy;
	}
	return (*hd);
}

/**
 * free_command_lines_t - frees command_lines_t
 * @hd: linked list head
 * Return: none
 */

void free_command_lines_t(command_lines_t **hd)
{
	command_lines_t *copy, *node;

	if (hd != NULL)
	{
		node = *hd;
		while (node != NULL)
		{
			copy = node;
			node = node->next;
			free(copy);
		}
		*hd = NULL;
	}
}

