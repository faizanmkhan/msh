/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:37:14 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static int	valid_n_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[i] != '-')
		return (false);
	while (arg[++i] && arg[i] == 'n')
		;
	if (arg[i] == '\0')
		return (true);
	return (false);
}

static void	print_args(char **args, int with_newline)
{
	if (!args || !*args)
	{
		if (with_newline)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
	if (with_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	bool	with_newline;

	i = 0;
	with_newline = true;
	while (cmd->args[++i] && valid_n_arg(cmd->args[i]))
		with_newline = false;
	print_args(cmd->args + i, with_newline);
	return (0);
}

int	builtin_env(t_appdata *appdata)
{
	int	i;

	i = -1;
	while (appdata->envl && appdata->envl[++i])
		ft_putendl_fd(appdata->envl[i], STDOUT_FILENO);
	return (0);
}

bool	builtin_pwd(void)
{
	char	current_pwd[PATH_MAX];

	ft_memset(current_pwd, 0, PATH_MAX);
	if (!getcwd(current_pwd, PATH_MAX))
	{
		perror("PWD Error");
		return (BAD);
	}
	ft_putstr_fd(current_pwd, 1);
	ft_putstr_fd("\n", 1);
	return (OK);
}
