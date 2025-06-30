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

void	handle_word_expand(t_cmd *cmd, t_token *token, t_shell_data *myshell)
{
	int		count;
	char	**new_arg;
	char	*final_arg;
	int		i;

	final_arg = processing_env_expansion(token->value, myshell);
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
				handle_word_expand(current, token, myshell);
		else if (token->type == TOK_SQUOTE)
				handle_argument_word(current, token);
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
