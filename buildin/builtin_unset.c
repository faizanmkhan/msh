/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:32:51 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

#define ENV_NOT_FOUND -1

char	**unset_env(t_appdata *appdata, int index_to_remove)
{
	int		env_count;
	int		new_index;
	char	**new_envl_list;
	int		i;

	env_count = 0;
	new_index = 0;
	if (index_to_remove == ENV_NOT_FOUND)
		return (NULL);
	while (appdata->envl[env_count])
		env_count++;
	new_envl_list = malloc(sizeof(char *) * (env_count));
	if (!new_envl_list)
		return (NULL);
	i = -1;
	while (++i < env_count)
	{
		if (i == index_to_remove)
			continue ;
		new_envl_list[new_index++] = appdata->envl[i];
	}
	free_ptr(appdata->envl[index_to_remove]);
	new_envl_list[new_index] = NULL;
	free(appdata->envl);
	return (new_envl_list);
}

int	look_env(char *arg, t_appdata *appdata)
{
	size_t	arg_len;
	int		i;

	arg_len = ft_strlen(arg);
	i = -1;
	while (appdata->envl[++i])
	{
		if (!ft_strncmp(appdata->envl[i], arg, arg_len)
			&& appdata->envl[i][arg_len] == '=')
			return (i);
	}
	return (-1);
}

int	builtin_unset(t_appdata *appdata, t_cmd *cmd)
{
	int		index;
	char	**new_envl;
	int		i;

	if (!cmd->args[1])
		return (0);
	i = 0;
	while (cmd->args[++i])
	{
		index = look_env(cmd->args[i], appdata);
		if (index == ENV_NOT_FOUND)
			continue ;
		new_envl = unset_env(appdata, index);
		if (!new_envl)
			return (1);
		appdata->envl = new_envl;
	}
	return (0);
}
