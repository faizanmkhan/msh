#include "../minishell.h"

int	pipe_loop(t_cmd *cmd, t_shell *shell)
{
	int	pipefd[2];
	int	prev_pipe_read;
	pid_t	pid;
	int	i;
	int	status;

	prev_pipe_read = -1;
	i = 0;

	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
				return (-1);
		}
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if (i != 0)
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
		else
		{
			if (i != 0)
				close(prev_pipe_read);
			if (cmd->next)
				close(pipefd[1]);
			if (cmd->next)
				prev_pipe_read = pipefd[0];
			else
				prev_pipe_read = -1;
			cmd = cmd->next;
			i++;
		}
	}
	while (wait(&status) > 0)
		;
	return (0);
}

/*int	pipe_loop(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (i != 0)	
			input_redir(cmd, shell, ".f_temp");
		if (cmd->next)
			output_redir(cmd, shell, ".f_temp", 0);
		else if (cmd->output_file)
			output_redir(cmd, shell, NULL, cmd->append_mode);
		else
			if (reset_redir(shell) == -1)
				return (-1);
		check_is_buildin(cmd->args, shell);
		cmd = cmd->next;
		i++;
	}
	return (0);			
}

int	pipe_loop(t_cmd *cmds, t_shell *shell)
{
	int	fd[2];
	int	pid;
	char	buffer[1024];
	ssize_t	n;

	while (cmds->next)
	{
		pipe(fd);
		pid = fork();
		if(pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STD_OUT);
			close(fd[1]);
			check_is_buildin(cmds->args, shell);
			exit(1);
		}
		else
		{
			close(fd[1]);
			while ((n = read(fd[0], buffer, sizeof(buffer)-1)) > 0)
			{
				buffer[n] = '\0';
				printf("Parent received: %s", buffer);
			}
			close(fd[0]);
			wait(0);
		}
		cmds = cmds->next;
	}
	return (0);
}
*/
