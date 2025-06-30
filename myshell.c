
#include "myshell.h"

int g_signal;

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_shell_data myshell;
	//t_env_data *current;

	init_shell_data(&myshell, envp);
	core_shell_loop(&myshell);
	cleanup_shell(&myshell);
	return (0);
}

