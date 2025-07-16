/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_operators.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:59:11 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:59:13 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

void	handle_pipe(t_cmd **current)
{
	(*current)->next = init_command();
	*current = (*current)->next;
}

void	handle_indirection(t_cmd *current, t_token **token)
{
	*token = (*token)->next;
	if (!*token)
		return ;
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_SQUOTE
		|| (*token)->type == TOK_DQUOTE)
	{
		current ->in_file = (*token)->value;
	}
}

void	handle_outdirection(t_cmd *current, t_token **token, int mode)
{
	*token = (*token)->next;
	if (!*token)
		return ;
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_SQUOTE
		|| (*token)->type == TOK_DQUOTE)
	{
		current ->out_file = (*token)->value;
		current->append_mode = mode;
	}
}

int	handle_heredoc_token(t_cmd *current, t_token **token)
{
	*token = (*token)->next;
	if (!*token)
		return (-1);
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_SQUOTE
		|| (*token)->type == TOK_DQUOTE)
	{
		current ->heredoc_delim = ft_strdup((*token)->value);
	}
	return (0);
}
