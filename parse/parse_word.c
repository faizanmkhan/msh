/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:08:20 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static void	split_var_cmd_token(t_cmd *cmd, char *data)
{
	t_tok	*toks;
	t_tok	*tmp;
	char	**strs;
	int		i;

	strs = ft_split(data, ' ');
	if (!strs)
		return ;
	if (strs[0])
		cmd->name = ft_strdup(strs[0]);
	i = -1;
	if (strs[++i])
	{
		toks = new_tok(ft_strdup(strs[i]), NULL, WORD, NORMAL);
		tmp = toks;
		while (strs[++i])
			add_back_tok(&toks, new_tok(ft_strdup(strs[i]), NULL, WORD,
					NORMAL));
		add_back_tok(&toks, new_tok(NULL, NULL, END, NORMAL));
		set_cmd_args(cmd, &toks);
		del_all_toks(&tmp, &free_ptr);
	}
	free_str_tab(strs);
}

void	parse_word(t_cmd **head_cmd, t_tok **head_tok)
{
	t_cmd	*cmd;
	t_tok	*tok;

	tok = *head_tok;
	while (tok->type == WORD || tok->type == VAR)
	{
		cmd = last_cmd(*head_cmd);
		if (tok->prv == NULL || cmd->name == NULL || (tok->prv
				&& tok->prv->type == PIPE))
		{
			if (tok->type == VAR && ft_strchr(tok->data, ' '))
				split_var_cmd_token(cmd, tok->data);
			else
				cmd->name = ft_strdup(tok->data);
			tok = tok->nxt;
		}
		else
			set_cmd_args(cmd, &tok);
	}
	*head_tok = tok;
}
