#include "myshell.h"

void cleanup_shell(t_shell_data *shell)
{
	t_env_data	*current;
	t_env_data	*next;

	current = shell->myenv;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
