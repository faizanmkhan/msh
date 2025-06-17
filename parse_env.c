#include "myshell.h"

t_env_data *parse_env_var(char *env_str)
{
	t_env_data	*new_env;
	char	*delimiter;
	char	*key;
	char	*value;

	delimiter = ft_strchr(env_str, '=');
	if (!delimiter)
		return NULL;
	*delimiter = 0;
	key = ft_strdup(env_str);
	value = ft_strdup(delimiter + 1);
	*delimiter = '=';
	new_env = malloc(sizeof(t_env_data));
	if (!new_env)
		return NULL;
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	return new_env;
}

void append_env_vars(t_shell_data *myshell, t_env_data *sh_env)
{
	t_env_data	*current;

	if(!myshell->myenv)
		myshell->myenv = sh_env;
	else
	{
		current = myshell->myenv;
		while (current->next)
			current = current->next;
		current->next = sh_env;
	}
}
