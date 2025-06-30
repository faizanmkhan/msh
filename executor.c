#include "myshell.h"

int	command_execution(t_shell_data *myshell)
{
	t_cmd *cmd;
	
	cmd = myshell->head_cmd;
	if (!cmd)
		return (0);
	if(!cmd->next)
		return (execute_single_cmd(myshell));
	else
		return (execute_pipeline(myshell));
	return (0);
}

int execute_single_cmd(t_shell_data *myshell)
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
		signal(SIGQUIT, quit_handler);
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

int execute_pipeline(t_shell_data *myshell)
{
	pid_t	pid;
	t_cmd *current;
	int prev_fd = -1;
	int res;

	current = myshell->head_cmd;
	while (current)
	{
		if (setup_pipe_if_needed(current) == -1)
			return (1);
		pid = fork();
		if (pid == 0)
			handle_child_process(myshell, current, prev_fd);
		else if (pid > 0)
		{
			res = handle_parent_process(pid, &prev_fd, current);
			if (res != -2)
				return res;
		}
		else
		{
			perror("fork");
			return 1;
		}
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	return 0;
}