/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:55:19 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	save_word(t_tok **head, char *input, int begin, int i)
{
	int		iter;
	char	*word;

	iter = -1;
	word = ft_calloc(i - begin + 1, sizeof(char));
	if (!word)
		return (1);
	while (begin < i)
		word[++iter] = input[begin++];
	word[++iter] = '\0';
	add_back_tok(head, new_tok(word, ft_strdup(word), WORD, NORMAL));
	return (0);
}

int	save_separator(t_tok **head, char *input, int type, int i)
{
	int		iter;
	char	*sep;
	int		size;

	if (type == APPEND || type == HEREDOC)
		size = 2;
	else
		size = 1;
	sep = ft_calloc(size + 1, sizeof(char));
	if (!sep)
		return (1);
	iter = -1;
	while (++iter < size)
		sep[iter] = input[i++];
	add_back_tok(head, new_tok(sep, NULL, type, NORMAL));
	return (0);
}

void	add_token(t_appdata *appdata, char *input, int *begin, int *i)
{
	int	tok_type;

	tok_type = get_separator(input + *i);
	if (tok_type)
	{
		if ((*i) != 0 && get_separator(input + (*i) - 1) == 0)
			save_word(&appdata->head_tok, input, *begin, *i);
		if (tok_type >= END)
		{
			save_separator(&appdata->head_tok, input, tok_type, *i);
			if (tok_type == APPEND || tok_type == HEREDOC)
				(*i)++;
		}
		*begin = (*i) + 1;
	}
	return ;
}

int	tokenize(t_appdata *appdata, char *input)
{
	int	i;
	int	begin;
	int	size;
	int	flag;

	i = -1;
	begin = 0;
	size = ft_strlen(input);
	flag = NORMAL;
	while (++i <= size)
	{
		update_flag(&flag, input[i]);
		if (flag == NORMAL)
			add_token(appdata, input, &begin, &i);
	}
	if (flag != NORMAL)
	{
		if (flag == DQUOTE)
			ft_print_error(EOF_ERR_MSG, "\"", true);
		if (flag == QUOTE)
			ft_print_error(EOF_ERR_MSG, "\'", true);
		return (BAD);
	}
	return (OK);
}
