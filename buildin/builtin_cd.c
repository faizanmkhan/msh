/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:31:24 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

bool	home_folder(t_appdata *appdata, char *new_dir, char *curr_dir)
{
	new_dir = look_env_value("HOME", appdata->envl);
	if (!new_dir)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), true);
	if (ft_chdir(new_dir))
		return (true);
	swap_pwd(new_dir, appdata, curr_dir);
	new_dir = NULL;
	return (false);
}

bool	cd_null_argument(t_appdata *appdata, char *new_dir, char *curr_dir)
{
	if (!getcwd(curr_dir, PATH_MAX))
		return (perror(""), true);
	new_dir = curr_dir;
	swap_pwd(new_dir, appdata, curr_dir);
	return (false);
}

bool	cd_prv(t_appdata *appdata, char *new_dir, char *curr_dir, char *dir)
{
	new_dir = look_env_value("OLDPWD", appdata->envl);
	if (!new_dir)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), true);
	if (ft_chdir(new_dir))
		return (true);
	ft_putendl_fd(new_dir, STDOUT_FILENO);
	ft_memmove(dir, new_dir, ft_strlen(new_dir) + 1);
	swap_pwd(dir, appdata, curr_dir);
	return (false);
}

bool	cd_change(char *argv, t_appdata *appdata, char *dir, char *curr_dir)
{
	if (ft_chdir(argv))
		return (true);
	swap_pwd(getcwd(dir, PATH_MAX), appdata, curr_dir);
	return (false);
}

bool	builtin_cd(t_appdata *appdata, char **argv)
{
	int		i;
	char	*new_dir;
	char	dir[PATH_MAX];
	char	curr_dir[PATH_MAX];

	new_dir = NULL;
	dir[0] = 0;
	curr_dir[0] = 0;
	i = 1;
	getcwd(curr_dir, PATH_MAX);
	if ((!argv[i]) || (!ft_strncmp(argv[i], "--", ft_strlen("--") + 1)))
		return (home_folder(appdata, new_dir, curr_dir));
	if (argv[2])
		return (perror("bash: cd: too many arguments"), true);
	else if (!ft_strncmp(argv[i], "", 1))
		return (cd_null_argument(appdata, new_dir, curr_dir));
	else if (!ft_strncmp(argv[i], "-", ft_strlen("-") + 1))
		return (cd_prv(appdata, new_dir, curr_dir, dir));
	else if (argv[i])
		return (cd_change(argv[i], appdata, dir, curr_dir));
	return (false);
}
