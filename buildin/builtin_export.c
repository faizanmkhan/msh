/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:39:44 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	**allocate_env_var_split(int size)
{
	char	**env_var_split;

	env_var_split = malloc(sizeof(char *) * size);
	if (!env_var_split)
		return (NULL);
	return (env_var_split);
}

char	**handle_no_equal_sign(char *env_var)
{
	char	**env_var_split;

	env_var_split = allocate_env_var_split(2);
	if (!env_var_split)
		return (NULL);
	env_var_split[0] = ft_strdup(env_var);
	if (!env_var_split[0])
	{
		free(env_var_split);
		return (NULL);
	}
	env_var_split[1] = NULL;
	return (env_var_split);
}

char	**handle_equal_sign(char *env_var, char *first_eq)
{
	char	**env_var_split;

	env_var_split = allocate_env_var_split(3);
	if (!env_var_split)
		return (NULL);
	env_var_split[0] = ft_substr(env_var, 0, first_eq - env_var);
	if (!env_var_split[0])
	{
		free(env_var_split);
		return (NULL);
	}
	env_var_split[1] = ft_strdup(first_eq + 1);
	if (!env_var_split[1])
	{
		free(env_var_split[0]);
		free(env_var_split);
		return (NULL);
	}
	env_var_split[2] = NULL;
	return (env_var_split);
}

char	**extract_env_var(char *env_var)
{
	char	*first_eq;

	first_eq = ft_strchr(env_var, '=');
	if (!first_eq)
		return (handle_no_equal_sign(env_var));
	else
		return (handle_equal_sign(env_var, first_eq));
}

int	builtin_export(t_appdata *appdata, t_cmd *cmd)
{
	int		i;
	char	**env_var;

	i = 1;
	if (!cmd->args[i])
		return (builtin_env(appdata));
	while (cmd->args[i])
	{
		if (!is_valid_env_key(cmd->args[i]))
			return (ft_print_cmd_error("export", cmd->args[i], INVALID, 1));
		env_var = extract_env_var(cmd->args[i]);
		if (env_var)
		{
			if (!change_envl(appdata, env_var[0], env_var[1]))
			{
				ft_free_tab(env_var);
				return (1);
			}
			ft_free_tab(env_var);
		}
		else
			return (1);
		++i;
	}
	return (0);
}
