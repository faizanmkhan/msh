/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:57:00 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	update_flag(int *flag, char s)
{
	if (*flag == NORMAL)
	{
		if (s == '\'')
			*flag = QUOTE;
		else if (s == '\"')
			*flag = DQUOTE;
	}
	else if ((*flag == DQUOTE && s == '\"') || (*flag == QUOTE && s == '\''))
		*flag = NORMAL;
	return ;
}

int	get_separator(char *s)
{
	if ((s[0] > 8 && s[0] < 14) || s[0] == 32)
		return (WHITESPACE);
	else if (s[0] == '\0')
		return (END);
	else if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	else if (s[0] == '>')
		return (OUTPUT_REDIR);
	else if (s[0] == '<' && s[1] == '<')
		return (HEREDOC);
	else if (s[0] == '<')
		return (INPUT_REDIR);
	else if (s[0] == '|')
		return (PIPE);
	else
		return (0);
}
