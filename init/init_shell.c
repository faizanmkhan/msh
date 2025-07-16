/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:39:18 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	init_fds(t_cmd *cmd)
{
	if (!cmd->fds)
	{
		cmd->fds = malloc(sizeof(*cmd->fds));
		if (!cmd->fds)
			return ;
		cmd->fds->input_file = NULL;
		cmd->fds->fd_in = -1;
		cmd->fds->stdin_cpy = -1;
		cmd->fds->output_file = NULL;
		cmd->fds->fd_out = -1;
		cmd->fds->stdout_cpy = -1;
		cmd->fds->heredoc_delim = NULL;
		cmd->fds->heredoc_quotes = false;
	}
}

bool	init_appdata(t_appdata *appdata, int argc, char **argv, char **envp)
{
	((void)argc, (void)argv);
	if (!init_envl(appdata, envp))
	{
		ft_print_cmd_error("minishell", NULL, "Failed to initialize envl", 1);
		return (false);
	}
	g_exit_code = 0;
	appdata->input = NULL;
	appdata->head_tok = NULL;
	appdata->head_cmd = NULL;
	appdata->pid = -1;
	return (true);
}

void	free_appdata(t_appdata *appdata, bool clean_history)
{
	if (appdata)
	{
		if (appdata->input)
		{
			free_ptr(appdata->input);
			appdata->input = NULL;
		}
		if (appdata->head_tok)
			del_all_toks(&appdata->head_tok, &free_ptr);
		if (appdata->head_cmd)
			del_all_cmds(&appdata->head_cmd, &free_ptr);
	}
	if (clean_history)
	{
		if (appdata)
		{
			if (appdata->envl)
				free_str_tab(appdata->envl);
		}
		rl_clear_history();
	}
}
