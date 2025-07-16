/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:00:08 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

bool	clean_var(t_tok *tok, char *str, int var_i)
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
	free_ptr(tok->data);
	tok->data = new_str;
	return (true);
}

char	*replace_env_var(char *str, char *val, int new_len, int var_i)
{
	int		i;
	int		j;
	char	*new_str;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && i == var_i)
		{
			while (val[k])
				new_str[j++] = val[k++];
			i += key_length(str + var_i) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

static	char	*fill_var(t_tok *tok, char *str, char *val, int i)
{
	char	*new_str;
	int		new_len;

	new_len = ft_strlen(str) - key_length(str + i) + ft_strlen(val);
	new_str = replace_env_var(str, val, new_len, i);
	if (tok)
	{
		free_ptr(tok->data);
		tok->data = new_str;
	}
	return (new_str);
}

bool	fill_env_var_val(t_tok *tok, char *val, int i)
{
	if (val == NULL)
	{
		if (clean_var(tok, tok->data, i))
		{
			free_ptr(val);
			return (true);
		}
	}
	else
	{
		if (fill_var(tok, tok->data, val, i))
		{
			free_ptr(val);
			return (true);
		}
	}
	free_ptr(val);
	return (false);
}

char	*fill_env_var_val_heredoc(char *str, char *val, int i)
{
	char	*tmp;

	tmp = NULL;
	if (val == NULL)
		str = (clean_var_heredoc(str, i));
	else
	{
		tmp = str;
		str = fill_var(NULL, str, val, i);
		free_ptr(tmp);
	}
	return (str);
}
