/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:59:04 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:59:04 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

t_cmd	*init_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->append_mode = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->next = NULL;
	return (cmd);
}

static void	check_token(t_token *token, t_cmd *current, t_shell_data *myshell)
{
	while (token)
	{
		if (token->type == TOK_WORD || token->type == TOK_DQUOTE)
			handle_word_expand(current, token, myshell);
		else if (token->type == TOK_SQUOTE)
			handle_argument_word(current, token);
		else if (token->type == TOK_PIPE)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_pipe(&current);
		}
		else if (token->type == TOK_IN_DIRECT)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_indirection(current, &token);
			continue ;
		}
		else if (token->type == TOK_OUT_DIRECT)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_outdirection(current, &token, 0);
			continue ;
		}
		else if (token->type == TOK_APPEND)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_outdirection(current, &token, 1);
			continue ;
		}
		else if (token->type == TOK_HEREDOC)
		{
			if (handle_heredoc_token(current, &token) == -1)
			{
				syntax_error(myshell);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
				break ;
			}
			continue ;
		}
		token = token->next;
	}
}

//ft_putstr_fd("\n", STDIN_FILENO); line 76
t_cmd	*create_cmd_with_token(t_shell_data *myshell)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*token;

	(void) myshell;
	if (!myshell->head_token)
		return (NULL);
	token = myshell->head_token;
	current = init_command();
	head = current;
	check_token(token, current, myshell);
	return (head);
}
