#include "myshell.h"

void	init_shell_data(t_shell_data *myshell, char **envp)
{
	int	i;
	t_env_data	*env_var;
	
	myshell->exit_status = 0;
	myshell->envp = NULL;
	myshell->pid = -1;
	myshell->head_cmd = NULL;
	myshell->head_token = NULL;
	myshell->shell_env = NULL;
	i = 0;
	while (envp[i])
	{
		env_var = parse_env_var(envp[i]);
		if (env_var)
			append_env_vars(myshell, env_var);
		i++;
	}
}

void	core_shell_loop(t_shell_data *myshell)
{
	char	*input;

	// set_signal(); singnal handling function
	while(42)
	{
		input = readline("mY_sHEll:~$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (g_signal == SIGINT)
		{
			myshell->exit_status = 130;
			g_signal = 0;
		}
		if (input)
		{
			managing_input(myshell, input);
			check_cmd(myshell->head_cmd, myshell);
			reset_redir(myshell);
			//free_cmds()
		}
		free(input);
	}
}