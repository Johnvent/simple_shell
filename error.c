#include "shell.h"
/**
 *  _prerror - printing error
 *eput prnt input string
 * @c: counter
 * 
 * Return nothing
 */
void _prerror(char **argv, int fc, char **cmd)
{
	char *err = _itoa(fc);

	PRINTER(argv[0]);
	PRINTER(": ");
	PRINTER(err);
	PRINTER(": ");
	PRINTER(cmd[0]);
	PRINTER(": Illegal number: ");
	PRINTER(cmd[1]);
	PRINTER("\n");
	free(err);
}
