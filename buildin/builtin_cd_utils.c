/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:31:57 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	*look_env_value(char *argv, char **new_env)
{
	int	i;
	int	j;

	j = 0;
	if (!argv && !new_env)
		return (NULL);
	i = ft_strlen(argv);
	while (new_env[j])
	{
		if (!ft_strncmp(new_env[j], argv, i))
			if (new_env[j][i] == '=')
				return (&new_env[j][i + 1]);
		j++;
	}
	return (NULL);
}

int	only_oldpwd_setted(t_appdata *appdata, char *temp)
{
	int	i;

	i = 0;
	i = look_env("OLDPWD", appdata);
	free(appdata->envl[i]);
	appdata->envl[i] = ft_strdup("OLDPWD=");
	if (!appdata->envl[i])
		return (ft_putendl_fd("ERROR MALLOC strdup", STDERR_FILENO), -1);
	add_new_envl(appdata, "PWD", temp);
	return (1);
}

int	only_pwd_setted(t_appdata *appdata, char *temp, char *pwd)
{
	int	i;

	i = 0;
	i = look_env("PWD", appdata);
	free(appdata->envl[i]);
	appdata->envl[i] = ft_strjoin("PWD=", temp);
	if (!appdata->envl[i])
		return (ft_putendl_fd("ERROR MALLOC ON JOIN", STDERR_FILENO), -1);
	add_new_envl(appdata, "OLDPWD", pwd);
	return (2);
}

int	pwd_oldpwd_setted(t_appdata *appdata, char *temp)
{
	int		i;
	int		j;
	char	*env;
	char	pwd[PATH_MAX];

	env = look_env_value("PWD", appdata->envl);
	i = look_env("OLDPWD", appdata);
	j = look_env("PWD", appdata);
	ft_strlcpy(pwd, env, ft_strlen(env) + 1);
	env = NULL;
	free(appdata->envl[i]);
	env = ft_strjoin("OLDPWD=", pwd);
	if (!env)
		return (ft_putendl_fd("ERROR MALLOC ON JOIN", STDERR_FILENO), -1);
	appdata->envl[i] = env;
	free(appdata->envl[j]);
	appdata->envl[j] = ft_strjoin("PWD=", temp);
	return (3);
}

int	swap_pwd(char *dir, t_appdata *appdata, char *curr_dir)
{
	int		k;
	char	pwd[PATH_MAX];
	char	temp[PATH_MAX];

	k = 0;
	if (!dir)
		dir = "";
	if (!curr_dir)
		curr_dir = "";
	pwd[0] = 0;
	temp[0] = 0;
	ft_memmove(temp, dir, ft_strlen(dir) + 1);
	ft_memmove(pwd, curr_dir, ft_strlen(curr_dir) + 1);
	if (look_env_value("OLDPWD", appdata->envl))
		k = 1;
	if (look_env_value("PWD", appdata->envl))
		k += 2;
	if (k == 3)
		return (pwd_oldpwd_setted(appdata, temp));
	else if (k == 2)
		return (only_pwd_setted(appdata, temp, pwd));
	else if (k == 1)
		return (only_oldpwd_setted(appdata, temp));
	else
		return (add_new_envl(appdata, "PWD", temp), k);
}
