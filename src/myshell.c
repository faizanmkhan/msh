#include "../include/myshell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	myshell;

	(void) argc;
	(void) argv;
	init_shell_data(&myshell, envp);
	core_shell_loop(&myshell);
	cleanup_shell(&myshell);
	return (0);
}
