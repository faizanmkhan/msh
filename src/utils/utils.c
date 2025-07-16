/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:00:03 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 14:00:04 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

// void	cleanup_shell(t_shell_data *shell)
// {
// 	free_env(shell->shell_env);
// 	free_token(shell->head_token);
// 	free_commands(shell->head_cmd);
// }

void	free_env(t_env_data *env)
{
	t_env_data	*current;
	t_env_data	*next;

	current = env;
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
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		free_array(current->args);
		free(current->in_file);
		free(current->out_file);
		free(current->heredoc_delim);
		free(current);
		current = next;
	}
}
