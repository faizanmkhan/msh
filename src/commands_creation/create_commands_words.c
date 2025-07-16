/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:59:18 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:59:19 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

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
	if (cmd->args)
	{
		i = -1;
		while (++i < count)
			new_arg[i] = cmd->args[i];
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

	final_arg = NULL;
	processing_env_expansion(token->value, myshell, &final_arg);
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_arg = malloc(sizeof(char *) * (count + 2));
	if (cmd->args)
	{
		i = -1;
		while (++i < count)
			new_arg[i] = cmd->args[i];
		free (cmd->args);
	}
	new_arg[count] = final_arg;
	new_arg[count + 1] = 0;
	cmd->args = new_arg;
}
