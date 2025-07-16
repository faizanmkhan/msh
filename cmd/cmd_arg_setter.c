/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_setter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:09:13 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	args_size(t_tok *tok)
{
	int		i;
	t_tok	*tmp;

	i = 0;
	tmp = tok;
	while (tmp && (tmp->type == WORD || tmp->type == VAR))
	{
		++i;
		tmp = tmp->nxt;
	}
	return (i);
}

int	create_args(t_cmd *cmd, t_tok **head_tok)
{
	int		i;
	t_tok	*tok;

	tok = *head_tok;
	cmd->args = malloc(sizeof(char *) * (args_size(tok) + 2));
	if (!cmd->args)
		return (BAD);
	cmd->args[0] = ft_strdup(cmd->name);
	i = 1;
	while (tok && (tok->type == WORD || tok->type == VAR))
	{
		cmd->args[i++] = ft_strdup(tok->data);
		tok = tok->nxt;
	}
	cmd->args[i] = NULL;
	*head_tok = tok;
	return (OK);
}

static char	**recreate_args(char **args, int len, t_cmd *cmd, t_tok **head_tok)
{
	int		i;
	t_tok	*tok;

	i = 0;
	while (i < len)
	{
		args[i] = cmd->args[i];
		++i;
	}
	tok = *head_tok;
	while (tok && (tok->type == WORD || tok->type == VAR))
	{
		args[i++] = ft_strdup(tok->data);
		tok = tok->nxt;
	}
	args[i] = NULL;
	return (args);
}

int	update_args(t_cmd *cmd, t_tok **head_tok)
{
	char	**args;
	int		args_size;
	int		i;
	t_tok	*tok;

	args_size = 0;
	tok = *head_tok;
	while (tok->type == WORD || tok->type == VAR)
	{
		++args_size;
		tok = tok->nxt;
	}
	i = -1;
	while (cmd->args[++i])
		;
	args = malloc(sizeof(char *) * (i + args_size + 1));
	if (!args)
		return (BAD);
	args = recreate_args(args, i, cmd, head_tok);
	free(cmd->args);
	cmd->args = args;
	*head_tok = tok;
	return (OK);
}

int	set_cmd_args(t_cmd *cmd, t_tok **head_tok)
{
	if (ft_strncmp(cmd->name, "echo", 5) == 0)
	{
		if (!(cmd->args))
			return (create_echo_args(cmd, head_tok));
		else
			return (update_echo_args(cmd, head_tok));
	}
	else
	{
		if (cmd && !(cmd->args))
			return (create_args(cmd, head_tok));
		else
			return (update_args(cmd, head_tok));
	}
	return (OK);
}
