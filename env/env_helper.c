/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:01:58 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	*clean_var_heredoc(char *str, int var_i)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - key_length(str + var_i);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$' && i == var_i)
		{
			i += key_length(str + var_i) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_ptr(str);
	return (new_str);
}

bool	update_existing_envl(t_appdata *appdata, char *key, char *value)
{
	int		i;
	char	*new_key_value;

	i = -1;
	while (appdata->envl[++i])
	{
		if (ft_strncmp(appdata->envl[i], key, ft_strlen(key)) == 0)
		{
			new_key_value = create_new_envl_entry(key, value);
			if (!new_key_value)
				return (false);
			free(appdata->envl[i]);
			appdata->envl[i] = new_key_value;
			return (true);
		}
	}
	return (false);
}

char	*create_new_envl_entry(char *key, char *value)
{
	char	*new_envl;
	size_t	key_len;
	size_t	value_len;
	size_t	total_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	total_len = key_len + value_len + 2;
	new_envl = malloc(total_len);
	if (!new_envl)
		return (NULL);
	ft_strlcpy(new_envl, key, total_len);
	ft_strlcat(new_envl, "=", total_len);
	ft_strlcat(new_envl, value, total_len);
	return (new_envl);
}

char	**expand_envl_list(char **envl, int size)
{
	int		j;
	char	**new_envl_list;

	new_envl_list = malloc(sizeof(char *) * (size + 2));
	if (!new_envl_list)
		return (NULL);
	j = -1;
	while (++j < size)
		new_envl_list[j] = envl[j];
	return (new_envl_list);
}

bool	add_new_envl(t_appdata *appdata, char *key, char *value)
{
	int		i;
	char	*new_envl;
	char	**new_envl_list;

	i = -1;
	while (appdata->envl[++i])
		;
	new_envl = create_new_envl_entry(key, value);
	if (!new_envl)
		return (false);
	new_envl_list = expand_envl_list(appdata->envl, i);
	if (!new_envl_list)
	{
		free(new_envl_list);
		return (false);
	}
	new_envl_list[i] = new_envl;
	new_envl_list[i + 1] = NULL;
	free(appdata->envl);
	appdata->envl = new_envl_list;
	return (true);
}
