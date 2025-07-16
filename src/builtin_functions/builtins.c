/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:58:00 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:58:39 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	return (ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0
		|| ft_strcmp(command, "exit") == 0);
}

int	execute_builtin(t_shell_data *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(shell, cmd->args));
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	builtin_exit(t_shell_data *shell, char **args)
{
	int	exit_code;

	exit_code = shell->exit_status;
	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
	}
	printf("exit\n");
	exit(exit_code);
}

//	cleanup_shell(shell); line 96