/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:57:18 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 12:57:21 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static char	*resolve_cd_path(t_shell_data *shell, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value(shell, "HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else
	{
		path = args[1];
	}
	return (path);
}

static char	*get_current_dir(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (ft_strdup(""));
}

static int	change_directory(const char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static void	update_env_pwd(t_shell_data *shell, const char *oldpwd)
{
	char	cwd[1024];

	set_env_value(shell, "OLDPWD", (char *)oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(shell, "PWD", cwd);
}

int	builtin_cd(t_shell_data *shell, char **args)
{
	char	*path;
	char	*oldpwd;

	path = resolve_cd_path(shell, args);
	if (!path)
		return (1);
	oldpwd = get_current_dir();
	if (!oldpwd)
		return (1);
	if (change_directory(path))
	{
		free(oldpwd);
		return (1);
	}
	update_env_pwd(shell, oldpwd);
	free(oldpwd);
	return (0);
}
