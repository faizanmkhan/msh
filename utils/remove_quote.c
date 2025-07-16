/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:05:18 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = NORMAL;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == NORMAL)
		{
			if (str[i] == '\'')
				status = QUOTE;
			else if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == QUOTE) || (str[i] == '\"'
				&& status == DQUOTE))
		{
			status = NORMAL;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

int	remove_quotes(t_tok *tok)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len(tok->data, i, i));
	if (!new_line)
		return (1);
	while (tok->data[i])
	{
		if (should_change_status(tok, &i))
			continue ;
		new_line[j++] = tok->data[i++];
	}
	new_line[j] = '\0';
	free_ptr(tok->data);
	tok->data = new_line;
	tok->join = true;
	return (0);
}

bool	quotes_in_tok(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (true);
		str++;
	}
	return (false);
}

int	remove_quotes_in_toks(t_appdata *appdata)
{
	t_tok	*tmp;

	tmp = appdata->head_tok;
	while (tmp)
	{
		if ((!tmp->prv || (tmp->prv && tmp->prv->type != HEREDOC))
			&& quotes_in_tok(tmp->data))
			remove_quotes(tmp);
		tmp = tmp->nxt;
	}
	return (0);
}
