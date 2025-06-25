#include "myshell.h"

void managing_input(t_shell_data *myshell, char *input)
{
	(void)myshell;

	if(ft_isprint(*input))
	{
		if (!isspace(*input))
			add_history(input);
	}
	myshell->head_token = input_tokenaizer(input);
	myshell->head_cmd = create_cmd_with_token(myshell);
	// test
	
}
t_token	*input_tokenaizer(char *input_str)
{
	int i;
	t_token	*head;
	t_token *current;
	t_token	*new_token;

	head = NULL;
	current = NULL;
	new_token = NULL;
	i = 0;
	while(input_str[i])
	{
		while (ft_isspace(input_str[i]))
			i++;
		if (!input_str[i])
			break;
		if (input_str[i] == '\'' || input_str[i] == '"')
			new_token = handle_quote(input_str, &i, input_str[i]);
		else if (ft_strchr("|<>", input_str[i]))
			new_token = handle_metachar(input_str, &i);
		else
			new_token = handle_word(input_str, &i); // need to code
		if (!new_token)
			return (NULL);
		append_token(&head, &current, new_token); // need to code
	}
	return (head);
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

static char	*extract_word(char *input, int *i)
{
	int	start;
	int len;
	char *result;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_metachar(input[*i]) &&
			!is_quote(input[*i]))
			(*i)++;
	len = *i - start;
	result = malloc((len + 1)* sizeof(char));
	ft_strncpy(result, &input[start], len);
	result[len] = 0;
	return (result);
}

t_token	*handle_word(char *input, int *i)
{
	char	*data;
	t_token	*token;

	data = extract_word(input, i);
	if (!data)
		return (NULL);
	token = create_token(data, TOK_WORD);
	free(data);
	return (token);
}

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
