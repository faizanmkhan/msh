/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:07:25 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static void	add_args_to_cmds(t_appdata *appdata)
{
	t_cmd	*cmd;

	if (!appdata || !appdata->head_cmd)
		return ;
	cmd = appdata->head_cmd;
	while (cmd && cmd->name)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->name);
			cmd->args[1] = NULL;
		}
		cmd = cmd->nxt;
	}
	cmd = last_cmd(appdata->head_cmd);
}

void	generate_cmd_list(t_appdata *appdata, t_tok *head_tok)
{
	t_tok	*tmp;

	tmp = head_tok;
	if (tmp->type == END)
		return ;
	while (tmp->nxt)
	{
		if (tmp == head_tok)
			add_back_cmd(&appdata->head_cmd, new_cmd());
		if (tmp->type == WORD || tmp->type == VAR)
			parse_word(&appdata->head_cmd, &tmp);
		else if (tmp->type == END)
			break ;
		else if (tmp->type == OUTPUT_REDIR)
			parse_output_redirection(&appdata->head_cmd, &tmp);
		else if (tmp->type == APPEND)
			parse_append(&appdata->head_cmd, &tmp);
		else if (tmp->type == INPUT_REDIR)
			parse_input_redirection(&appdata->head_cmd, &tmp);
		else if (tmp->type == HEREDOC)
			parse_heredoc(appdata, &appdata->head_cmd, &tmp);
		else if (tmp->type == PIPE)
			parse_pipe(&appdata->head_cmd, &tmp);
	}
	add_args_to_cmds(appdata);
}
