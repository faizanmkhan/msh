/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo_arg_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:10:15 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	create_echo_args(t_cmd *cmd, t_tok **head_tok)
{
	int		i;
	t_tok	*tok;

	clear_empty_echo_vars(head_tok);
	tok = *head_tok;
	cmd->args = malloc(sizeof(char *) * (args_echo_size(tok) + 2));
	if (!cmd->args)
		return (BAD);
	cmd->args[0] = ft_strdup(cmd->name);
	i = 1;
	while (tok && (tok->type == WORD || tok->type == VAR))
	{
		if (tok->join == true)
			cmd->args[i] = join_echo_args(&tok);
		else
			cmd->args[i] = ft_strdup(tok->data);
		i++;
		tok = tok->nxt;
	}
	cmd->args[i] = NULL;
	*head_tok = tok;
	return (OK);
}

int	update_echo_args(t_cmd *cmd, t_tok **head_tok)
{
	char	**args;
	int		i;
	t_tok	*tok;

	clear_empty_echo_vars(head_tok);
	tok = *head_tok;
	i = -1;
	while (cmd->args[++i])
		;
	args = malloc(sizeof(char *) * (i + args_echo_size(tok) + 1));
	if (!args)
		return (BAD);
	args = recreate_echo_args(args, i, cmd, head_tok);
	free(cmd->args);
	cmd->args = args;
	while (tok->type == WORD || tok->type == VAR)
		tok = tok->nxt;
	*head_tok = tok;
	return (OK);
}
