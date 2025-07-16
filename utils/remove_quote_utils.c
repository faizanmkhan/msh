/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:06:13 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static bool	is_first_quote(t_tok *tok, int i)
{
	return ((tok->data[i] == '\'' || tok->data[i] == '\"')
		&& tok->status == NORMAL);
}

static void	change_status_to_quote(t_tok *tok, int *i)
{
	if (tok->data[*i] == '\'')
		tok->status = QUOTE;
	else if (tok->data[*i] == '\"')
		tok->status = DQUOTE;
	(*i)++;
}

static bool	is_end_quote(t_tok *tok, int i)
{
	return ((tok->data[i] == '\'' || tok->data[i] == '\"')
		&& (tok->status == QUOTE || tok->status == DQUOTE));
}

static bool	change_status_to_normal(t_tok *tok, int *i)
{
	if ((tok->data[*i] == '\'' && tok->status == QUOTE)
		|| (tok->data[*i] == '\"' && tok->status == DQUOTE))
	{
		tok->status = NORMAL;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

bool	should_change_status(t_tok *tok, int *i)
{
	if (is_first_quote(tok, *i))
	{
		change_status_to_quote(tok, i);
		return (true);
	}
	else if (is_end_quote(tok, *i) && change_status_to_normal(tok, i))
	{
		return (true);
	}
	return (false);
}
