/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:44:41 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static int	get_children(t_appdata *appdata)
{
	int		wstatus;
	int		tmp_status;
	int		restore_fds;
	pid_t	w_pid;

	restore_fds = false;
	close_fds(appdata->head_cmd, restore_fds);
	tmp_status = 0;
	w_pid = 0;
	while (w_pid != -1 || errno != ECHILD)
	{
		w_pid = waitpid(-1, &wstatus, 0);
		if (appdata->pid == w_pid)
			tmp_status = wstatus;
		continue ;
	}
	if (WIFEXITED(tmp_status))
		wstatus = WEXITSTATUS(tmp_status);
	else if (WIFSIGNALED(tmp_status))
		wstatus = 128 + WTERMSIG(tmp_status);
	else
		wstatus = tmp_status;
	return (wstatus);
}

int	create_children(t_appdata *appdata)
{
	t_cmd	*cmd;

	cmd = appdata->head_cmd;
	while (appdata->pid != 0 && cmd)
	{
		appdata->pid = fork();
		if (appdata->pid == 0)
			execute_command(appdata, cmd);
		else if (appdata->pid == -1)
			return (ft_print_cmd_error("fork", NULL, strerror(errno), BAD));
		cmd = cmd->nxt;
	}
	return (get_children(appdata));
}
