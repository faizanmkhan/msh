/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:59:37 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 13:59:39 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

void	append_token(t_token **head, t_token **current, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
}

t_token	*create_token(char *data, t_tok_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(data);
	token->type = type;
	token->next = NULL;
	return (token);
}

static t_token	*operators_checker(char *input_str,
		t_token *head, t_token *current)
{
	int		i;
	t_token	*new_token;

	i = 0;
	new_token = NULL;
	while (input_str[i])
	{
		while (ft_isspace(input_str[i]))
			i++;
		if (!input_str[i])
			break ;
		if (input_str[i] == '\'' || input_str[i] == '"')
			new_token = handle_quote(input_str, &i, input_str[i]);
		else if (ft_strchr("|<>", input_str[i]))
			new_token = handle_metachar(input_str, &i);
		else
			new_token = handle_word(input_str, &i);
		if (!new_token)
			return (NULL);
		append_token(&head, &current, new_token);
	}
	return (head);
}

t_token	*input_tokenaizer(char *input_str)
{
	t_token	*head;
	t_token	*current;

	head = NULL;
	current = NULL;
	return (operators_checker(input_str, head, current));
}
