/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:42:45 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static char	*get_val(t_appdata *appdata, char *key)
{
	char	**envl;
	int		key_len;
	int		val_len;
	char	*val;

	envl = appdata->envl;
	key_len = ft_strlen(key);
	while (*envl)
	{
		if (ft_strncmp(*envl, key, key_len) == 0)
		{
			val = ft_strchr(*envl, '=') + 1;
			val_len = ft_strlen(val);
			val = ft_substr(val, 0, val_len);
			return (val);
		}
		++envl;
	}
	return (NULL);
}

static bool	find_env(t_appdata *appdata, char *key)
{
	char	**envl;
	int		key_len;

	envl = appdata->envl;
	key_len = ft_strlen(key);
	while (*envl)
	{
		if (ft_strncmp(*envl, key, key_len) == 0)
			return (true);
		++envl;
	}
	return (false);
}

int	key_length(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] != '$')
		++i;
	++i;
	if (str[i] == '?')
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		++len;
		++i;
	}
	return (len);
}

char	*get_key(char *str)
{
	char	*key;
	int		key_len;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	key_len = key_length(str);
	key = ft_substr(str, i + 1, key_len);
	if (!key)
		return (NULL);
	key = ft_strextend(key, "=");
	return (key);
}

char	*get_env_var_val(t_appdata *appdata, t_tok *tok, char *str)
{
	char	*key;
	char	*value;

	key = get_key(str);
	if (key && find_env(appdata, key))
	{
		if (tok)
			tok->has_var = true;
		value = get_val(appdata, key);
	}
	else if (key && key[0] == '?' && key[1] == '=')
		value = ft_itoa(g_exit_code);
	else
		value = NULL;
	free_ptr(key);
	return (value);
}
