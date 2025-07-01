#include "../../include/myshell.h"

int	reset_redir(t_shell_data *shell)
{
	int	in;
	int	out;

	in = dup2(shell->saved_stdin, STDIN_FILENO);
	out = dup2(shell->saved_stdout, STDOUT_FILENO);
	if (in > 0 && out > 0)
		return (0);
	else
		return (-1);
}
