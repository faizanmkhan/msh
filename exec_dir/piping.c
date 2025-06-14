#include "../minishell.h"

void	fork_child(int *pipefd, int prev_pipe_read, t_cmd *cmd, t_shell *shell)
{
	if (shell->cmd_index != 0)
	{
		dup2(prev_pipe_read, STD_IN);
		close (prev_pipe_read);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STD_OUT);
		close(pipefd[1]);
	}
	check_is_buildin(cmd->args, shell);
	exit (EXIT_FAILURE);
}

t_cmd	*fork_parent(int *pipefd, t_cmd *cmd,
		int *prev_pipe_read, t_shell *shell)
{
	if (shell->cmd_index != 0)
		close(*prev_pipe_read);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_pipe_read = pipefd[0];
	}
	else
		*prev_pipe_read = -1;
	shell->cmd_index++;
	return (cmd->next);
}

int	pipe_loop(t_cmd *cmd, t_shell *shell)
{
	int		pipefd[2];
	int		prev_pipe_read;
	int		status;
	pid_t	pid;

	prev_pipe_read = -1;
	shell->cmd_index = 0;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipefd) == -1)
				return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			fork_child(pipefd, prev_pipe_read, cmd, shell);
		else
			cmd = fork_parent(pipefd, cmd, &prev_pipe_read, shell);
	}
	while (wait(&status) > 0)
		;
	return (0);
}
