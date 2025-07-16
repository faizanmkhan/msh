/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo_arg_setter_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:11:08 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	args_echo_size(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok && (tok->type == WORD || tok->type == VAR))
	{
		++i;
		if (tok->type == VAR && tok->join == true)
		{
			while (tok->type == VAR && tok->join == true)
				tok = tok->nxt;
		}
		else
			tok = tok->nxt;
	}
	return (i);
}

char	*join_echo_args(t_tok **tok)
{
	char	*str;
	char	*tmp_str;
	t_tok	*tmp;

	tmp = *tok;
	str = ft_strdup(tmp->data);
	while (tmp->type == VAR && tmp->nxt->type == VAR && tmp->nxt->join == true)
	{
		tmp_str = str;
		str = ft_strjoin(str, tmp->nxt->data);
		free(tmp_str);
		tmp = tmp->nxt;
	}
	*tok = tmp;
	return (str);
}

char	**recreate_echo_args(char **args, int size, t_cmd *cmd,
		t_tok **head_tok)
{
	int		i;
	t_tok	*tok;

	i = -1;
	tok = *head_tok;
	while (++i < size)
		args[i] = cmd->args[i];
	while (tok->type == WORD || tok->type == VAR)
	{
		if (tok->join == true)
			args[i] = join_echo_args(&tok);
		else
			args[i] = ft_strdup(tok->data);
		i++;
		tok = tok->nxt;
	}
	args[i] = NULL;
	return (args);
}

void	clear_empty_echo_vars(t_tok **tok)
{
	t_tok	*tmp;

	tmp = *tok;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->type == VAR && tmp->data[0] == '\0' && tmp->has_var == false)
		{
			tmp = tmp->nxt;
			if (tmp == (*tok)->nxt)
				(*tok) = (*tok)->nxt;
			del_tok(tmp->prv, free_ptr);
		}
		else
			tmp = tmp->nxt;
	}
}
