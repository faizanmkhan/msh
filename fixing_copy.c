// for debugging ignore this file

static int	check_token_v2(t_token **token,
		t_cmd *current, t_shell_data *myshell)
{
	if ((*token)->type == TOK_OUT_DIRECT)
	{
		if (!(*token)->next || (*token)->next->type == TOK_PIPE)
			syntax_error(myshell);
		handle_outdirection(current, &(*token), 0);
		(*token) = (*token)->next;
		return (1);
	}
	else if ((*token)->type == TOK_APPEND)
	{
		if (!(*token)->next || (*token)->next->type == TOK_PIPE)
			syntax_error(myshell);
		handle_outdirection(current, &(*token), 1);
		(*token) = (*token)->next;
		return (1);
	}
	else if ((*token)->type == TOK_HEREDOC)
	{
		handle_heredoc_token(current, &(*token));
		return (1);
	}
	return (0);
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
		else if (check_token_v2(&token, current, myshell) == 1)
			continue ;
		token = token->next;
	}
}
/////////
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
		if (token->type == TOK_IN_DIRECT)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_indirection(current, &token);
			continue;
		}
		else if (token->type == TOK_OUT_DIRECT)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_outdirection(current, &token, 0);
			continue;
		}
		else if (token->type == TOK_APPEND)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_outdirection(current, &token, 1);
			continue;
		}
		else if (token->type == TOK_HEREDOC)
		{
			handle_heredoc_token(current, &token);
			continue;
		}
		token = token->next;
	}
}

///////
static int	check_token_v2(t_token **token,
		t_cmd *current, t_shell_data *myshell)
{
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_DQUOTE)
	{
		handle_word_expand(current, *token, myshell);
		(*token) = (*token)->next;
		return (1);
	}
	else if ((*token)->type == TOK_SQUOTE)
	{
		handle_argument_word(current, *token);
		(*token) = (*token)->next;
		return (1);
	}
	else if ((*token)->type == TOK_PIPE)
	{
		if (!(*token)->next || (*token)->next->type == TOK_PIPE)
			syntax_error(myshell);
		handle_pipe(&current);
		(*token) = (*token)->next;
		return (1);
	}
	return (0);
}

static void	check_token(t_token *token, t_cmd *current, t_shell_data *myshell)
{
	while (token)
	{
		if (token->type == TOK_IN_DIRECT)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_indirection(current, &token);
			continue;
		}
		else if (token->type == TOK_OUT_DIRECT)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_outdirection(current, &token, 0);
			continue;
		}
		else if (token->type == TOK_APPEND)
		{
			if (!token->next || token->next->type == TOK_PIPE)
				syntax_error(myshell);
			handle_outdirection(current, &token, 1);
			continue;
		}
		else if (token->type == TOK_HEREDOC)
		{
			handle_heredoc_token(current, &token);
			continue;
		}
		else if (check_token_v2(&token, current, myshell) == 1)
		token = token->next;
	}
}
