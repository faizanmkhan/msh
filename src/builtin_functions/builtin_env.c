/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:57:30 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:57:34 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

int	builtin_unset(t_shell_data *shell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_value(shell, args[i]);
		i++;
	}
	return (0);
}

int	builtin_env(t_shell_data *shell)
{
	t_env_data	*current;

	current = shell->shell_env;
	while (current)
	{
		if (current->value && ft_strlen(current->value) > 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

char	*get_env_value(t_shell_data *shell, char *key)
{
	t_env_data	*current;

	current = shell->shell_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	set_env_value(t_shell_data *shell, char *key, char *value)
{
	t_env_data	*current;
	t_env_data	*new_env;

	current = shell->shell_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env_data));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = shell->shell_env;
	shell->shell_env = new_env;
}

void	unset_env_value(t_shell_data *shell, char *key)
{
	t_env_data	*current;
	t_env_data	*prev;

	current = shell->shell_env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->shell_env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
