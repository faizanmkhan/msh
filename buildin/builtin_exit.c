/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:52:46 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

bool	is_out_of_range(unsigned long long n, int sign, bool *error)
{
	if ((sign == 1 && n > LONG_MAX) || (sign == -1
			&& n > (-(unsigned long)LONG_MIN)))
		*error = true;
	return (*error);
}

int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	n;
	int					sign;
	int					i;

	n = 0;
	sign = 1;
	i = -1;
	while (str[++i] && ft_isspace(str[i]))
		;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		n = (n * 10) + (str[i] - '0');
		if (is_out_of_range(n, sign, error))
			break ;
		++i;
	}
	return (sign * n);
}

int	parse_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

static bool	skip_exit(t_appdata *appdata)
{
	t_cmd	*cmd;

	cmd = appdata->head_cmd;
	if (cmd == NULL)
		return (false);
	return (cmd->nxt != NULL || cmd->prv != NULL);
}

int	builtin_exit(t_appdata *appdata, t_cmd *cmd)
{
	int		exit_code;
	bool	error;

	error = false;
	if (!skip_exit(appdata))
		ft_putendl_fd("exit", 2);
	if (!cmd || !cmd->args || !cmd->args[1])
		exit_code = g_exit_code;
	else
	{
		exit_code = parse_exit_code(cmd->args[1], &error);
		if (error)
			exit_code = ft_print_cmd_error("exit", cmd->args[1],
					"numeric argument required", 2);
		else if (cmd->args[2])
			return (ft_print_cmd_error("exit", NULL, "too many arguments", 1));
	}
	exit_minishell(appdata, exit_code);
	return (2);
}
