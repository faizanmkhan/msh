/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:57:41 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:57:44 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static void	print_export_env(t_env_data *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

static void	handle_export_argument(t_shell_data *shell, char *arg)
{
	char	*equals;
	char	*key;
	char	*value;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		*equals = '\0';
		key = arg;
		value = equals + 1;
		set_env_value(shell, key, value);
		*equals = '=';
	}
	else
	{
		set_env_value(shell, arg, "");
	}
}

int	builtin_export(t_shell_data *shell, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		print_export_env(shell->shell_env);
		return (0);
	}
	while (args[i])
	{
		handle_export_argument(shell, args[i]);
		i++;
	}
	return (0);
}
