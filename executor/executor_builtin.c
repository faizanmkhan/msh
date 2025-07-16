/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:30:40 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	execute_builtin(t_appdata *appdata, t_cmd *cmd)
{
	int	ret;

	ret = 127;
	if (ft_strncmp(cmd->name, "cd", 3) == 0)
		ret = builtin_cd(appdata, cmd->args);
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		ret = builtin_echo(cmd);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		ret = builtin_env(appdata);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		ret = builtin_export(appdata, cmd);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		ret = builtin_pwd();
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		ret = builtin_unset(appdata, cmd);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		ret = builtin_exit(appdata, cmd);
	return (ret);
}
