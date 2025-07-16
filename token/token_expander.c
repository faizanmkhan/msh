/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:58:36 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static bool	is_valid_env_var_char(char c)
{
	return (isalnum(c) || c == '_' || c == '?');
}

static bool	is_between_quotes(char *str, int i)
{
	return (i > 0 && str[i - 1] == '\"' && str[i + 1] == '\"');
}

static void	expand_env_var(t_appdata *appdata, t_tok *tok)
{
	int		i;
	char	*val;

	i = 0;
	while (tok->data[i])
	{
		update_flag(&tok->status, tok->data[i]);
		if (tok->data[i] == '$'
			&& ((tok->status == DQUOTE && tok->data[i + 1] != '\"')
				|| tok->status != DQUOTE)
			&& is_valid_env_var_char(tok->data[i + 1])
			&& !is_between_quotes(tok->data, i) && tok->status != QUOTE)
		{
			val = get_env_var_val(appdata, tok, tok->data + i);
			fill_env_var_val(tok, val, i);
		}
		else
			++i;
	}
}

void	expand_env_vars(t_appdata *appdata)
{
	t_tok	*tmp;

	tmp = appdata->head_tok;
	while (tmp)
	{
		if (tmp->type == VAR)
			expand_env_var(appdata, tmp);
		tmp = tmp->nxt;
	}
}

char	*expand_heredoc_vars(t_appdata *appdata, char *str)
{
	int		i;
	char	*val;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_valid_env_var_char(str[i + 1])
			&& !is_between_quotes(str, i))
		{
			val = get_env_var_val(appdata, NULL, str + i);
			str = fill_env_var_val_heredoc(str, val, i);
			free_ptr(val);
		}
		else
			++i;
	}
	return (str);
}
