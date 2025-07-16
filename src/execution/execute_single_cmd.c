/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:07:22 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:07:23 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static void	child_process(t_shell_data *myshell, char *executable)
{
	if (setup_redirections(myshell->head_cmd) == -1)
		exit (1);
	execve(executable, myshell->head_cmd->args, myshell->envp);
	perror("execve");
	exit (127);
}

static int	parent_process(pid_t pid, char *executable)
{
	int	status;

	waitpid(pid, &status, 0);
	free (executable);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	execute_single_cmd(t_shell_data *myshell)
{
	pid_t	pid;
	char	*executable;

	if (!myshell->head_cmd->args || !myshell->head_cmd->args[0])
		return (0);
	if (is_builtin(myshell->head_cmd->args[0]))
		return (execute_builtin(myshell, myshell->head_cmd));
	executable = find_executable(myshell, myshell->head_cmd->args[0]);
	if (!executable)
	{
		ft_putstr_fd("Error: Command not found!\n", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		child_process(myshell, executable);
	else if (pid > 0)
		return (parent_process(pid, executable));
	else
	{
		perror("fork");
		free(executable);
		return (1);
	}
	return (0);
}
