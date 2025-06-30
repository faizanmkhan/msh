#include "myshell.h"

int	command_execution(t_shell_data *myshell)
{
	t_cmd *cmd;
	
	cmd = myshell->head_cmd;
	if (!cmd)
		return (0);
	if(!cmd->next)
		return (execute_sigle_cmd(myshell));
	else
		return (execute_pipeline(myshell));
}

int execute_sigle_cmd(t_shell_data *myshell)
{
	pid_t pid;
	int status;
	char *executable;

	if (!myshell->head_cmd->args || !myshell->head_cmd->args[0])
		return (0);
	if (is_builtin(myshell->head_cmd->args[0]))
		return (execute_builtin(myshell, myshell->head_cmd));
	executable = find_executable(myshell, myshell->head_cmd->args[0]);
	if(!executable)
	{
		ft_putstr_fd("Error: Command not found!", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections(myshell->head_cmd) == -1)
			exit (1);
		execve(executable, myshell->head_cmd->args, myshell->envp);
		perror("execve");
		exit (127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free (executable);
		if(WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	else
	{
		perror("fork");
		free(executable);
		return (1);
	}
	return (0);
}