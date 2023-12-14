#include "shell.h"
/**
 *  _exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @c: Count
 * Return: Void
 */
void  exit_bul(char **cmd, char *input, char **argv, int c)
{
	int stat, r = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	while (cmd[1][r])
	{
		if (_isalpha(cmd[1][r++]) != 0)
		{
			_prerror(argv, c, cmd);
			break;
		}
		else
		{
			stat = _atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(stat);
		}
	}
}


/**
 * _change_dir - Change Dirctorie
 * Return: 0
 */
int change_dir(char **cmd, __attribute__((unused))int er)
{
	int t = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		t = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		t = chdir(getenv("OLDPWD"));
	}
	else
		t = chdir(cmd[1]);

	if (t == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (t != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * _dis_env - display env
 * Return:0
 */
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
size_t r;
	int j;

	for (r = 0; environ[r] != NULL; r++)
	{
		j = _strlen(environ[r]);
		write(1, environ[r], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * display_help - help
 * @cmd: command
 * @er: status
 * Return: 0
 */
int display_help(char **cmd, __attribute__((unused))int er)
{
	int doc, w, d = 1;
	char z;

	doc = open(cmd[1], O_RDONLY);
	if (doc < 0)
	{
		perror("Error");
		return (0);
	}
	while (d > 0)
	{
		d = read(doc, &z, 1);
		w = write(STDOUT_FILENO, &z, d);
		if (w < 0)
		{
			return (-1);
		}
	}
	_putchar('\n');
	return (0);
}
/**
 * _echo_bul - echo command
 * Return: 0
 */
int echo_bul(char **cmd, int st)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number_in(st);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");

	}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);

	}
	else
		return (print_echo(cmd));

	return (1);
}
