#include "myshell.h"

void cleanup_shell(t_shell_data *shell)
{
	t_env_data	*current;
	t_env_data	*next;

	current = shell->shell_env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_token(t_token *tokens)
{
	t_token *current;
	t_token *next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
