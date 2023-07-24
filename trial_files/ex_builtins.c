#include "main.h"

int handle_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias_value(char *alias_name, char *alias_value);
void print_aliases(alias_t *alias_list);

/**
 * handle_alias - Command that prints aliases, specific
 * aliases, or sets an alias.
 * @args: Array of arguments.
 * @front: Double pointer to the beginning of arguements.
 *
 * Return: If an error occurs -1, else 0.
 */
int handle_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp = aliases;
	int i, ret = 0;
	char *alias_value;

	if (!args[0])
	{
		while (tmp)
		{
			print_aliases(tmp);
			tmp = tmp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		alias_value = _strchr(args[i], '=');
		if (!alias_value)
		{
			while (tmp)
			{
				if (_strcmp(args[i], tmp->name) == 0)
				{
					print_aliases(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias_value(args[i], alias_value);
	}
	return (ret);
}

/**
 * set_alias_value - This fnc will either set an already existing
 * alias 'name' with a new value, called;
 * 'value' or creates a new alias with 'name' and 'value'.
 * @alias_name: Name of alias.
 * @alias_value: Value of alias. First character is an equal to '='.
 */
void set_alias_value(char *alias_name, char *alias_value)
{
	alias_t *tmp = aliases;
	int len, j, k;
	char *new_value;

	*alias_value = '\0';
	alias_value++;
	len = _strlen(alias_value) - _strspn(alias_value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; alias_value[j]; j++)
	{
		if (alias_value[j] != '\'' && alias_value[j] != '"')
			new_value[k++] = alias_value[j];
	}
	new_value[k] = '\0';
	while (tmp)
	{
		if (_strcmp(alias_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, alias_name, new_value);
}

/**
 * print_aliases - Prints alias in the format name ='value'.
 * @alias_list: Pointer to an alias.
 */
void print_aliases(alias_t *alias_list)
{
	char *alias_str;
	int len = _strlen(alias_list->name) + _strlen(alias_list->value) + 4;

	alias_str = malloc(sizeof(char) * (len + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias_list->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias_list->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, len);
	free(alias_str);
}

/**
 * replace_aliases - Goes through arguments and replaces any matching alias
 * with each of their values.
 * @args: Double pointer to the arguments.
 *
 * Return: Double pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *tmp;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[i], tmp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, tmp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}
