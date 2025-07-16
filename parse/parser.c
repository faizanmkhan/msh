/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:51:33 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static void	check_for_dollar_sign(t_tok **tok)
{
	int	i;

	i = -1;
	while ((*tok)->data[++i])
	{
		if ((*tok)->data[i] == '$')
		{
			if ((*tok)->prv && (*tok)->prv->type == HEREDOC)
				break ;
			(*tok)->type = VAR;
			return ;
		}
	}
}

static bool	prev_tok_is_separator(t_tok *tok)
{
	if (tok->type == PIPE && tok->prv->type == PIPE)
		return (true);
	if ((tok->type > VAR && tok->type <= PIPE)
		&& (tok->prv->type > VAR && tok->prv->type < PIPE))
		return (true);
	if (tok->type == END && tok->prv->type >= PIPE)
		return (true);
	return (false);
}

int	check_for_double_separators(t_tok **head_tok)
{
	t_tok	*tok;

	tok = *head_tok;
	while (tok)
	{
		if (tok->prv && prev_tok_is_separator(tok))
		{
			if (tok->type == END && tok->prv && tok->prv->type > PIPE)
				ft_print_error(SYNTAX_ERR_MSG, "newline", true);
			else if (tok->type == END && tok->prv)
				ft_print_error(SYNTAX_ERR_MSG, tok->prv->data, true);
			else
				ft_print_error(SYNTAX_ERR_MSG, tok->data, true);
			return (BAD);
		}
		tok = tok->nxt;
	}
	return (OK);
}

int	mark_vars(t_tok **head_tok)
{
	t_tok	*tmp;

	tmp = *head_tok;
	if (tmp->type == PIPE)
	{
		ft_print_error(SYNTAX_ERR_MSG, tmp->data, true);
		return (BAD);
	}
	while (tmp)
	{
		check_for_dollar_sign(&tmp);
		if (check_for_double_separators(&tmp) == BAD)
			return (BAD);
		tmp = tmp->nxt;
	}
	return (OK);
}

bool	parse_user_input(t_appdata *appdata)
{
	if (appdata->input == NULL)
		builtin_exit(appdata, NULL);
	else if (ft_strncmp(appdata->input, "\0", 1) == 0)
		return (false);
	else if (is_only_whitespace(appdata->input))
		return (true);
	add_history(appdata->input);
	if (tokenize(appdata, appdata->input) == BAD)
		return (false);
	if (mark_vars(&appdata->head_tok) == BAD)
		return (false);
	expand_env_vars(appdata);
	remove_quotes_in_toks(appdata);
	generate_cmd_list(appdata, appdata->head_tok);
	return (true);
}
