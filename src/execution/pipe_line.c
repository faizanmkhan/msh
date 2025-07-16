/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:07:38 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:07:39 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

int	setup_pipe_if_needed(t_cmd *current)
{
	if (current->next)
	{
		if (pipe(current->pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

int	handle_parent_process(pid_t pid, int *prev_fd, t_cmd *current)
{
	int	status;

	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(current->pipe_fd[1]);
		*prev_fd = current->pipe_fd[0];
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (-2);
}

void	cmd_not_found(void)
{
	ft_putstr_fd("Error: command not found\n", STDERR_FILENO);
	exit(127);
}

void	handle_child_process(t_shell_data *shell, t_cmd *current, int prev_fd)
{
	char	*executable;

	if (setup_redirections(current) == -1)
		exit(1);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		close(current->pipe_fd[0]);
		dup2(current->pipe_fd[1], STDOUT_FILENO);
		close(current->pipe_fd[1]);
	}
	if (is_builtin(current->args[0]))
		exit(execute_builtin(shell, current));
	executable = find_executable(shell, current->args[0]);
	if (!executable)
		cmd_not_found();
	execve(executable, current->args, shell->envp);
	perror("execve");
	exit(127);
}
