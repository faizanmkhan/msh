/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:45:25 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static int	execute_sys_bin(t_appdata *appdata, t_cmd *cmd)
{
	int	i;

	if (!cmd->name || cmd->name[0] == '\0')
		return (127);
	i = look_env("PATH", appdata);
	if (i == -1)
		return (-1);
	cmd->path = find_path(appdata->envl, cmd->name, i);
	if (!cmd->path)
		return (127);
	if (execve(cmd->path, cmd->args, appdata->envl) == -1)
		ft_print_cmd_error("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	execute_local_bin(t_appdata *data, t_cmd *cmd, int code)
{
	int	ret;

	ret = check_command_not_found(cmd, code);
	if (ret != 0)
		return (ret);
	if (execve(cmd->name, cmd->args, data->envl) == -1)
		return (ft_print_cmd_error("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

void	set_pipe_fds(t_cmd *head_cmd, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	if (cmd->prv && cmd->prv->is_pipe_output)
		dup2(cmd->prv->pipe_fd[0], STDIN_FILENO);
	if (cmd->is_pipe_output)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	tmp = head_cmd;
	while (tmp)
	{
		if (!(tmp == cmd) && tmp->pipe_fd[0])
		{
			if (tmp->pipe_fd[0] != -1)
				wrapper_close_pipe(&tmp->pipe_fd[0]);
			if (tmp->pipe_fd[1] != -1)
				wrapper_close_pipe(&tmp->pipe_fd[1]);
		}
		tmp = tmp->nxt;
	}
	return ;
}

void	set_command_redir(t_cmd *head_cmd, t_cmd *cmd)
{
	bool	restore_fds;

	set_pipe_fds(head_cmd, cmd);
	redirect(cmd->fds);
	restore_fds = false;
	close_fds(head_cmd, restore_fds);
}

int	execute_command(t_appdata *appdata, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 127;
	if (valid_command(cmd, &exit_code) == 1)
		exit_minishell(appdata, ft_print_cmd_error("child", NULL,
				"parsing error: no command to execute!", exit_code));
	set_command_redir(appdata->head_cmd, cmd);
	if (!exit_code)
		exit_minishell(appdata, exit_code);
	if (ft_strchr(cmd->name, '/') == NULL)
	{
		exit_code = execute_builtin(appdata, cmd);
		if (exit_code != 127)
			exit_minishell(appdata, exit_code);
		exit_code = execute_sys_bin(appdata, cmd);
		if (exit_code == 127)
			ft_print_cmd_error(cmd->name, NULL, "command not found",
				127);
		if (exit_code != -1)
			exit_minishell(appdata, exit_code);
	}
	exit_code = execute_local_bin(appdata, cmd, exit_code);
	exit_minishell(appdata, exit_code);
	return (exit_code);
}
