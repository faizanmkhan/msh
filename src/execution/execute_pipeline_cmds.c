/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_cmds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:07:16 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:07:17 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static int	execute_loop(t_cmd *current, t_shell_data *myshell, int prev_fd)
{
	int		res;
	pid_t	pid;

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
				return (res);
		}
		else
		{
			perror("fork");
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	execute_pipeline(t_shell_data *myshell)
{
	t_cmd	*current;
	int		prev_fd;
	int		loop_result;

	prev_fd = -1;
	current = myshell->head_cmd;
	loop_result = execute_loop(current, myshell, prev_fd);
	if (loop_result != 0)
		return (loop_result);
	while (wait(NULL) > 0)
		;
	return (0);
}
