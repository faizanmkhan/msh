/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_restore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:34:03 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

bool	restore_fds(t_fds *fds)
{
	bool	ret;

	ret = true;
	if (!fds)
		return (ret);
	if (fds->stdin_cpy != -1)
	{
		if (dup2(fds->stdin_cpy, STDIN_FILENO) == -1)
			ret = false;
		wrapper_close_pipe(&fds->stdin_cpy);
		fds->stdin_cpy = -1;
	}
	if (fds->stdout_cpy != -1)
	{
		if (dup2(fds->stdout_cpy, STDOUT_FILENO) == -1)
			ret = false;
		wrapper_close_pipe(&fds->stdout_cpy);
		fds->stdout_cpy = -1;
	}
	return (ret);
}

void	std_backup(t_fds *fds, int *result)
{
	*result = true;
	fds->stdin_cpy = dup(STDIN_FILENO);
	if (fds->stdin_cpy == -1)
		*result = ft_print_cmd_error("dup", "stdin backup", strerror(errno),
				false);
	fds->stdout_cpy = dup(STDOUT_FILENO);
	if (fds->stdout_cpy == -1)
		*result = ft_print_cmd_error("dup", "stdout backup", strerror(errno),
				false);
}

bool	redirect(t_fds *fds)
{
	int	result;

	if (!fds)
		return (true);
	std_backup(fds, &result);
	if (fds->fd_in > -1)
		if (dup2(fds->fd_in, STDIN_FILENO) == -1)
			result = ft_print_cmd_error("dup2", fds->input_file,
					strerror(errno), false);
	if (fds->fd_out > -1)
		if (dup2(fds->fd_out, STDOUT_FILENO) == -1)
			result = ft_print_cmd_error("dup2", fds->output_file,
					strerror(errno), false);
	return (result);
}

int	valid_fds(t_fds *fds)
{
	if (!fds)
		return (OK);
	if (!fds->input_file && !fds->output_file)
		return (OK);
	if ((fds->input_file && fds->fd_in == -1) || (fds->output_file
			&& fds->fd_out == -1))
		return (BAD);
	return (OK);
}

int	valid_appdata(t_appdata *appdata)
{
	int	code;

	code = 0;
	if (!appdata->head_cmd)
	{
		g_exit_code = OK;
		return (code);
	}
	if (!appdata->head_cmd->name && !appdata->head_cmd->nxt)
	{
		if (appdata->head_cmd->fds)
			g_exit_code = valid_fds(appdata->head_cmd->fds);
		else
			g_exit_code = OK;
		return (code);
	}
	code = 1;
	return (code);
}
