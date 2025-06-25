#include "myshell.h"

static t_cmd	*init_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->in_file = NULL;
	cmd->out_file= NULL;
	cmd->heredoc_delim = NULL;
	cmd->append_mode = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->next = NULL;
	return (cmd);
}

char	*print_env(char *env_s)
{
	char	*new_str;
	char	*env_big;
	char	*pid_str;
	char	*fin_str;

	if (env_s[0] == '$')
	{
		pid_str = ft_itoa((int)getpid());//
		new_str = ft_substr(env_s, 1, ft_strlen(env_s) - 1);
		fin_str = ft_strjoin(pid_str, new_str);//
		free(pid_str);
		free(new_str);
		if (!fin_str)
			return (NULL);
		return (fin_str);
	}
	else
	{
		env_big = getenv(env_s);
		if (!env_big)
			env_big = ft_strdup("");
		return (env_big);
	}
	return (NULL);
}

int	ft_chr_pos(char *s, int start, char c)
{
	while (s[start])
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

char	*manage_env(char *s)
{
	int		sign_pos;
	int		space_i;
	char	*bef_s;
	char	*env_s;
	char	*final_str;
	char	*exp_env;

	sign_pos = ft_chr_pos(s, 0, '$');
	if (sign_pos == -1)
		return (s);
	bef_s = ft_substr(s, 0, sign_pos);
	space_i = ft_chr_pos(s, sign_pos, ' ');
	if (space_i == -1)
		space_i = ft_strlen(s);
	env_s = ft_substr(s, sign_pos + 1, space_i - sign_pos - 1);
	exp_env = print_env(env_s);//
	free(env_s);
	if (exp_env)
		final_str = ft_strjoin(bef_s, exp_env);
	free(bef_s);
	if (!final_str)
		return (NULL);
	return (final_str);
}

void	handle_argument_word_expand(t_cmd	*cmd, t_token *token)
{
	int		count;
	char	**new_arg;
	char	*final_arg;
	int		i;

	final_arg = manage_env(token->value);
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_arg = malloc(sizeof(char *) * (count + 2));
	if(cmd->args)
	{
		i = 0;
		while (i < count)
		{
			new_arg[i] = cmd->args[i];
			i++;
		}
		free (cmd->args);
	}
	new_arg[count] = final_arg;
	new_arg[count + 1] = 0;
	cmd->args = new_arg;
}

void	handle_argument_word(t_cmd	*cmd, t_token *token)
{
	int		count;
	char	**new_arg;
	char	*final_arg;
	int		i;
	
	final_arg = ft_strdup(token->value);
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_arg = malloc(sizeof(char *) * (count + 2));
	if(cmd->args)
	{
		i = 0;
		while (i < count)
		{
			new_arg[i] = cmd->args[i];
			i++;
		}
		free (cmd->args);
	}
	new_arg[count] = final_arg;
	new_arg[count + 1] = 0;
	cmd->args = new_arg;
}

void	handle_pipe(t_cmd **current)
{
	(*current)->next = init_command();
	*current = (*current)->next;
}

void	handle_indirection(t_cmd *current, t_token **token)
{
	*token = (*token)->next;
	if (!*token)
		return;
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_SQUOTE ||
			(*token)->type == TOK_DQUOTE)
			{
				current ->in_file = (*token)->value;
			}
}

void	handle_outdirection(t_cmd *current, t_token **token, int mode)
{
	*token = (*token)->next;
	if (!*token)
		return;
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_SQUOTE ||
			(*token)->type == TOK_DQUOTE)
			{
				current ->out_file = (*token)->value;
				current->append_mode = mode;
			}
}

void	handle_heredoc(t_cmd *current, t_token **token)
{
	*token = (*token)->next;
	if ((*token)->type == TOK_WORD || (*token)->type == TOK_SQUOTE ||
			(*token)->type == TOK_DQUOTE)
			{
				current ->heredoc_delim = ft_strdup((*token)->value);
			}
}

t_cmd	*create_cmd_with_token(t_shell_data *myshell)
{
	(void) myshell;
	t_cmd	*head;
	t_cmd	*current;
	t_token	*token;

	if (!myshell->head_token)
		return (NULL);
	token = myshell->head_token;
	current = init_command();
	head = current;
	while(token)
	{
		if (token->type == TOK_WORD || token->type == TOK_DQUOTE)
				handle_argument_word_expand(current, token);
		//else if (token->type == TOK_SQUOTE)
				//handle_argument_word(current, token);
		else if (token->type == TOK_PIPE)
				handle_pipe(&current); 
		else if (token->type == TOK_IN_DIRECT)
				handle_indirection(current, &token);
		else if (token->type == TOK_OUT_DIRECT)
				handle_outdirection(current, &token, 0);
		else if (token->type == TOK_APPEND)
				handle_outdirection(current, &token, 1); 
		else if (token->type == TOK_HEREDOC)
				handle_heredoc(current, &token); 
		token = token->next;	
	}
	return (head);
}
