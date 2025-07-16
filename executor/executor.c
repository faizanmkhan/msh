/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:28:58 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	wrap_restore(int *backup, int std_fileno, int *exit_code)
{
	if (*backup != -1)
	{
		if (dup2(*backup, std_fileno) == -1)
			*exit_code = false;
		wrapper_close_pipe(&(*backup));
		*backup = -1;
	}
}

bool	use_backup_fd(t_fds *fds)
{
	int	exit_code;

	if (!fds)
		return (true);
	exit_code = true;
	wrap_restore(&(fds->stdin_cpy), STDIN_FILENO, &exit_code);
	wrap_restore(&(fds->stdout_cpy), STDOUT_FILENO, &exit_code);
	return (exit_code);
}

void	plumber(t_appdata *appdata, int *exit_code)
{
	t_cmd	*cmd;

	cmd = appdata->head_cmd;
	while (cmd)
	{
		if ((cmd->prv && cmd->prv->is_pipe_output) || cmd->is_pipe_output)
		{
			if (pipe(cmd->pipe_fd) == -1)
			{
				*exit_code = BAD;
				free_appdata(appdata, false);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				return ;
			}
		}
		cmd = cmd->nxt;
	}
	return ;
}

int	execute(t_appdata *appdata)
{
	int		exit_code;
	t_cmd	*exe;

	exe = appdata->head_cmd;
	exit_code = 127;
	plumber(appdata, &exit_code);
	if (exit_code != 127)
		return (exit_code);
	if (!exe->is_pipe_output && !exe->prv)
	{
		if (valid_fds(exe->fds))
			return (1);
		redirect(exe->fds);
		exit_code = execute_builtin(appdata, exe);
		use_backup_fd(exe->fds);
	}
	if (exit_code != 127)
		return (exit_code);
	return (create_children(appdata));
}
