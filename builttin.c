#include "shell.h"

/**
 i* _myhisto - disp the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: contain potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: void
 */
int _myhisto(info_x *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - alias to string
 * @info: parameter structure
 * @str: string alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_x *info, char *str)
{
	char *q, d;
	int rat;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	rat = delete_node_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = d;
	return (rat);
}

/**
 * set_alias - set alias to string
 * @info: parameter structure
 * @stre: string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_x *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_x *node)
{
	char *s = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
