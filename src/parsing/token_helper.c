/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:59:33 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 13:59:33 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static t_token	*in_direction(char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			(*i) += 2;
			return (create_token("<<", TOK_HEREDOC));
		}
		else if (input[*i] == '<')
		{
			(*i)++;
			return (create_token("<", TOK_IN_DIRECT));
		}
		else
			return (NULL);
	}
	return (NULL);
}

static t_token	*out_direction(char *input, int *i)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			(*i) += 2;
			return (create_token(">>", TOK_APPEND));
		}
		else if (input[*i] == '>')
		{
			(*i)++;
			return (create_token(">", TOK_OUT_DIRECT));
		}
		else
			return (NULL);
	}
	return (NULL);
}

t_token	*handle_quote(char *input, int *i, char quote)
{
	char	*quoted_str;
	t_token	*token;

	token = NULL;
	quoted_str = extract_string(input, i);
	if (!quoted_str)
		return (NULL);
	if (quote == '\'')
		token = create_token(quoted_str, TOK_SQUOTE);
	else if (quote == '"')
		token = create_token(quoted_str, TOK_DQUOTE);
	free(quoted_str);
	return (token);
}

char	*extract_string(char *input, int *i)
{
	char	quote;
	int		start;
	int		len;
	char	*result;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (NULL);
	len = *i - start;
	result = malloc(len * sizeof(char) + 1);
	ft_strncpy(result, &input[start], len);
	result[len] = 0;
	(*i)++;
	return (result);
}

t_token	*handle_metachar(char *input, int *i)
{
	t_token	*token;

	if (input[*i] == '|')
	{
		(*i)++;
		token = create_token("|", TOK_PIPE);
		return (token);
	}
	else if (input[*i] == '<')
	{
		token = in_direction(input, i);
		return (token);
	}
	else if (input[*i] == '>')
	{
		token = out_direction(input, i);
		return (token);
	}
	return (NULL);
}
