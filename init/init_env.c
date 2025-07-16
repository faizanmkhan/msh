/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:40:24 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

bool	init_envl(t_appdata *appdata, char **envp)
{
	int	len;

	len = -1;
	while (envp[++len])
		;
	appdata->envl = malloc(sizeof(char *) * (len + 1));
	if (!appdata->envl)
		return (false);
	len = -1;
	while (envp[++len])
	{
		appdata->envl[len] = ft_strdup(envp[len]);
		if (!appdata->envl[len])
			return (false);
	}
	appdata->envl[len] = NULL;
	return (true);
}

bool	change_envl(t_appdata *appdata, char *key, char *value)
{
	if (value == NULL)
		value = "";
	if (update_existing_envl(appdata, key, value))
		return (true);
	return (add_new_envl(appdata, key, value));
}

bool	is_valid_env_key(char *key)
{
	int	i;

	i = -1;
	if (!ft_isalpha(key[++i]) && key[i] != '_')
		return (false);
	while (key[++i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
	}
	return (true);
}
