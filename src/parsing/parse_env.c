/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:59:30 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 13:59:31 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

t_env_data	*parse_env_var(char *str_after_signtr)
{
	t_env_data	*new_env;
	char		*delimiter;
	char		*key;
	char		*value;

	delimiter = ft_strchr(str_after_signtr, '=');
	if (!delimiter)
		return (NULL);
	*delimiter = 0;
	key = ft_strdup(str_after_signtr);
	value = ft_strdup(delimiter + 1);
	*delimiter = '=';
	new_env = malloc(sizeof(t_env_data));
	if (!new_env)
		return (NULL);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	return (new_env);
}

void	append_env_vars(t_shell_data *myshell, t_env_data *sh_env)
{
	t_env_data	*current;

	if (!myshell->shell_env)
		myshell->shell_env = sh_env;
	else
	{
		current = myshell->shell_env;
		while (current->next)
			current = current->next;
		current->next = sh_env;
	}
}

int	ft_char_pos(char *s, int start, char c)
{
	while (s[start])
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

char	*expand_env_value(char *str_after_sign, t_shell_data *shell)
{
	char	*env_big;

	if (str_after_sign[0] == '?')
	{
		return (ft_itoa(shell->exit_status));
	}
	else
	{
		env_big = getenv(str_after_sign);
		if (!env_big)
			env_big = ft_strdup("");
		return (env_big);
	}
	return (NULL);
}

void	processing_env_expansion(char *s, t_shell_data *myshell,
		char **final_str)
{
	int		sign_pos;
	int		first_space_index;
	char	*str_before_sign;
	char	*str_after_sign;
	char	*expanded_env;

	sign_pos = ft_char_pos(s, 0, '$');
	if (sign_pos == -1)
	{
		*final_str = ft_strdup(s);
		return ;
	}
	str_before_sign = ft_substr(s, 0, sign_pos);
	first_space_index = ft_char_pos(s, sign_pos, ' ');
	if (first_space_index == -1)
		first_space_index = ft_strlen(s);
	str_after_sign = ft_substr(s, sign_pos + 1,
			first_space_index - sign_pos - 1);
	expanded_env = expand_env_value(str_after_sign, myshell);
	free(str_after_sign);
	*final_str = ft_strjoin(str_before_sign, expanded_env);
	free(str_before_sign);
}
